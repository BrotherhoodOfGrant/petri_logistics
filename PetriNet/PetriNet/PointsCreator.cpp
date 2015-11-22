#include "stdafx.h"
#include "PointsCreator.h"

bool PointsCreator::OpenFile(LPCWSTR filePath, HANDLE &hFile)
{
	hFile = CreateFile(
		filePath,
		GENERIC_WRITE,
		NULL,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		hFile = NULL;
		return false;
	}
	else return true;
}

bool PointsCreator::CloseFile(HANDLE hFile)
{
	if (FAILED(CloseHandle(hFile)))
		return false;
	else return true;
}

bool PointsCreator::WriteToFile(HANDLE hFile, AlternativeNest* altNets, vector<int> UniteOperationsVector, bool newMethod)
{
	char buffer[1024];
	PointD* point;
	DWORD dwNumberOfBytes;
	Petri_Net* lbfNet, * primitiveNet;
	Matrix* tensor;
	UINT PrimCount;

	point = new PointD();

	int i = 0;
	for (AlternativeNest::iterator NetsIterator = altNets->begin();
		NetsIterator != altNets->end();
		++NetsIterator, i++)
	{
		//NetsIterator++;
		//(*NetsIterator)->GetMToLBF();
		Petri_Net* lbfNet_NEW = SrcToLbfSeparator::Separate(*NetsIterator, newMethod);
		AltStructsSynthesizer::PrintPetriNet(*lbfNet_NEW);

		FILE* pFile = fopen("PosSeq.names", "r");
		int Name = 0;
		int LBFCount = 0;
		do{
			Name = -1;			
			fscanf(pFile, "%d", &Name);
			LBFCount++;
		} while (Name != -1);
		fclose(pFile);

		pFile = fopen("TrnSeq.names", "r");
		do{
			Name = -1;
			fscanf(pFile, "%d", &Name);
			fscanf(pFile, "%d", &Name);
			LBFCount += Name;
		} while (Name != -1);
		fclose(pFile);

		//расчет значений по осям

		primitiveNet = LbfToPrimitiveSeparator::Separate(*lbfNet_NEW, &tensor, &PrimCount);

		//число простейших сетей (переходов), то бишь ранг сети
		point->F1 = primitiveNet->GetNumberOfTransitions();

		//сумма весов входных и выходных дуг (пока веса по 1): 
		point->F2 = FindSumPositionsWeight(*NetsIterator);

		//количество разделений(объединений) позиций и переходов
		//point->Z = UniteOperationsVector[i];
		point->F3 = LBFCount + PrimCount;


		// АНДРЕЙ! ЗАМЕНИ ЭТОТ КУСОК НА НОВУЮ ФУНКЦИЮ РАЗБИЕНИЯ!---ОТСЮДА-----------

		Petri_Net* lbfNet_NEW_kul = SrcToLbfSeparator::Separate(*NetsIterator, newMethod);

		pFile = fopen("PosSeq.names", "r");
		Name = 0;
		int LBFCount_kul = 0;
		do {
			Name = -1;
			fscanf(pFile, "%d", &Name);
			LBFCount_kul++;
		} while (Name != -1);
		fclose(pFile);

		pFile = fopen("TrnSeq.names", "r");
		do {
			Name = -1;
			fscanf(pFile, "%d", &Name);
			fscanf(pFile, "%d", &Name);
			LBFCount_kul += Name;
		} while (Name != -1);
		fclose(pFile);

		//----------------------------------------------------------ДОСЮДА---------------

		primitiveNet = LbfToPrimitiveSeparator::Separate(*lbfNet_NEW_kul, &tensor, &PrimCount);

		//Ранг сети (F1 по Кулагину)
		point->F4 = primitiveNet->GetNumberOfTransitions();
		//Количество объединений (F3 по Кулагину)
		point->F5 = LBFCount_kul + PrimCount;
		
		sprintf(buffer, "%f %f %f %f %f", point->F1, point->F2, point->F3, point->F4, point->F5);
		if (!WriteFile(hFile, buffer, strlen(buffer), &dwNumberOfBytes, NULL))
		{
			CloseFile(hFile);
			return false;
		}
		if (i < altNets->size()-1)
		{
			if (!WriteFile(hFile, "\r\n", strlen("\r\n"), &dwNumberOfBytes, NULL))
			{
				CloseFile(hFile);
				return false;
			}
		}
		
	}
	delete(point);

	return true;
}

int PointsCreator:: FindSumPositionsWeight(Petri_Net* pNet)
{
	int wtStart = 1, wtEnd = 1;//пока веса головных и хвостовых позиций по 1
	int f1, f2, f3, countStart = 0, countEnd = 0;
	for (int p = 0; p < pNet->GetNumberOfPositions(); p++)
	{
		f1 = 0; f2 = 0; f3 = 0;
		for (int t = 0; t < pNet->GetNumberOfTransitions(); t++)
		{
			if (pNet->GetElementMatrixD(p, t) > 0)
				f1++;
			if (pNet->GetElementMatrixD(p, t) < 0)
				f2++;
			if (pNet->GetElementMatrixD(p, t) == 0)
				f3++;
		}
		if (((f1 + f3) == pNet->GetNumberOfTransitions()) && (f1 != 0))
			countStart++;
		if (((f2 + f3) == pNet->GetNumberOfTransitions()) && (f2 != 0))
			countEnd++;
	}
	return countStart * wtStart + countEnd * wtEnd;
}

bool PointsCreator::CreatePoints(AlternativeNest* altNets, vector<int> UniteOperationsVector, LPCWSTR filePath, bool fNewMethd)
{
	HANDLE fileHandle = NULL;
	if (!OpenFile(filePath, fileHandle))
		return false;
	if (!WriteToFile(fileHandle, altNets, UniteOperationsVector, fNewMethd))
		return false;
	if (!CloseFile(fileHandle))
		return false;

	return true;
}

PointsCreator::PointsCreator()
{
}


PointsCreator::~PointsCreator()
{
}
