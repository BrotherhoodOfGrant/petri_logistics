/**
* @file InverseTransformer.h
* �����, ����������� �������������� ��-�������� � �������� ������� ���������
* @author ... @date 02.11.2015
*/

#pragma once
static class InverseTransformer
{
public:
	/**
	* �������������� ��-�������� � �������� ������� ���������
	* @param[inout] altNets - ��������� ������������� ��-��������
	* @param[in] tensor - ������ ��������������
	*/
	static void Transform(_Inout_ vector<Petri_Net*> &altNets, _In_ Matrix &tensor);

private:
	InverseTransformer();
	~InverseTransformer();
};

