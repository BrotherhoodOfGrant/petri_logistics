/**
* @file Synthesys.h
* ���������� ������, ������������ ������ ��-��������
* @author Lena @date 02.11.2015
*/


#include "stdafx.h"

#include "SynthesisProgrammGenerator.h"

Synthesis::Synthesis()
{
}


Synthesis::~Synthesis()
{
}

vector<Petri_Net*>* Synthesis::Synthesise(Petri_Net &LbfNet, Petri_Net &PrimitiveNet)
{
	SynthesisProgrammGenerator PositionsGenerator;
	SynthesisProgrammGenerator TransitionsGenerator;

	// TODO: ��������� ������� �� ��� �� �������, 
	// ������������ ������ ����������� ��� ���������

	// ��� �������: 3 ���, ����������� �� 6 ����������

	LbfVector TransitionRestrictions = {1, 2, 3};
	LbfVector PositionRestrictions = {2, 2, 2, 2, 2, 2};
	
	SynthesysVector TransitionsProgramm;
	SynthesysVector PositionsProgramm;

	PositionsGenerator.InitializeGenerator(12, PositionRestrictions);
	TransitionsGenerator.InitializeGenerator(6, TransitionRestrictions);

	while (TransitionsGenerator.GetNextSynthesisProgramm(TransitionsProgramm)){
		while (PositionsGenerator.GetNextSynthesisProgramm(PositionsProgramm)){

			// TODO: ����������� ������� � ��������� �������� ��������  TransitionsProgramm + PositionsProgramm

			// it's a trap!
			int a = 0;
		}
	}

	return NULL;
}
