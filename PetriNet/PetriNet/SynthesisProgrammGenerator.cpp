/**
* @file SynthesisProgrammGenerator.cpp
* Реализация класса генерации программ синтеза
* @author Lena @date 02.11.2015
*/

#include "stdafx.h"
#include "SynthesisProgrammGenerator.h"

struct SSynMeta{

	SSynMeta()
		: m_nCurrentValue(1), m_nMaxValue(1){}

	SSynMeta(int nCurrentValue, int nMaxValue)
		: m_nCurrentValue(nCurrentValue), m_nMaxValue(nMaxValue){}

	int m_nCurrentValue;

	int m_nMaxValue;
};

void PrintVector(SynthesysVector &V)
{
	for(UINT j = 0; j < V.size(); j++){
		printf("%d ", V[j]);
	}
	printf("\n");
}

SynthesisProgrammGenerator::SynthesisProgrammGenerator()
{
}

SynthesisProgrammGenerator::SynthesisProgrammGenerator(RestrictionsfVector &Restrictions)
	: m_RestrictionsVector(Restrictions)
{
	int nElementsCount = 0;
	for (unsigned int i = 0; i < Restrictions.size(); i++){
		nElementsCount += Restrictions[i];
	}
		
	for (int i = 0; i < nElementsCount; i++){
		
		m_FlexibleCounter.push_back(1);
		m_MaxValues.push_back(2);
	}

	m_MaxValues[0] = 1;		
	m_nElementsCount = nElementsCount;
}


SynthesisProgrammGenerator::~SynthesisProgrammGenerator()
{
}

// Найти максимальный элемент вектора
int SynthesisProgrammGenerator::MaxVectorElement(SynthesysVector &ProgSynthesis, UINT nMaxIndex)
{
	int nLimit = 0;
	if (nMaxIndex && (nMaxIndex < ProgSynthesis.size())){
		nLimit = nMaxIndex;
	}
	else{
		nLimit = ProgSynthesis.size();
	}

	int nMax = 0;
	for (int i = 0; i < nLimit; i++){
		if (ProgSynthesis[i] > nMax){
			nMax = ProgSynthesis[i];
		}
	}
	return nMax;
}

bool SynthesisProgrammGenerator::IsMatch(SynthesysVector &Vector, int nStartIndex, int nSize)
{
	bool fMatch = false;

	if (nSize <= 1){
		return false;
	}

	// Сравнить попарно все элементы участка вектора
	for (int i = 0; i < nSize - 1; i++){
		for (int j = i + 1; j < nSize; j++){
			if (Vector[i + nStartIndex] == Vector[j + nStartIndex]){
				return true;
			}
		}
	}

	return fMatch;
}

bool SynthesisProgrammGenerator::IsEnable(SynthesysVector &ProgSynthesys)
{
	bool fUnable = false;
	int nCurrentIndex = 0;

	for (unsigned int i = 0; i < m_RestrictionsVector.size(); i++){

		// Если есть одинаковые числа в рамках группы, вектор не подходит
		if (IsMatch(ProgSynthesys, nCurrentIndex, m_RestrictionsVector[i])){
			return false;
		}

		// Переход к следующей группе
		nCurrentIndex += m_RestrictionsVector[i];
	}

	return true;
}

void SynthesisProgrammGenerator::Reset()
{
	// Заново  инициализировать вектора
	for (UINT i = 0; i < m_FlexibleCounter.size(); i++){
		m_FlexibleCounter[i] = 1;
		m_MaxValues[i] = 2;
	}
	m_MaxValues[0] = 1;

	// Сбросить флаги
	m_fCarry = false;
	m_nCarryIndex = 0;
	m_fOverflow = false;
}



bool SynthesisProgrammGenerator::GetNextCounterSynthesisProgramm(SynthesysVector &SynthesisProgramm)
{
	// Пока будут доступны новые программы синтеза ...
	while (GenerateSynthsisProgrammCounter()){
		
		// искать допустимую
		if (IsEnable(m_FlexibleCounter)){
			SynthesisProgramm = m_FlexibleCounter;
			return true;
		}		
	}

	return false;
}

bool SynthesisProgrammGenerator::GenerateSynthsisProgrammCounter()
{
	while (!m_fOverflow){

		m_fCarry = false;

		// Инкрементировать младший разряд счетчика
		m_FlexibleCounter[m_FlexibleCounter.size() - 1]++;

		// Проверить разряды на переполнение
		for (UINT i = m_FlexibleCounter.size() - 1; i > 0; i--){

			// Если текущее значение разряда, больше 
			// чем, чем указано в ограничивающем векторе, зафиксировать перенос
			if (m_FlexibleCounter[i] > m_MaxValues[i]){

				// Сбросить текущий разряд в 1
				m_FlexibleCounter[i] = 1;

				// Увеличить значение в предыдущем разряде
				m_FlexibleCounter[i - 1]++;

				m_fCarry = true;

				// Запомнить разряд, в котором произошел перенос
				m_nCarryIndex = i;

				// При переполнении во втором разряде счет прекращается
				// зафиксировать переполнение
				if (i == 1){
					m_fOverflow = true;
					break;
				}
			}
			else{
				// в случае переноса пересчитать ограничивающий вектор для разрядов старше разряда с переносом включительно
				if (m_fCarry){
					int nNewMaxValue = MaxVectorElement(m_FlexibleCounter, m_nCarryIndex) + 1;
					for (UINT j = m_nCarryIndex; j < m_FlexibleCounter.size(); j++){
						m_MaxValues[j] = nNewMaxValue;
					}
				}
				// Вектор получен
				return true;
			}
		}		
	}

	return false;
}

