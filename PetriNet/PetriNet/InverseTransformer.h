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
	static bool Transform(_Inout_ AlternativeNest &altNets, _In_ Matrix &tensor);
	static bool Reduce(_Inout_ Petri_Net * pAltNet);

private:
	InverseTransformer();
	~InverseTransformer();

	static bool Convert(_Inout_ Petri_Net * pAltNet, _In_ Matrix &tensor);
	

};

