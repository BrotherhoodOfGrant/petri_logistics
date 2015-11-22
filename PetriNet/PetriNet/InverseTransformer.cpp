#include "stdafx.h"
#include "InverseTransformer.h"


InverseTransformer::InverseTransformer()
{
}


InverseTransformer::~InverseTransformer()
{
}

bool InverseTransformer::Transform(_Inout_ AlternativeNest &altNets, _In_ Matrix &tensor)
{
	AlternativeNest::iterator Iter;

	for (Iter = altNets.begin(); Iter != altNets.end(); Iter++)
	{
		if (!Convert(*Iter, tensor))
		{
			// TODO: исключение. Продолжать работу, записать в лог или выйти?
			return false;
		}

		if (!Reduce(*Iter))
		{
			return false;
		}
	}

	return true;
}

bool InverseTransformer::Convert(
	_Inout_ Petri_Net * pAltNet,
	_In_ Matrix &tensor
	)
{
	Matrix * pNewNetMatrix;
	double dElementValue;

	// Создаем новую матрицу для преобразованной сети.
	pNewNetMatrix = new Matrix(
		pAltNet->GetNumberOfPositions(),
		pAltNet->GetNumberOfTransitions());
	if (!pNewNetMatrix)
	{
		return false;
	}

	// Заполняем матрицу.
	for (UINT i = 0; i < pNewNetMatrix->get_count_row(); i++)
	{
		for (UINT j = 0; j < pNewNetMatrix->get_count_col(); j++)
		{
			dElementValue = 0;

			for (UINT k = 0; k < pNewNetMatrix->get_count_row(); k++)
			{
				dElementValue +=
					tensor.get_value(i, k) * pAltNet->GetElementMatrixD(k, j);
			}

			pNewNetMatrix->set_value(j, i, dElementValue);
		}
	}

	// Заполняем матрицу имеющейся сети значениями из матрицы преобразованной
	// сети.
	for (UINT i = 0; i < pNewNetMatrix->get_count_col(); i++)
	{
		for (UINT j = 0; j < pNewNetMatrix->get_count_row(); j++)
		{
			if (!pAltNet->SetElementMatrixD(i, j, pNewNetMatrix->get_value(i, j)))
			{
				delete pNewNetMatrix;
				return false;
			}
		}
	}

	return true;
}

bool InverseTransformer::Reduce(
	_Inout_ Petri_Net * pAltNet
	)
{
	bool fDifferencesFound;

	fDifferencesFound = true;

	//row transition, col position
	do
	{
		for (UINT nCurColPosition = 0; nCurColPosition < pAltNet->GetNumberOfPositions(); nCurColPosition++)
		{
			for (UINT nCurColComparedPos = nCurColPosition + 1; nCurColComparedPos < pAltNet->GetNumberOfPositions(); nCurColComparedPos++)
			{
				fDifferencesFound = false;

				for (UINT nCurRowTransition = 0; nCurRowTransition < pAltNet->GetNumberOfTransitions(); nCurRowTransition++)
				{
					if (pAltNet->GetElementMatrixD(nCurColPosition, nCurRowTransition)
						!= pAltNet->GetElementMatrixD(nCurColComparedPos, nCurRowTransition))
					{
						fDifferencesFound = true;
						break;
					}
				}

				if (!fDifferencesFound)
				{
					if (!pAltNet->RemovePosition(pAltNet->GetNumberPosition(nCurColPosition)))
					{
						return false;
					}

					break;
				}
			}

			if (!fDifferencesFound)
			{
				break;
			}
		}

	} while (!fDifferencesFound);

	/*do
	{
		for (UINT nCurRowPosition = 0; nCurRowPosition < pAltNet->GetNumberOfPositions(); nCurRowPosition++)
		{
			for (UINT nCurRowComparedPos = nCurRowPosition + 1; nCurRowComparedPos < pAltNet->GetNumberOfPositions(); nCurRowComparedPos++)
			{
				fDifferencesFound = false;

				for (UINT nCurColTransition = 0; nCurColTransition < pAltNet->GetNumberOfTransitions(); nCurColTransition++)
				{
					if (pAltNet->GetElementMatrixD(nCurColTransition, nCurRowPosition) 
						!= pAltNet->GetElementMatrixD(nCurColTransition, nCurRowComparedPos))
					{
						fDifferencesFound = true;
						break;
					}
				}

				if (!fDifferencesFound)
				{
					if (!pAltNet->RemovePosition(pAltNet->GetNumberPosition(nCurRowPosition)))
					{
						return false;
					}
					
					break;
				}
			}

			if (!fDifferencesFound)
			{
				break;
			}
		}

	} while (!fDifferencesFound);*/

	return true;
}