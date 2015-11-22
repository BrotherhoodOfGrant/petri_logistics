// PetriNet.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

bool LbfToPrimitiveSeparatorTest()
{
	Petri_Net* primitiveNet;
	Petri_Net* lbfNet;
	Matrix* tensor;
	double daPrimitivesMatrix[] = { -1, 0, 1, 0, 0, -1, 0, 1 };
	double daTensorMatrix[] = { 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1 };

	lbfNet = new Petri_Net();
	if (!lbfNet)
	{
		return false;
	}

	lbfNet->AddPosition(1, 0, "P1");
	lbfNet->AddPosition(0, 1, "P2");
	lbfNet->AddPosition(0, 2, "P3");

	lbfNet->AddTransition(0, "T1");
	lbfNet->AddTransition(1, "T2");

	lbfNet->AddArc(1, 0, 0, true);
	lbfNet->AddArc(1, 0, 1, false);
	lbfNet->AddArc(1, 1, 1, true);
	lbfNet->AddArc(1, 1, 2, false);

	primitiveNet = LbfToPrimitiveSeparator::Separate(*lbfNet, &tensor);
	if (!primitiveNet || !tensor)
	{
		return false;
	}

	if (4 != primitiveNet->GetNumberOfPositions())
	{
		return false;
	}

	if (2 != primitiveNet->GetNumberOfTransitions())
	{
		return false;
	}

	for (UINT i = 0; i < primitiveNet->GetNumberOfPositions(); i++)
	{
		for (UINT j = 0; j < primitiveNet->GetNumberOfTransitions(); j++)
		{
			if (primitiveNet->GetElementMatrixD(j, i) != daPrimitivesMatrix[j + 2 * i])
			{
				return false;
			}
		}
	}

	if ((4 != tensor->get_count_col()) || (4 != tensor->get_count_row()))
	{
		return false;
	}

	for (UINT i = 0; i < tensor->get_count_col(); i++)
	{
		for (UINT j = 0; j < tensor->get_count_row(); j++)
		{
			if (tensor->get_value(i, j) != daTensorMatrix[i * tensor->get_count_col() + j])
			{
				return false;
			}
		}
	}

	return true;
}

bool InverseTransformerTest()
{
	return true;
}

bool ReduceTest()
{
	Petri_Net* lbfNet;

	lbfNet = new Petri_Net();
	if (!lbfNet)
	{
		return false;
	}

	lbfNet->AddPosition(1, 0, "P1");
	lbfNet->AddPosition(0, 1, "P2");
	lbfNet->AddPosition(0, 2, "P21");
	lbfNet->AddPosition(0, 3, "P3");

	lbfNet->AddTransition(0, "T1");
	lbfNet->AddTransition(1, "T2");

	lbfNet->AddArc(1, 0, 0, true);
	lbfNet->AddArc(1, 0, 1, false);
	lbfNet->AddArc(1, 0, 2, false);
	lbfNet->AddArc(1, 1, 1, true);
	lbfNet->AddArc(1, 2, 1, true);
	lbfNet->AddArc(1, 1, 3, false);
	
	if (!InverseTransformer::Reduce(lbfNet))
	{
		return false;
	}
	
	return true;
}

bool Tests()
{
	if (!LbfToPrimitiveSeparatorTest())
	{
		printf("- Тест модуля преобразования ЛБФ в примитивы не пройден\n");
	}
	else
	{
		printf("+ Тест модуля преобразования ЛБФ в примитивы пройден\n");
	}

	if (!InverseTransformerTest())
	{
		printf("- Тест модуля обратного преобразования не пройден\n");
	}
	else
	{
		printf("+ Тест модуля обратного преобразования пройден\n");
	}

	if (!ReduceTest())
	{
		printf("- Тест модуля редукции не пройден\n");
	}
	else
	{
		printf("+ Тест модуля редукции пройден\n");
	}
		  
	return true;
}

