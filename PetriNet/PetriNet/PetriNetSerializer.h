/**
* @file PetriNetSerializer.h
* ����������� ������ ������������/�������������� ���� �����
* @author ... @date 02.11.2015
*/
#include <fstream>
#include <iostream>
#pragma once
#define BUFFER_SIZE (1024*64)
static class PetriNetSerializer
{
public:
	/**
	* �������� ��-��������� �� xml-�����
	* @param[in] sFilePath - ���� � xml-�����
	* @result - ��-���������
	*/
	static Petri_Net *Load(_In_ String sFilePath);
	/**
	* ���������� ��-��������� � xml-����
	* @param[in] sFilePath - ���� � xml-�����
	* @param[in] net - ��-���������
	*/
	static void Save(_In_ String sFilePath, _In_ Petri_Net &Petri);
private:
	PetriNetSerializer();
	~PetriNetSerializer();
};