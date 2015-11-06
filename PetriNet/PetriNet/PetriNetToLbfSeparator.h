/**
* @file PetriNetToLbfSeparator.h
* Определение класса, выполняющего разделение исходной сети Петри на ЛБФ
* @author ... @date 02.11.2015
*/

#pragma once

class PetriNetToLbfSeparator
{
public:
	PetriNetToLbfSeparator();
	~PetriNetToLbfSeparator();

	// Выполнить разделение исходной сети Петр на ЛБФ
	Petri_Net *Separate(_In_ Petri_Net *SrcNet);
};

