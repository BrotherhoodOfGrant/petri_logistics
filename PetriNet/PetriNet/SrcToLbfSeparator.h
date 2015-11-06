/**
* @file PetriNetToLbfSeparator.h
* Определение класса, выполняющего разделение исходной сети Петри на ЛБФ
* @author ... @date 02.11.2015
*/

#pragma once

static class SrcToLbfSeparator
{
public:
	// Выполнить разделение исходной сети Петр на ЛБФ
	/**
	* Преобразование исходной СП-структуры в СП-структуру, представляющую ЛБФ
	* @param[in] srcNet - Исходная СП-структура
	* @result - СП-структура, представляющая ЛБФ
	*/
	static Petri_Net *Separate(_In_ Petri_Net &srcNet);

private:
	SrcToLbfSeparator();
	~SrcToLbfSeparator();
};

