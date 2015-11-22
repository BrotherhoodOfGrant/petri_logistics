/**
* @file PetriNetSerializer.h
* Определение класса сериализации/десериализации сети Петри
* @author ... @date 02.11.2015
*/
#include <fstream>
#include <iostream>
#pragma once
#define BUFFER_SIZE (1024*64)
static class PetriNetSerializer
{
public:
	/**
	* Загрузка СП-структуры из xml-файла
	* @param[in] sFilePath - Путь к xml-файлу
	* @result - СП-структура
	*/
	static Petri_Net *Load(_In_ String sFilePath);
	/**
	* Сохранение СП-структуры в xml-файл
	* @param[in] sFilePath - Путь к xml-файлу
	* @param[in] net - СП-структура
	*/
	static void Save(_In_ String sFilePath, _In_ Petri_Net &Petri);
private:
	PetriNetSerializer();
	~PetriNetSerializer();
};