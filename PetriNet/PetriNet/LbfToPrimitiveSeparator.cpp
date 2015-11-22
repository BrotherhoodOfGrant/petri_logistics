#include "stdafx.h"
#include "LbfToPrimitiveSeparator.h"

LbfToPrimitiveSeparator::LbfToPrimitiveSeparator()
{
}


LbfToPrimitiveSeparator::~LbfToPrimitiveSeparator()
{
}

Petri_Net * LbfToPrimitiveSeparator::Separate(
	_In_ Petri_Net& lbfNet,
	_Out_ Matrix** tensor,
	_Out_opt_ UINT * pnCountDecompositedPos /*= NULL*/
	)
{
	Petri_Net * pPrimitivesNet;
	Petri_Net * pLbfNetSized;

	// Получение сети Петри, состоящей из примитивов.
	pPrimitivesNet = GeneratePrimitivesNet(lbfNet, &pLbfNetSized, pnCountDecompositedPos);
	if (!pPrimitivesNet || !pLbfNetSized)
	{
		return NULL;
	}
	
	*tensor = BuildTensor(pLbfNetSized, pPrimitivesNet);
	if (!(*tensor))
	{
		delete pLbfNetSized;
		delete pPrimitivesNet;
		return NULL;
	}

	return pPrimitivesNet;
}

Petri_Net * LbfToPrimitiveSeparator::GeneratePrimitivesNet(
	_In_ Petri_Net& lbfNet,
	_Out_ Petri_Net ** ppSizedLbfNet,
	_Out_opt_ UINT * pnCountDecompositedPos
	)
{
	Petri_Net * pPetriNetPrimitives;
	Petri_Net * pSizedLbfNet;
	UINT cntDecompositedPos = 0;
	UINT nCurInTransition;
	UINT nCurOutTransition;
	UINT nCurConvertedPosIndex;
	bool fResult;

	pPetriNetPrimitives = new Petri_Net();
	if (!pPetriNetPrimitives)
	{
		return NULL;
	}

	if (!pPetriNetPrimitives->GetClone(&lbfNet, true))
	{
		delete pPetriNetPrimitives;
		return NULL;
	}

	pSizedLbfNet = new Petri_Net();
	if (!pSizedLbfNet)
	{
		return NULL;
	}

	if (!pSizedLbfNet->GetClone(&lbfNet, true))
	{
		delete pSizedLbfNet;
		delete pPetriNetPrimitives;
		return NULL;
	}

	bool fDecompositionOccuried;
	AltStructsSynthesizer::PrintPetriNet(*pPetriNetPrimitives);
	do
	{
		fDecompositionOccuried = false;

		for (size_t curRowPosition = 0; curRowPosition < pPetriNetPrimitives->GetNumberOfPositions(); curRowPosition++)
		{
			int cntPosInRow = 0;

			nCurInTransition = 0;
			nCurOutTransition = 0;

			for (size_t curColTransition = 0; curColTransition < pPetriNetPrimitives->GetNumberOfTransitions(); curColTransition++)
			{
				int ElementMatrixD = pPetriNetPrimitives->GetElementMatrixD(curRowPosition, curColTransition);

				if (isUsePosInTransition(ElementMatrixD))
				{
					if (ElementMatrixD < 0)
					{
						nCurOutTransition = curColTransition;
					}
					else
					{
						nCurInTransition = curColTransition;
					}

					if (++cntPosInRow > 1)
					{
						break;
					}
				}
			}

			if (cntPosInRow > 1)
			{
				if (!pSizedLbfNet->DecompositionPos(pPetriNetPrimitives->GetNumberPosition(curRowPosition), cntPosInRow))
				{
					delete pSizedLbfNet; 
					delete pPetriNetPrimitives;
					return NULL;
				}

				if (!pPetriNetPrimitives->DecompositionPos(pPetriNetPrimitives->GetNumberPosition(curRowPosition), cntPosInRow))
				{
					delete pSizedLbfNet;
					delete pPetriNetPrimitives;
					return NULL;
				}

				// Разрываем связи.
				nCurConvertedPosIndex = pPetriNetPrimitives->GetNumberPosition(
					pPetriNetPrimitives->GetNumberOfPositions() - 2);

				nCurOutTransition = pPetriNetPrimitives->GetNumberTtransition(nCurOutTransition);
				nCurInTransition = pPetriNetPrimitives->GetNumberTtransition(nCurInTransition);

				AltStructsSynthesizer::PrintPetriNet(*pPetriNetPrimitives);

				fResult = pPetriNetPrimitives->RemoveArc(
					pPetriNetPrimitives->GetNamePosition(nCurConvertedPosIndex),
					pPetriNetPrimitives->GetNameTransition(nCurOutTransition));
				if (!fResult)
				{
					delete pSizedLbfNet;
					delete pPetriNetPrimitives;
					return NULL;
				}

				AltStructsSynthesizer::PrintPetriNet(*pPetriNetPrimitives);

				nCurConvertedPosIndex = pPetriNetPrimitives->GetNumberPosition(
					pPetriNetPrimitives->GetNumberOfPositions() - 1);

				fResult = pPetriNetPrimitives->RemoveArc(
					pPetriNetPrimitives->GetNameTransition(nCurInTransition),
					pPetriNetPrimitives->GetNamePosition(nCurConvertedPosIndex));
				if (!fResult)
				{
					delete pSizedLbfNet;
					delete pPetriNetPrimitives;
					return NULL;
				}

				AltStructsSynthesizer::PrintPetriNet(*pPetriNetPrimitives);

				fDecompositionOccuried = true;
				cntDecompositedPos++;
				break;
			}
		}

	} while (fDecompositionOccuried);

	if (pnCountDecompositedPos)
	{
		*pnCountDecompositedPos = cntDecompositedPos;
	}

	delete pSizedLbfNet;

	return pPetriNetPrimitives;
}

bool LbfToPrimitiveSeparator::isUsePosInTransition(int ElementMatrixD)
{
	return ElementMatrixD ? true : false;
}

Matrix * LbfToPrimitiveSeparator::BuildTensor(
	_In_ Petri_Net * pLbfNetSized,
	_In_ Petri_Net * pPrimitivesNet
	)
{
	Matrix * pTensor;

	// Создаем тензор.
	pTensor = new Matrix(
		pPrimitivesNet->GetNumberOfPositions(),
		pPrimitivesNet->GetNumberOfPositions());
	if (!pTensor)
	{
		return NULL;
	}

	// Заполняем матрицу по алгоритму Кулагина.
	for (UINT i = 0; i < pTensor->get_count_col(); i++)
	{
		for (UINT j = 0; j < pTensor->get_count_row(); j++)
		{
			pTensor->set_value(i, j, 0);
		}

		// Для всех i=(1,n) выполнить: c(i, i) = 1.
		pTensor->set_value(i, i, 1);

		// Для всех i=(1,m-1) выполнить: c(2i, 2i + 2) = -1
		//				    		     c(2i+1, 2i) = 1.
		// Важно помнить, что у Кулагина координаты задаются, как (строка, столбец).
		if (i < pPrimitivesNet->GetNumberOfTransitions() - 1)
		{
			// Удостоверимся, что индекс не выйдет за границу массива.
			// TODO: Здесь стоит добавить исключение.
			//ASSERT( 2 * i + 2 < pTensor->get_count_col() );

			pTensor->set_value(2 * i + 2, 2 * i, -1);
			pTensor->set_value(2 * i, 2 * i + 1, 1);
		}
	}

	return pTensor;
}

