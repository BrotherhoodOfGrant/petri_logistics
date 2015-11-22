/**
* @file Synthesys.h
* Реализация класса, выполняющего синтез СП-структур
* @author Егор, Лена, Кристина @date 02.11.2015
*/


#include "stdafx.h"
#include "SynthesisProgrammGenerator.h"

AltStructsSynthesizer::AltStructsSynthesizer()
{
}


AltStructsSynthesizer::~AltStructsSynthesizer()
{
}

void AltStructsSynthesizer::PrintPetriNet(Petri_Net& net)
{
	int posLimit = net.GetNumberOfPositions();
	int trnLimit = net.GetNumberOfTransitions();
	int elem;

	for (int transInd = 0; transInd < trnLimit; transInd++)
	{
		for (int posInd = 0; posInd < posLimit; posInd++)
		{
			elem = net.GetElementMatrixD(posInd, transInd);
			printf("%2d ", elem);
		}

		printf("\n");
	}

	//for (int posInd = 0; posInd < posLimit; posInd++)
	//{
	//	for (int transInd = 0; transInd < trnLimit; transInd++)
	//	{
	//		elem = net.GetElementMatrixD(posInd, transInd);
	//		printf("%2d ", elem);
	//	}

	//	printf("\n");
	//}

	printf("\n");
}

AlternativeNest* AltStructsSynthesizer::Synthesise(
	Petri_Net *LbfNet, 
	Petri_Net *PrimitiveNet, 
	vector<int> *pUniteOoerationeVector,
	DWORD nAdditionalRestrictions)
{
/*
	LbfNet = new Petri_Net();
	LbfNet->AddPosition(1, 0, "P1");
	LbfNet->AddPosition(1, 1, "P2");
	LbfNet->AddPosition(1, 2, "P3");
	LbfNet->AddPosition(1, 3, "P4");
	LbfNet->AddPosition(1, 4, "P5");
// 	LbfNet->AddPosition(1, 5, "P6");
// 	LbfNet->AddPosition(1, 6, "P7");
// 	LbfNet->AddPosition(1, 7, "P8");
	LbfNet->AddTransition(0, "T1");
	LbfNet->AddTransition(1, "T2");
	LbfNet->AddTransition(2, "T3");
// 	LbfNet->AddTransition(3, "T4");
// 	LbfNet->AddTransition(4, "T5");
// 	LbfNet->AddTransition(5, "T6");
	LbfNet->AddArc(1, 0, 0, true);
	LbfNet->AddArc(1, 0, 1, false);
	LbfNet->AddArc(1, 1, 1, true);
	LbfNet->AddArc(1, 1, 2, false);
	LbfNet->AddArc(1, 3, 2, true);
	LbfNet->AddArc(1, 2, 4, false);
// 	LbfNet->AddArc(1, 5, 3, true);
// 	LbfNet->AddArc(1, 3, 6, false);
// 	LbfNet->AddArc(1, 6, 4, true);
// 	LbfNet->AddArc(1, 4, 7, false);
// 	LbfNet->AddArc(1, 7, 5, true);
// 	LbfNet->AddArc(1, 5, 5, false);
	
	PrimitiveNet = new Petri_Net();
	PrimitiveNet->AddPosition(0, 0, "P1");
	PrimitiveNet->AddPosition(0, 1, "P21");
	PrimitiveNet->AddPosition(0, 2, "P22");
	PrimitiveNet->AddPosition(0, 3, "P3");
	PrimitiveNet->AddPosition(0, 4, "P4");
	PrimitiveNet->AddPosition(0, 5, "P5");
// 	PrimitiveNet->AddPosition(0, 6, "P61");
// 	PrimitiveNet->AddPosition(0, 7, "P62");
// 	PrimitiveNet->AddPosition(0, 8, "P71");
// 	PrimitiveNet->AddPosition(0, 9, "P72");
// 	PrimitiveNet->AddPosition(0, 10, "P81");
// 	PrimitiveNet->AddPosition(0, 11, "P82");
	PrimitiveNet->AddTransition(0, "T1");
	PrimitiveNet->AddTransition(1, "T2");
	PrimitiveNet->AddTransition(2, "T3");
// 	PrimitiveNet->AddTransition(3, "T4");
// 	PrimitiveNet->AddTransition(4, "T5");
// 	PrimitiveNet->AddTransition(5, "T6");
	PrimitiveNet->AddArc(1, 0, 0, true);
	PrimitiveNet->AddArc(1, 0, 1, false);
	PrimitiveNet->AddArc(1, 2, 1, true);
	PrimitiveNet->AddArc(1, 1, 3, false);
	PrimitiveNet->AddArc(1, 4, 2, true);
	PrimitiveNet->AddArc(1, 2, 5, false);
// 	PrimitiveNet->AddArc(1, 6, 3, true);
// 	PrimitiveNet->AddArc(1, 3, 8, false);
// 	PrimitiveNet->AddArc(1, 9, 4, true);
// 	PrimitiveNet->AddArc(1, 4, 10, false);
// 	PrimitiveNet->AddArc(1, 7, 5, true);
// 	PrimitiveNet->AddArc(1, 5, 11, false);

	PrintPetriNet(*LbfNet);
	PrintPetriNet(*PrimitiveNet);
*/


	// Разделение переходов из ЛБФ по группам, разделение позиций из примитивов по группам,  
	// формирование вектор распределения для переходов и позиций
	auto lbfGroups = GetTransitionPositionGroups(*LbfNet);
	auto primitiveGroups = GetTransitionPositionGroups(*PrimitiveNet);
	
	RestrictionsfVector TransitionRestrictions;
	RestrictionsfVector PositionRestrictions;
	
	// сформировать вектор ограничений для переходов
	for (int i = 0; i < lbfGroups->size(); i++)
	{
		TransitionRestrictions.push_back((*lbfGroups)[i].Transitions->size());
		delete((*lbfGroups)[i].Transitions);
		delete((*lbfGroups)[i].Positions);
	}

	// сформировать вектор ограничений для позиций
	for (int i = 0; i < primitiveGroups->size(); i++)
	{
		PositionRestrictions.push_back((*primitiveGroups)[i].Positions->size());
		delete((*primitiveGroups)[i].Transitions);
		delete((*primitiveGroups)[i].Positions);
	}

	delete(lbfGroups);
	delete(primitiveGroups);

	// Инициализировать генераторы программ синтеза
	SynthesisProgrammGenerator PositionsGenerator(PositionRestrictions);
	SynthesisProgrammGenerator TransitionsGenerator(TransitionRestrictions);

	SynthesysVector TransitionsProgramm;
	SynthesysVector PositionsProgramm;

	AlternativeNest *NewNets = new AlternativeNest();

	
	while (TransitionsGenerator.GetNextCounterSynthesisProgramm(TransitionsProgramm)){
		while (PositionsGenerator.GetNextCounterSynthesisProgramm(PositionsProgramm)){
		
			// Проверка дополнительных ораничений
			if (nAdditionalRestrictions & SYSNTHESIS_LOOP_RESTRICTION){
				if (!LoopRestrictionPass(TransitionsProgramm, PositionsProgramm)){
					continue;
				}
			}

			int nUniteOperationsCount = 0;
			Petri_Net *pAlternativeNet = Union(&PositionsProgramm, &TransitionsProgramm, PrimitiveNet, &nUniteOperationsCount);

			if (pAlternativeNet){
				//PrintPetriNet(*pAlternativeNet);
				NewNets->push_back(pAlternativeNet);
				if (pUniteOoerationeVector)
					pUniteOoerationeVector->push_back(nUniteOperationsCount);
			}
			else{
				// Ошибка
				__debugbreak();
			}
		}
		PositionsGenerator.Reset();
	}

	return NewNets;
}

