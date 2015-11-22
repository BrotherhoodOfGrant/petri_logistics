/**
* @file PetriNetToLbfSeparator.cpp
* Реализация класса, выполняющего разделение исходной сети Петри на ЛБФ
* @author ... @date 02.11.2015
*/

#include "stdafx.h"

Petri_Net * SrcToLbfSeparator::Separate(_In_ Petri_Net *srcNet, _In_ bool newMethod)
{
	//srcNet->Separate();
	srcNet->GetMToLBF(newMethod);

	Petri_Net *Clone = new Petri_Net();
	Clone->GetClone(srcNet, false);

	if (Clone->Separate())
	{
		return Clone;
	}
	else
		return NULL;
}

SrcToLbfSeparator::SrcToLbfSeparator()
{
}

SrcToLbfSeparator::~SrcToLbfSeparator()
{
}