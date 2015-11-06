/**
* @file PetriNetToLbfSeparator.h
* ����������� ������, ������������ ���������� �������� ���� ����� �� ���
* @author ... @date 02.11.2015
*/

#pragma once

static class SrcToLbfSeparator
{
public:
	// ��������� ���������� �������� ���� ���� �� ���
	/**
	* �������������� �������� ��-��������� � ��-���������, �������������� ���
	* @param[in] srcNet - �������� ��-���������
	* @result - ��-���������, �������������� ���
	*/
	static Petri_Net *Separate(_In_ Petri_Net &srcNet);

private:
	SrcToLbfSeparator();
	~SrcToLbfSeparator();
};

