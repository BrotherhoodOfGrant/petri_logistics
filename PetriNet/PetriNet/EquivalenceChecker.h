/**
* @file InverseTransformer.h
* Класс, выполняющий проверку эквивалентности альтернативных СП-структур исходной СП-структуре
* @author ... @date 02.11.2015
*/

#pragma once
static class EquivalenceChecker
{
public:
	/**
	* Проверка эквивалентности альтернативных СП-структур исходной СП-структуре
	* @param[in] srcNet - Исходная СП-структура
	* @param[inout] altNets - Коллекция проверяемых СП-структур. СП-структуры, которые не прошли проверку, удаляются из коллекции.
	*/
	static void Check(_In_ Petri_Net &srcNet, _Inout_ vector<Petri_Net*> &altNets);
private:
	EquivalenceChecker();
	~EquivalenceChecker();
};

