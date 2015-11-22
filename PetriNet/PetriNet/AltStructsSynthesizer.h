/**
* @file Synthesys.h
* Определение класса, выполняющего синтез альтернативных СП-структур
* @author Егор, Лена, Кристина @date 02.11.2015
*/


#pragma once

typedef vector<int> SynthesysVector;
typedef vector<int> RestrictionsfVector;

// флаг для применения ограничений на петли в процессе синтеза
#define SYSNTHESIS_LOOP_RESTRICTION (0x00000001 << 0)

static class AltStructsSynthesizer
{
public:
	/**
	* Синтез альтернативных СП-структур
	* @param[in] LbfNet - СП-структура, представляющая ЛБФ
	* @param[in] PrimitiveNet - СП-структура, представляющая примитивную сеть
	* @param[out] pUniteOoerationeVector - массив количества операций объединения для каждой сети
	* @param[in] nAdditionalRestrictions - битовая маска дополнительных ограничений
	* @result - Коллекция альтернативных СП-структур
	*/
	static AlternativeNest* Synthesise(
		Petri_Net *LbfNet, 
		Petri_Net *PrimitiveNet, 
		vector<int> *pUniteOoerationeVector = NULL,
		DWORD nAdditionalRestrictions = 0);

	/**
	* Отладочная печать сети Петри
	*/
	static void AltStructsSynthesizer::PrintPetriNet(Petri_Net& net);

private:
	/**
	* Структура, описывающая группу переходов и позиций
	*/
	struct TransitionPositionGroup
	{
	public:
		vector<int>* Transitions;
		vector<int>* Positions;
	};

	/**
	* Получение вектора, описывающего распределение переходов и позиций по группам
	* @param[in] lbfNet - СП-структура
	* @result - Вектор групп позиций и переходов
	*/
	static vector<TransitionPositionGroup>* GetTransitionPositionGroups(Petri_Net &net);

	/**
	* Добавление в вектор номеров всех переходов, относящихся к заданной позиции, если номер 
	* такого перехода еще не добавлен
	* @param[in] lbfNet - СП-структура
	* @param[in] positionIndex - номер позиции
	* @param[inout] transGroup - вектор номеров переходов
	*/
	static void AddTransitionsRelatedPositionIfNotAdded(_In_ Petri_Net& net, _In_ int positionIndex, _Inout_ vector<int> &transGroup);
	
	/**
	* Добавление в вектор номеров всех позиций, относящихся к заданному переходу, если номер
	* такой позиции еще не добавлен
	* @param[in] lbfNet - СП-структура
	* @param[in] transitionIndex - номер перехода
	* @param[inout] posGroup - вектор номеров позиций
	*/
	static void AddPositionsRelatedTransitionIfNotAdded(_In_ Petri_Net& net, _In_ int transitionIndex, _Inout_ vector<int> &posGroup);
	
	/**
	* Объединить вершины и позиции согласно программе синтеза
	* @param[in] PositionsProgramm - Программа синтеза для позиций
	* @param[in] TransitionsProgramm - Программа синтеза для переходов
	* @param[in] PrimitiveNet - Примитивная сеть, на основе которой будут строиться новые сети
	*/
	static Petri_Net* Union(SynthesysVector *PositionsProgramm, SynthesysVector *TransitionsProgramm, Petri_Net *PrimitiveNet, int *pnUniteOperationsCount);

	/**
	* Выделить элементы, относящиеся к текущему подмножеству
	* @param[in] Programm - Программа синтеза
	* @param[in] index - Номер текущего подмножества
	*/
	static vector<int> AltStructsSynthesizer::GetUnionElements(SynthesysVector *Programm, int index);

	/**
	* Получить количество операций объединения по вектору объединений
	* @param[in] UniteVector - ссылка на вектор, который будет заполнен
	*/
	static int GetUniteOperationsCount(vector<int> &UniteVector);

	/**
	* Проходит ли программа синтеза ограничение на петли
	* @param[in] TransitionsProgramm - Программа синтеза для переходов
	* @param[in] PositionsProgramm - Программа синтеза для позиций
	*/
	static bool LoopRestrictionPass(
		SynthesysVector &TransitionsProgramm,
		SynthesysVector &PositionsProgramm);
	

	AltStructsSynthesizer();
	~AltStructsSynthesizer();
};

