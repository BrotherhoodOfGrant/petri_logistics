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
	static Petri_Net* Separate(_In_ Petri_Net& lbfNet, _Out_ Matrix** tensor, _Out_opt_ UINT * pnCountDecompositedPos = NULL);
	static void PrintNet(Petri_Net * pNet);
private:
	LbfToPrimitiveSeparator();
	~LbfToPrimitiveSeparator();


	static Petri_Net * GeneratePrimitivesNet(_In_ Petri_Net& lbfNet, _Out_ Petri_Net ** ppSizedLbfNet, _Out_ UINT * pnCountDecompositedPos);
	static Matrix * BuildTensor(_In_ Petri_Net * pLbfNetSized, _In_ Petri_Net * pPrimitivesNet);
	static bool isUsePosInTransition(int ElementMatrixD);

};

