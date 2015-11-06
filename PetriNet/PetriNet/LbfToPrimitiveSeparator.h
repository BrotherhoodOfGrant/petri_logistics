/**
* @file LbfToPrimitiveSeparator.h
* �����, ����������� �������������� ��-���������, �������������� ���, � ��-���������, �������������� ����������� ��������� 
* @author ... @date 02.11.2015
*/

#pragma once
static class LbfToPrimitiveSeparator
{
public:
	/**
	* �������������� ��-���������, �������������� ���, � ��-���������, �������������� ����������� ��������� 
	* @param[in] lbfNet - ��-���������, �������������� ���
	* @param[out] tensor - ������ ��������� ��������������
	* @result - ��-���������, �������������� ����������� ��������� 
	*/
	static Petri_Net* Separate(_In_ Petri_Net& lbfNet, _Out_ Matrix* tensor);
private:
	LbfToPrimitiveSeparator();
	~LbfToPrimitiveSeparator();
};

