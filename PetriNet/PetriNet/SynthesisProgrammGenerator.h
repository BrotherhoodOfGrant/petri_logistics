/**
* @file SynthesisProgrammGenerator.h
* ����������� ������ ��������� �������� �������
* @author Lena @date 02.11.2015
*/

#pragma once

class SynthesisProgrammGenerator
{
public:
	SynthesisProgrammGenerator();
	~SynthesisProgrammGenerator();
		

	/**
	* ������������� ����������
	* @param[in] nVectorSize - ������ �������
	* @param[in] Restrictions - ������ �����������
	*/
	SynthesisProgrammGenerator(RestrictionsfVector &Restrictions);
		

	/**
	* �������� ��������� ��������� ������� �� ��������
	* @param[in] SynthesisProgramm - ������, ������� ����� ��������
	*/
	bool GetNextCounterSynthesisProgramm(SynthesysVector &SynthesisProgramm);

	/**
	* �������� ��������� � �������� ���������
	*/
	void Reset();
	
	/**
	* ����� ������������ ������� �������
	* @param[in] ProgSynthesys - ������������� ������
	* @param[in] nMaxIndex - ������������ ����������� ����� �������� (0 - ������ �������)
	*/
	static int MaxVectorElement(SynthesysVector &ProgSynthesys, UINT nMaxIndex = 0);

private:
	
	/**
	* ������� �� �� ������� ������� ������� ������������� ��������
	* @param[in] Vector - ������������� ������
	* @param[in] nStartIndex - ������ ������� �������� �� �������
	* @param[in] nSize - ����� �������
	*/
	bool IsMatch(SynthesysVector &Vector, int nStartIndex, int nSize);

	/**
	* �������� �� ��������� ������� ����������
	* @param[in] ProgSynthesys - ������������� ������
	*/
	bool IsEnable(SynthesysVector &ProgSynthesys);
		

	/**
	* ������������� ��������� ������� ��� ������ �������
	* @return true - ������ �������
	* @remarks �� ������������� � ��������� �����, ���������� �� 
	* ������� ����������� ����������� ��� ������ �����������
	*/
	bool GenerateSynthsisProgrammCounter();

	//////////////////////////////////////////////////////////////////////////

	// ������ �����������
	RestrictionsfVector m_RestrictionsVector;

	int m_nElementsCount;
			

	//////////////////////////////////////////////////////////////////////////
	// ���������� ���������

	// ������ ������������ �������� ��������
	SynthesysVector m_MaxValues;

	// ������� �������� ��������
	SynthesysVector m_FlexibleCounter;

	// ���� ��������
	bool m_fCarry;

	// ������ �������� �������, � ������� ��� �������
	UINT m_nCarryIndex = 0;

	// ���� ������������
	bool m_fOverflow = false;
};

