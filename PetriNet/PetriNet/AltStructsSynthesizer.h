/**
* @file Synthesys.h
* ����������� ������, ������������ ������ �������������� ��-��������
* @author Lena @date 02.11.2015
*/


#pragma once

typedef vector<int> SynthesysVector;
typedef vector<int> LbfVector;

static class AltStructsSynthesizer
{
public:
	/**
	* ������ �������������� ��-��������
	* @param[in] LbfNet - ��-���������, �������������� ���
	* @param[in] PrimitiveNet - ��-���������, �������������� ����������� ����
	* @result - ��������� �������������� ��-��������
	*/
	static vector<Petri_Net*>* Synthesise(Petri_Net *LbfNet, Petri_Net *PrimitiveNet);

private:
	AltStructsSynthesizer();
	~AltStructsSynthesizer();

	static Petri_Net* Union(SynthesysVector *PositionsProgramm, SynthesysVector *TransitionsProgramm, Petri_Net *PrimitiveNet);
	static vector<int> AltStructsSynthesizer::GetUnionElements(SynthesysVector *Programm, int index);
	
};

