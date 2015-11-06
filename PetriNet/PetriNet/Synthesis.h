/**
* @file Synthesys.h
* Определение класса, выполняющего синтез СП-структур
* @author Lena @date 02.11.2015
*/


#pragma once

typedef vector<int> SynthesysVector;
typedef vector<int> LbfVector;

class Synthesis
{
public:
	Synthesis();
	~Synthesis();

	/** 
	* Синтезировать структуры и передать их на следующий этап
	* @param[in] LbfNet - Сеть, представляющая ЛБФ
	* @param[in] LbfNet - Примитивная сеть
	*/
	static vector<Petri_Net*>* Synthesise(Petri_Net &LbfNet, Petri_Net &PrimitiveNet);

};