//#define PETRI_NET_TESTS

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Russian");
	String filePath;
	String resultDir;
	String pointsPath, pointsFileName = L"points.txt";
	vector<int> UniteOperationsVector;
	bool newMethod = true;
	
#ifdef PETRI_NET_TESTS

	Tests();
	_getch();
	return 0;

#endif

	if (argc >= 2)
	{
		filePath = argv[1];
		resultDir = argc == 2 || argv[2] == nullptr ? L"." : argv[2];
		pointsPath = resultDir + L"\\" + pointsFileName;
		
		//Здесь подставляем значение из командной строки
		newMethod = true;
	}
	else
	{
		printf("Программа запускается с параметрами командной строки : <путь к xml - файлу с описанием исходной сети> [<путь к папке для результирующих файлов>]");
		return -1;
	}

	// Загрузка сети из xml-файла (Артем и Илья)
	Petri_Net* srcNet = PetriNetSerializer::Load(filePath);
	printf("Загрузка исходной СП-структуры \"%ls\" выполнена.\n", filePath.c_str());

	// TODO Разбиение на ЛБФ (Андрей и Павел)
	Petri_Net* lbfNet = SrcToLbfSeparator::Separate(srcNet, newMethod);
	printf("Разбиение исходной СП-структуры на ЛБФ выполнено.\n");

	AltStructsSynthesizer::PrintPetriNet(*lbfNet);

	// Разбиение на примитивы и формирование тензора (Кирилл и Андрей)
	Matrix* tensor;

	Petri_Net* primitiveNet = LbfToPrimitiveSeparator::Separate(*lbfNet, &tensor);
	printf("Разбиение ЛБФ на примитивные фрагменты выполнено. Количество примитивных фрагментов - %d.\n", primitiveNet->GetNumberOfTransitions());

	AltStructsSynthesizer::PrintPetriNet(*primitiveNet );

	// Синтез альтернативных моделей (Егор, Лена, Кристина)
	printf("Начинается синтез альтернативных СП-структур...\n");
	AlternativeNest* altNets = AltStructsSynthesizer::Synthesise(lbfNet, primitiveNet, &UniteOperationsVector);
	printf("Синтез альтернативных СП-структур выполнен.\nКоличество синтезированных СП-структур - %d.\n", altNets->size());

	// Преобразование в исходную систему координат (Кирилл и Андрей)
	//InverseTransformer::Transform(*altNets, *tensor);
	printf("Преобразование альтернативных СП-структур в исходную систему координат выполнено.\n");

	// TODO Проверка эквивалентности (Дмитрий)
	printf("Начинается проверка эквивалентности альтернативных СП-структур...\n");
	EquivalenceChecker::Check(*srcNet, *altNets);
	printf("Проверка эквивалентности альтернативных СП-структур выполнена.\nКоличество эквивалентных СП-структур - %d.\n", altNets->size());

	// Сохранение эквивалентных сетей в xml-файлы (Артем и Илья)
	int i = 0;
	for (AlternativeNest::iterator NetsIterator = altNets->begin();
		NetsIterator != altNets->end();
		++NetsIterator, ++i)
	{
		String savePath = resultDir + L"\\AltNet_" + to_wstring(i) + L".xml";
		PetriNetSerializer::Save(savePath, **NetsIterator);
	}
	printf("Сохранение эквивалентных СП-структур в директорию \"%ls\" выполнено.\n", resultDir.c_str());

	// Запись в файл данных для построения графиков (Галя и Катя)
	printf("Начинается оценка критериев эквивалентных СП-структур для построения графиков...\n");
	PointsCreator::CreatePoints(altNets, UniteOperationsVector, pointsPath.c_str(), newMethod);
	printf("Оценка критериев эквивалентных СП-структур для построения графиков выполнена.\n");
	printf("Готово! Генерация эквивалентных СП-структур выполнена!\n");
	_getch();
	return 0;
}

