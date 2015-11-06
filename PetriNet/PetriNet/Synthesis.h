/**
* @file Synthesys.h
* ����������� ������, ������������ ������ ��-��������
* @author Lena @date 02.11.2015
*/


#pragma once

typedef vector<int> SynthesysVector;
typedef vector<int> LbfVector;

class Synthesis
{
public:
	Synthesis();
	~Synthesis();

	/** 
	* ������������� ��������� � �������� �� �� ��������� ����
	* @param[in] LbfNet - ����, �������������� ���
	* @param[in] LbfNet - ����������� ����
	*/
	static vector<Petri_Net*>* Synthesise(Petri_Net &LbfNet, Petri_Net &PrimitiveNet);

};