vector<AltStructsSynthesizer::TransitionPositionGroup>*  AltStructsSynthesizer::GetTransitionPositionGroups(Petri_Net& lbfNet)
{
	auto groups = new vector<TransitionPositionGroup>();
	auto curTransGroup = new vector<int>();
	auto curPosGroup = new vector<int>();
	auto transToSkip = new vector<int>();
	auto posToSkip = new vector<int>();

	// Перебор всех позиций
	for (int pIndex = 0; pIndex < lbfNet.GetNumberOfPositions(); pIndex++)
	{
		// Если позиция уже рассмотрена, она пропускается
		if (std::find(posToSkip->begin(), posToSkip->end(), pIndex) != posToSkip->end())
		{
			continue;
		}

		// Добавление позиции в текущую группу
		curPosGroup->push_back(pIndex);

		int transAddedCount;
		int posAddedCount;

		do
		{
			transAddedCount = curTransGroup->size();
			posAddedCount = curPosGroup->size();

			// Получение всех переходов, связанных с позициями группы, и добавление их в группу, если они еще не добавлены.
			// Если в группе встречается рассмотренная позиция, она пропускается. Позиция считается рассмотренной после получения
			// всех связанных с ней переходов.
			for (int i = 0; i < curPosGroup->size(); i++)
			{
				if (std::find(posToSkip->begin(), posToSkip->end(), (*curPosGroup)[i]) != posToSkip->end())
				{
					continue;
				}

				AddTransitionsRelatedPositionIfNotAdded(lbfNet, (*curPosGroup)[i], *curTransGroup);
				posToSkip->push_back((*curPosGroup)[i]);
			}

			// Получение всех позиций, связанных с переходами группы, и добавление их в группу, если они еще не добавлены.
			// Если в группе встречается рассмотренный переход, он пропускается. Переход считается рассмотренным после получения
			// всех связанных с ним позиций.
			for (int i = 0; i < curTransGroup->size(); i++)
			{
				if (std::find(transToSkip->begin(), transToSkip->end(), (*curTransGroup)[i]) != transToSkip->end())
				{
					continue;
				}

				AddPositionsRelatedTransitionIfNotAdded(lbfNet, (*curTransGroup)[i], *curPosGroup);
				transToSkip->push_back((*curTransGroup)[i]);
			}
		// Если за итерацию цикла не добавилось в группы ни одной новой позиции или перехода, то все связанные 
		// между собой переходы и позиции рассмотрены, группа полностью сформирована
		} while (transAddedCount < curTransGroup->size() || posAddedCount < curPosGroup->size());
		
		if (curTransGroup->size() != 0 || curPosGroup->size() != 0)
		{
			TransitionPositionGroup group;
			group.Transitions = new vector<int>(*curTransGroup);
			group.Positions = new vector<int>(*curPosGroup);
			groups->push_back(group);

			curTransGroup->clear();
			curPosGroup->clear();
		}
	}
	
	delete(curTransGroup);
	delete(curPosGroup);
	delete(transToSkip);
	delete(posToSkip);

	return groups;
}

