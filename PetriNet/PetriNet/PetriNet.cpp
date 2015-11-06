// PetriNet.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	String filePath;
	String resultDir;
	
	vector<Petri_Net*>* altNets1 = AltStructsSynthesizer::Synthesise(NULL, NULL);


	if (argc > 2)
	{
		filePath = argv[0];
		resultDir = argv[1];
	}
	else
	{
		printf("Программа запускается с параметрами командной строки : <путь к xml - файлу с описанием исходной сети> <путь к папке для результирующих файлов>");
		return -1;
	}

	// TODO Загрузка сети из xml-файла Артем и Илья
	Petri_Net* srcNet = PetriNetSerializer::Load(filePath);

	// TODO Разбиение на ЛБФ Андрей и Павел
	Petri_Net* lbfNet = SrcToLbfSeparator::Separate(*srcNet);

	// TODO Разбиение на примитивы и формирование тензора Кирилл и Андрей
	Matrix* tensor;

	Petri_Net* primitiveNet = LbfToPrimitiveSeparator::Separate(*lbfNet, tensor);

	// TODO Синтез альтернативных моделей Егор, Лена, Кристина
	vector<Petri_Net*>* altNets = AltStructsSynthesizer::Synthesise(lbfNet, primitiveNet);

	// TODO Преобразование в исходную систему координат Кирилл и Андрей
	InverseTransformer::Transform(*altNets, *tensor);

	// TODO Проверка эквивалентности Дмитрий
	EquivalenceChecker::Check(*srcNet, *altNets);

	// TODO Сохранение эквивалентных сетей в xml-файлы Артем и Илья
	for (int i = 0; i < altNets->size(); i++)
	{
		//Ostringstream stringStream;
		//stringStream << resultDir << "\\" << i << ".xml";
		//String savePath = stringStream.str();
		//PetriNetSerializer::Save(savePath, (altNets[i]));
	}

	//TODO запись в файл данных для построения графиков


	return 0;
}

