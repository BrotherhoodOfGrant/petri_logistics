/**
* @file InverseTransformer.h
* �����, ����������� �������� ��������������� �������������� ��-�������� �������� ��-���������
* @author ... @date 02.11.2015
*/

#pragma once
static class EquivalenceChecker
{
public:
	/**
	* �������� ��������������� �������������� ��-�������� �������� ��-���������
	* @param[in] srcNet - �������� ��-���������
	* @param[inout] altNets - ��������� ����������� ��-��������. ��-���������, ������� �� ������ ��������, ��������� �� ���������.
	*/
	static void Check(_In_ Petri_Net &srcNet, _Inout_ vector<Petri_Net*> &altNets);
private:
	EquivalenceChecker();
	~EquivalenceChecker();
};

