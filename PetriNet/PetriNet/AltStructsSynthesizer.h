/**
* @file Synthesys.h
* ����������� ������, ������������ ������ �������������� ��-��������
* @author ����, ����, �������� @date 02.11.2015
*/


#pragma once

typedef vector<int> SynthesysVector;
typedef vector<int> RestrictionsfVector;

// ���� ��� ���������� ����������� �� ����� � �������� �������
#define SYSNTHESIS_LOOP_RESTRICTION (0x00000001 << 0)

static class AltStructsSynthesizer
{
public:
	/**
	* ������ �������������� ��-��������
	* @param[in] LbfNet - ��-���������, �������������� ���
	* @param[in] PrimitiveNet - ��-���������, �������������� ����������� ����
	* @param[out] pUniteOoerationeVector - ������ ���������� �������� ����������� ��� ������ ����
	* @param[in] nAdditionalRestrictions - ������� ����� �������������� �����������
	* @result - ��������� �������������� ��-��������
	*/
	static AlternativeNest* Synthesise(
		Petri_Net *LbfNet, 
		Petri_Net *PrimitiveNet, 
		vector<int> *pUniteOoerationeVector = NULL,
		DWORD nAdditionalRestrictions = 0);

	/**
	* ���������� ������ ���� �����
	*/
	static void AltStructsSynthesizer::PrintPetriNet(Petri_Net& net);

private:
	/**
	* ���������, ����������� ������ ��������� � �������
	*/
	struct TransitionPositionGroup
	{
	public:
		vector<int>* Transitions;
		vector<int>* Positions;
	};

	/**
	* ��������� �������, ������������ ������������� ��������� � ������� �� �������
	* @param[in] lbfNet - ��-���������
	* @result - ������ ����� ������� � ���������
	*/
	static vector<TransitionPositionGroup>* GetTransitionPositionGroups(Petri_Net &net);

	/**
	* ���������� � ������ ������� ���� ���������, ����������� � �������� �������, ���� ����� 
	* ������ �������� ��� �� ��������
	* @param[in] lbfNet - ��-���������
	* @param[in] positionIndex - ����� �������
	* @param[inout] transGroup - ������ ������� ���������
	*/
	static void AddTransitionsRelatedPositionIfNotAdded(_In_ Petri_Net& net, _In_ int positionIndex, _Inout_ vector<int> &transGroup);
	
	/**
	* ���������� � ������ ������� ���� �������, ����������� � ��������� ��������, ���� �����
	* ����� ������� ��� �� ��������
	* @param[in] lbfNet - ��-���������
	* @param[in] transitionIndex - ����� ��������
	* @param[inout] posGroup - ������ ������� �������
	*/
	static void AddPositionsRelatedTransitionIfNotAdded(_In_ Petri_Net& net, _In_ int transitionIndex, _Inout_ vector<int> &posGroup);
	
	/**
	* ���������� ������� � ������� �������� ��������� �������
	* @param[in] PositionsProgramm - ��������� ������� ��� �������
	* @param[in] TransitionsProgramm - ��������� ������� ��� ���������
	* @param[in] PrimitiveNet - ����������� ����, �� ������ ������� ����� ��������� ����� ����
	*/
	static Petri_Net* Union(SynthesysVector *PositionsProgramm, SynthesysVector *TransitionsProgramm, Petri_Net *PrimitiveNet, int *pnUniteOperationsCount);

	/**
	* �������� ��������, ����������� � �������� ������������
	* @param[in] Programm - ��������� �������
	* @param[in] index - ����� �������� ������������
	*/
	static vector<int> AltStructsSynthesizer::GetUnionElements(SynthesysVector *Programm, int index);

	/**
	* �������� ���������� �������� ����������� �� ������� �����������
	* @param[in] UniteVector - ������ �� ������, ������� ����� ��������
	*/
	static int GetUniteOperationsCount(vector<int> &UniteVector);

	/**
	* �������� �� ��������� ������� ����������� �� �����
	* @param[in] TransitionsProgramm - ��������� ������� ��� ���������
	* @param[in] PositionsProgramm - ��������� ������� ��� �������
	*/
	static bool LoopRestrictionPass(
		SynthesysVector &TransitionsProgramm,
		SynthesysVector &PositionsProgramm);
	

	AltStructsSynthesizer();
	~AltStructsSynthesizer();
};

