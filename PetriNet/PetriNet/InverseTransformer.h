/**
* @file InverseTransformer.h
* Класс, выполняющий преобразование СП-структур в исходную систему координат
* @author ... @date 02.11.2015
*/

#pragma once
static class InverseTransformer
{
public:
	/**
	* Перобразование СП-структур в исходную систему координат
	* @param[inout] altNets - Коллекция преобразуемых СП-структур
	* @param[in] tensor - Тензор преобразования
	*/
	static void Transform(_Inout_ vector<Petri_Net*> &altNets, _In_ Matrix &tensor);

private:
	InverseTransformer();
	~InverseTransformer();
};

