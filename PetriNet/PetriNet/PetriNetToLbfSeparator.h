/**
* @file PetriNetToLbfSeparator.h
* ����������� ������, ������������ ���������� �������� ���� ����� �� ���
* @author ... @date 02.11.2015
*/

#pragma once

class PetriNetToLbfSeparator
{
public:
	PetriNetToLbfSeparator();
	~PetriNetToLbfSeparator();

	// ��������� ���������� �������� ���� ���� �� ���
	Petri_Net *Separate(_In_ Petri_Net *SrcNet);
};