void AltStructsSynthesizer::AddTransitionsRelatedPositionIfNotAdded(Petri_Net& lbfNet, int positionIndex, vector<int>& transGroup)
{
	for (int tIndex = 0; tIndex < lbfNet.GetNumberOfTransitions(); tIndex++)
	{
		int ptRelation = lbfNet.GetElementMatrixD(positionIndex, tIndex);

		if (ptRelation != 0)
		{
			if (std::find(transGroup.begin(), transGroup.end(), tIndex) == transGroup.end())
			{
				transGroup.push_back(tIndex);
			}
		}
	}
}

void AltStructsSynthesizer::AddPositionsRelatedTransitionIfNotAdded(Petri_Net& lbfNet, int transitionIndex, vector<int>& posGroup)
{
	for (int pIndex = 0; pIndex < lbfNet.GetNumberOfPositions(); pIndex++)
	{
		int ptRelation = lbfNet.GetElementMatrixD(pIndex, transitionIndex);

		if (ptRelation != 0)
		{
			if (std::find(posGroup.begin(), posGroup.end(), pIndex) == posGroup.end())
			{
				posGroup.push_back(pIndex);
			}
		}
	}
}

Petri_Net* AltStructsSynthesizer::Union(SynthesysVector *PositionsProgramm, SynthesysVector *TransitionsProgramm, Petri_Net *PrimitiveNet, int *pnUniteOperationsCount)
{
	// Проверка входных параметров
	if (!PositionsProgramm
		|| !TransitionsProgramm
		|| !PrimitiveNet){
		return NULL;
	}

	// Эти массивы нужны для статистики!!!
	vector<int> unionPositions;
	vector<int> unionTransitions;

	// Создать новую сеть, копию примитивной
	Petri_Net *equivalentNet = new Petri_Net();
	equivalentNet->GetClone(PrimitiveNet, false);

	// Максимальный элемент программы синтеза - количество объединений
	int nPositionsUnionCount = SynthesisProgrammGenerator::MaxVectorElement(*PositionsProgramm);

	for (int i = 0; i < nPositionsUnionCount; i++)
	{
		unionPositions = GetUnionElements(PositionsProgramm, i+1);

		if (unionPositions.size() > 1)
		{
			equivalentNet->UnionPosition(unionPositions);
		}
	}

	int nTransitionsUnionCount = SynthesisProgrammGenerator::MaxVectorElement(*TransitionsProgramm);

	for (int i = 0; i < nTransitionsUnionCount; i++)
	{
		unionTransitions = GetUnionElements(TransitionsProgramm, i+1);

		if (unionTransitions.size() > 1)
		{
			equivalentNet->UnionTransition(unionTransitions);
		}
	}
	
	*pnUniteOperationsCount += GetUniteOperationsCount(unionPositions) + GetUniteOperationsCount(unionTransitions);

	return equivalentNet;
}

vector<int> AltStructsSynthesizer::GetUnionElements(SynthesysVector *Programm, int index)
{
	vector<int> unionElements;

	for (int j = 0; j < Programm->size(); j++)
	{
		if (index == Programm->at(j))
		{
			unionElements.push_back(j);
		}
	}

	return unionElements;
}

int AltStructsSynthesizer::GetUniteOperationsCount(vector<int> &UniteVector)
{
	int nCount = 0;

	for (int i = 0; i < UniteVector.size(); i++){
		nCount += UniteVector.at(i) - 1;
	}

	return nCount;
}

bool AltStructsSynthesizer::LoopRestrictionPass(
	SynthesysVector &TransitionsProgramm,
	SynthesysVector &PositionsProgramm)
{
	if ((TransitionsProgramm.size() * 2) != PositionsProgramm.size()){
		__debugbreak();
	}

	// рассмотреть все возможные пары объединений переходов
	for (int i = 0; i < TransitionsProgramm.size() - 1; i++){
		for (int j = i + 1; j < TransitionsProgramm.size(); j++){
			// при объединении переходов ...
			if (TransitionsProgramm[i] == TransitionsProgramm[j]){

				// не допускать объединение четных позиций с нечетными
				if (PositionsProgramm[i*2] == PositionsProgramm[j*2 + 1]
					|| PositionsProgramm[i*2 + 1] == PositionsProgramm[j*2]){
					return false;
				}
			}
		}
	}

	return true;
}

