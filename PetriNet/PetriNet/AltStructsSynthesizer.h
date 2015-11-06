/**
* @file Synthesys.h
* Определение класса, выполняющего синтез альтернативных СП-структур
* @author Lena @date 02.11.2015
*/


#pragma once

typedef vector<int> SynthesysVector;
typedef vector<int> LbfVector;

static class AltStructsSynthesizer
{
public:
	/**
	* Синтез альтернативных СП-структур
	* @param[in] LbfNet - СП-структура, представляющая ЛБФ
	* @param[in] PrimitiveNet - СП-структура, представляющая примитивную сеть
	* @result - Коллекция альтернативных СП-структур
	*/
	static vector<Petri_Net*>* Synthesise(Petri_Net *LbfNet, Petri_Net *PrimitiveNet);

private:
	AltStructsSynthesizer();
	~AltStructsSynthesizer();

	static Petri_Net* Union(SynthesysVector *PositionsProgramm, SynthesysVector *TransitionsProgramm, Petri_Net *PrimitiveNet);
	static vector<int> AltStructsSynthesizer::GetUnionElements(SynthesysVector *Programm, int index);
	
};

