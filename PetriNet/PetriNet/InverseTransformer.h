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
	static bool Transform(_Inout_ AlternativeNest &altNets, _In_ Matrix &tensor);
	static bool Reduce(_Inout_ Petri_Net * pAltNet);

private:
	InverseTransformer();
	~InverseTransformer();

	static bool Convert(_Inout_ Petri_Net * pAltNet, _In_ Matrix &tensor);
	

};

