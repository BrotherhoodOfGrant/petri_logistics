/**
* @file SynthesisProgrammGenerator.h
* Определение класса генерации программ синтеза
* @author Lena @date 02.11.2015
*/

#pragma once

class SynthesisProgrammGenerator
{
public:
	SynthesisProgrammGenerator();
	~SynthesisProgrammGenerator();
		

	/**
	* Инициализация генератора
	* @param[in] nVectorSize - Размер вектора
	* @param[in] Restrictions - Вектор ограничений
	*/
	SynthesisProgrammGenerator(RestrictionsfVector &Restrictions);
		

	/**
	* Получить следующую программу синтеза из счетчика
	* @param[in] SynthesisProgramm - Вектор, который будет заполнен
	*/
	bool GetNextCounterSynthesisProgramm(SynthesysVector &SynthesisProgramm);

	/**
	* Сбросить генератор в исходное состояние
	*/
	void Reset();
	
	/**
	* Найти максимальный элемент вектора
	* @param[in] ProgSynthesys - Анализируемый вектор
	* @param[in] nMaxIndex - Максимальный учитываемый номер элемента (0 - вектор целиком)
	*/
	static int MaxVectorElement(SynthesysVector &ProgSynthesys, UINT nMaxIndex = 0);

private:
	
	/**
	* Имеются ли на данному отрезке вектора повторяющиеся элементы
	* @param[in] Vector - Анализируемый вектор
	* @param[in] nStartIndex - Индекс первого элемента на отрезке
	* @param[in] nSize - Длина отрезка
	*/
	bool IsMatch(SynthesysVector &Vector, int nStartIndex, int nSize);

	/**
	* Является ли программа синтеза допустимой
	* @param[in] ProgSynthesys - Анализируемый вектор
	*/
	bool IsEnable(SynthesysVector &ProgSynthesys);
		

	/**
	* сгенерировать программу синтеза при помощи вектора
	* @return true - вектор получен
	* @remarks Не рекомендуется к прочтению людам, страдающим от 
	* тяжелых психических заболеваний или чайной зависимости
	*/
	bool GenerateSynthsisProgrammCounter();

	//////////////////////////////////////////////////////////////////////////

	// Вектор ограничений
	RestrictionsfVector m_RestrictionsVector;

	int m_nElementsCount;
			

	//////////////////////////////////////////////////////////////////////////
	// Реализация счетчиком

	// Вектор максимальных значений разрядов
	SynthesysVector m_MaxValues;

	// Текущее значение счетчика
	SynthesysVector m_FlexibleCounter;

	// Флаг переноса
	bool m_fCarry;

	// Индекс младшего разряда, в котором был перенос
	UINT m_nCarryIndex = 0;

	// флаг переполнения
	bool m_fOverflow = false;
};

