/**
* @file Synthesys.h
* Реализация класса, выполняющего синтез СП-структур
* @author Lena @date 02.11.2015
*/


#include "stdafx.h"
#include "SynthesisProgrammGenerator.h"

AltStructsSynthesizer::AltStructsSynthesizer()
{
}


AltStructsSynthesizer::~AltStructsSynthesizer()
{
}

vector<Petri_Net*>* AltStructsSynthesizer::Synthesise(Petri_Net *LbfNet, Petri_Net *PrimitiveNet)
{
	

	// TODO: Разделить позиции из ЛБФ по группам, 
	// сформировать вектор ограничений для переходов

	// Для отладки: 3 ЛБФ, разложенные на 6 примитивов, которых оказалось очень много. 3 примитива

	

	LbfVector TransitionRestrictions = { 1, 2, 3 };
	LbfVector PositionRestrictions = { 4, 2 };

	SynthesisProgrammGenerator PositionsGenerator(PositionRestrictions);
	SynthesisProgrammGenerator TransitionsGenerator(TransitionRestrictions);

	SynthesysVector TransitionsProgramm;
	SynthesysVector PositionsProgramm;
	
	int nCount = 0;
	while (PositionsGenerator.GetNextTreeSynthesisProgramm(PositionsProgramm)){
		nCount++;
	}

	while (TransitionsGenerator.GetNextSynthesisProgramm(TransitionsProgramm)){
		while (PositionsGenerator.GetNextSynthesisProgramm(PositionsProgramm)){

			// TODO: Объединение позиций и переходов согласно векторам  TransitionsProgramm + PositionsProgramm

			// it's a trap!
			int a = 0;
		}
	}

	return NULL;
}

Petri_Net* AltStructsSynthesizer::Union(SynthesysVector *PositionsProgramm, SynthesysVector *TransitionsProgramm, Petri_Net *PrimitiveNet)
{
	vector<int> unionPositions;
	vector<int> unionTransitions;

	Petri_Net equivalentNet = *PrimitiveNet;

	for (int i = 0; i < PositionsProgramm->size(); i++)
	{
		unionPositions = GetUnionElements(PositionsProgramm, i);

		if (unionPositions.size() > 1)
		{		
			for (int k = 0; k < unionPositions.size(); k + 2)
			{
				//equivalentNet.Union( k, k + 1 );
			}	

			//?acaaeaiea aa?oei

		}
	}

	for (int i = 0; i < TransitionsProgramm->size(); i++)
	{
		unionTransitions = GetUnionElements(TransitionsProgramm, i);

		if (unionTransitions.size() > 1)
		{
			for (int k = 0; k < unionTransitions.size(); k + 2)
			{
				//equivalentNet.Union( k, k + 1 );
			}

			//?acaaeaiea aa?oei

		}
	}


	return &equivalentNet;
	
}

vector<int> AltStructsSynthesizer::GetUnionElements(SynthesysVector *Programm, int index)
{
	vector<int> unionElements;

	int currentValue = Programm->at(index);

	unionElements.push_back(index);

	for (int j = 0; j < Programm->size(); j++)
	{
		if (currentValue == Programm->at(j))
		{
			unionElements.push_back(j);
		}

	}

	return unionElements;

}
