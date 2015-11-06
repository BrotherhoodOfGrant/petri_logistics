/**
* @file LbfToPrimitiveSeparator.h
* Класс, выполняющий преобразование СП-структуры, представляющей ЛБФ, в СП-структуру, представляющую примитивные фрагменты 
* @author ... @date 02.11.2015
*/

#pragma once
static class LbfToPrimitiveSeparator
{
public:
	/**
	* Преобразование СП-структуры, представляющей ЛБФ, в СП-структуру, представляющую примитивные фрагменты 
	* @param[in] lbfNet - СП-структура, представляющая ЛБФ
	* @param[out] tensor - Тензор обратного преобразования
	* @result - СП-структура, представляющая примитивные фрагменты 
	*/
	static Petri_Net* Separate(_In_ Petri_Net& lbfNet, _Out_ Matrix* tensor);
private:
	LbfToPrimitiveSeparator();
	~LbfToPrimitiveSeparator();
};

