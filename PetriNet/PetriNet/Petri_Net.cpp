/** 
* @file Petri_Net.cpp
* Реализация функций класса, соответствующего сети Петри
* @author Voinov, Senokosov @date 09.11.2015
*/

#include "stdafx.h"
#include <sstream>

Petri_Net::Petri_Net()
{
	MAXT = 0;
	MAXP = 0;
	Kolvo = 0;
	NumberLevel = 1;
}
void Petri_Net::NewPetriNet(int MAXT1, int MAXP1)
{
	CleaningPetriNet();
	MAXT = MAXT1;
	MAXP = MAXP1;
	Kolvo = 0;
	int i;
	for (i = 0; i < MAXT; i++)
	{
		MAXT--;
		AddTransition(i);
	}
	for (i = 0; i < MAXP; i++)
	{
		MAXP--;
		AddPosition(0, i);
	}
}
void Petri_Net::GetMToLBF(bool newMethod)
	{

		FILE* pFile;
		pFile = fopen("InputM.matrix", "w");
		if (newMethod)
		{
			fprintf(pFile, "1\n");
		}
		else
		{
			fprintf(pFile, "0\n");
		}

		fprintf(pFile, "%d\n%d\n", MAXP, MAXT);

		for (int i = 0; i < MAXP; i++)
		{
			for (int j = 0; j < MAXT; j++)
			{
				//правильно получаю значения матррицы D? -- не знаю - по столцам запишется
				fprintf(pFile, "%d\n", GetElementMatrixD(i, j));
			}
		}

		fclose(pFile);
	}
bool Petri_Net::Separate()
	{
			//Генерирует на основе матрицы D исходные данные для моего модуля
			//GetMToLBF();

			//запуск моего модуля
			TCHAR szPath[] = _T("LBF.exe");
			STARTUPINFO si;
			memset(&si, 0, sizeof(si));
			si.cb = sizeof(si);
			PROCESS_INFORMATION pi;
			memset(&pi, 0, sizeof(pi));
			if (CreateProcess(NULL, szPath, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
			{
				// программа запущена, ждем её завершения
				DWORD dwWait = WaitForSingleObject(pi.hProcess, INFINITE);
				if (dwWait == WAIT_OBJECT_0)
				{
					// программа благополучно завершилась

					//Очистить матрицу D --зачем?

					//Считываем первые два значения - количество вершин и количество переходов
					FILE* pFilePos = NULL;
					FILE* pFileTr = NULL;
					FILE* pFileM = NULL;

					pFileM = fopen("D_Matrix.matrix", "r");
					pFileTr = fopen("TrnSeq.names", "r");
					pFilePos = fopen("PosSeq.names", "r");

					int MAXP_NEW;
					int MAXT_NEW;
					double D;		
					
					int Name = 0;
					int Quant = 0;
					do{
						Name= -1;
						//Создать матрицу D нового размера -- добавить новые вершины/разделить имеющиеся
						fscanf(pFilePos, "%d", &Name);
						DecompositionPos(GetNumberPosition(Name), 2);
					} while (Name != -1);
					fclose(pFilePos);

					do{
						Name = -1;
						fscanf(pFileTr, "%d", &Name);
						fscanf(pFileTr, "%d", &Quant);
						DecompositionTra(GetNumberTtransition(Name), Quant);
					} while (Name != -1);
					fclose(pFileTr);

					fscanf(pFileM, "%d", &MAXP_NEW);
					fscanf(pFileM, "%d", &MAXT_NEW);

					//Заполнение матрицы D новыми значениями, соответствующими системе ЛБФ
					for (int i = 0; i < MAXP_NEW; i++)
					{
						for (int j = 0; j < MAXT_NEW; j++)
						{
							fscanf(pFileM, "%lf", &D);
							//ЗДЕСЬ добавить значение в матрицу -- как так? уже давно лежит
 							SetElementMatrixD(i, j, D);
						}
					}
					fclose(pFileM);

					//Добавить вершины и переходы с учётом родства (или поделить имеющиеся) -- это перед перезаполнением матрицы D, и как понять с учетом родства?
					//Все файлы с входными и выходными данными моего модуля описаны ниже (п.3) -- А функции записи в xml?
				}
				CloseHandle(pi.hProcess);
				CloseHandle(pi.hThread);
			}
			return true;
		}
int Petri_Net::GetNumberPos(int Number)
{
	for (int i = 0; i < MAXP; i++)
	{
		if (NaPo[i].Number == Number)
			return i;
	}
	return -1;
}
int Petri_Net::GetNumberTra(int Number)
{
	for (int i = 0; i < MAXT; i++)
	{
		if (NaTr[i].Number == Number)
			return i;
	}
	return -1;
}
bool Petri_Net::AddPosition(int Marking, int Number, vector<int>NumberParent, string Name) 
{
	if (AddPosition(Marking, Number, Name))
	{
		int i;
		EL.NameParent.clear();
		for (i = 0; i < NumberParent.size(); i++)
		{
			EL.NameParent.push_back(GetNamePosition(NumberParent[i]));
		}
		EL.NumberParent = NumberParent;
		EL.NumberName = Number;
		MassNameOnLevelForPosition.push_back(EL);
		return true;
	}
	else
	{
		return false;
	}
}
bool Petri_Net::AddTransition(int Number, vector<int>NumberParent, string Name)
{
	if (AddTransition(Number, Name))
	{
		EL.NameParent.clear();
		int i;
		for (i = 0; i < NumberParent.size(); i++)
		{
			EL.NameParent.push_back(GetNameTransition(NumberParent[i]));
		}
		EL.NumberParent = NumberParent;
		EL.NumberName = Number;
		MassNameOnLevelForTransition.push_back(EL);
		return true;
	}
	else
	{
		return false;
	}
}
bool Petri_Net::SetElementMatrixD(int col, int row, int weight) 
{
	if (col < 0 && col > NaPo.size())
		return false;
	if (row < 0 && row > NaTr.size())
		return false;
	if (weight < 0 && weight > MAXINT)
		return false;
	if (weight > 0)
	{
		SetElementMatrixInput(col, row, 0);
		SetElementMatrixOutput(col, row, weight);
	}
	else
	{
		SetElementMatrixInput(col, row, abs(weight));
		SetElementMatrixOutput(col, row, 0);
	}
	return true;
}
bool Petri_Net::GetClone(Petri_Net *BeginNet, bool LevelUp)
{
	CleaningPetriNet();

	for (BeginNet->iNaPo = BeginNet->NaPo.begin(); BeginNet->iNaPo != BeginNet->NaPo.end(); BeginNet->iNaPo++)
	{
		NamePos M1 = *BeginNet->iNaPo;
		AddPosition(M1.Marking, M1.Number, M1.Name);
	}
	for (BeginNet->iNaTr = BeginNet->NaTr.begin(); BeginNet->iNaTr != BeginNet->NaTr.end(); BeginNet->iNaTr++)
	{
		NameTrans M2 = *BeginNet->iNaTr;
		AddTransition(M2.Number, M2.Name);
	}
	for (BeginNet->iNaAr = BeginNet->NaAr.begin(); BeginNet->iNaAr != BeginNet->NaAr.end(); BeginNet->iNaAr++)
	{
		NameArc M = *(BeginNet->iNaAr);
		AddArc(M.Arkweight, M.StartPoint, M.EndPoint);

	}
	MappingForPosition = BeginNet->MappingForPosition;
	MappingForTrans = BeginNet->MappingForTrans;
	MassNameOnLevelForPosition = BeginNet->MassNameOnLevelForPosition;
	MassNameOnLevelForTransition = BeginNet->MassNameOnLevelForTransition;
	NumberLevel = BeginNet->GetLevelNet();
	if (LevelUp == true)
	{
		MappingForPosition.insert(pair<int, vector<Elementvector>>(NumberLevel, MassNameOnLevelForPosition));
		MappingForTrans.insert(pair<int, vector<Elementvector>>(NumberLevel, MassNameOnLevelForTransition));
		MassNameOnLevelForPosition.clear();
		MassNameOnLevelForTransition.clear();
		NumberLevel++;
	}
	return true;
}
bool Petri_Net::GetCloneMeta(Petri_Net *BeginNet, vector<int>matrixD, bool LevelUp)
{
	if (matrixD.size() != MAXP*MAXT)
	{
		return false;
	}
	GetClone(BeginNet, LevelUp);
	int i, j;
	for (i = 0; i < MAXT; i++)
	for (j = 0; j < MAXP; j++)
	{
		SetElementMatrixD(j, i, matrixD[i*MAXP + j]);
	}
	return true;

}
bool Petri_Net::DecompositionPos(int Number, int Number1)
{
	if (Number1<0 || Number1>MAXINT)
	{
		return false;
	}
	if (Number<0 || Number>MAXINT)
	{
		return false;
	}
	bool Ecsess = false;
	for (iNaPo = NaPo.begin(); iNaPo != NaPo.end(); iNaPo++)
	{
		NamePos M2 = *iNaPo;
		if (M2.Number == Number)
		{

			int j = 0;

			do{
				string Name = M2.Name;
				Name += "_";
				Name += to_string(j);
				bool check = false;
				int i = MAXP + 1;
				while (check == false)
				{
					vec.clear();
					vec.push_back(Number);
					check = AddPosition(M2.Marking, i, vec, Name);
					i++;
				}
				Ecsess = true;
				j++;
			} while (j < Number1);
			break;
		}
	}
	if (Ecsess == false)
	{
		return false;
	}
	for (int k = 0; k < Number1; k++)
	{
		for (int i = 0; i < MAXT; i++)
		{
			SetElementMatrixInput(MAXP - (k + 1), i, get_value_Input(GetNumberPos(Number), i));
			SetElementMatrixOutput(MAXP - (k + 1), i, get_value_Output(GetNumberPos(Number), i));
		}
	}
	RemovePosition(Number);
	return true;
}
bool Petri_Net::DecompositionTra(int Number, int Number1)
{
	if (Number1<0 || Number1>MAXINT)
	{
		return false;
	}
	if (Number<0 || Number>MAXINT)
	{
		return false;
	}
	bool Ecsess = false;
	for (iNaTr = NaTr.begin(); iNaTr != NaTr.end(); iNaTr++)
	{
		NameTrans M2 = *iNaTr;
		if (M2.Number == Number)
		{
			int j = 0;
			do{
				string Name = M2.Name;
				Name += "_";
				Name += to_string(j);
				bool check = false;
				int i = MAXT + 1;
				while (check == false)
				{
					vec.clear();
					vec.push_back(Number);
					check = AddTransition(i, vec, Name);
					i++;
				}
				Ecsess = true;
				j++;
			} while (j < Number1);
			break;
		}
	}
	if (Ecsess == false)
	{
		return false;
	}
	for (int k = 0; k < Number1; k++)
	{
		for (int i = 0; i < MAXP; i++)
		{
			SetElementMatrixInput(i, MAXT - (k + 1), get_value_Input(i, GetNumberTra(Number)));
			SetElementMatrixOutput(i, MAXT - (k + 1), get_value_Output(i, GetNumberPos(Number)));
		}
	}

	RemoveTransition(Number);
	return true;
}
bool Petri_Net::UnionPos(vector<int> number)
{
	vector<int> Num;
	int i, j;
	if (number.size() < 2)
		return false;
	for (i = 0; i < number.size(); i++)
	{
		if (GetNumberPos(number[i]) == -1)
		{
			return false;
		}
		Num.push_back(GetNumberPos(number[i]));
	}
	vec.clear();
	for (i = 0; i < number.size(); i++)
	{
		vec.push_back(number[i]);
	}

	int mark = 0;
	for (i = 0; i < number.size(); i++)
	{
		if (mark < GetMarkingPositions(number[i]))
			mark = GetMarkingPositions(number[i]);
	}

	string name;
	for (i = 0; i < number.size(); i++)
	{
		name += GetNamePosition(number[i]);
		name += "_";
	}

	i = MAXP + 1;

	while (!AddPosition(mark, i, vec, name))
	{
		i++;
	}

	for (int i = 0; i < MAXT; i++)
	{
		int weight = 0;
		for (j = 0; j < number.size(); j++)
		{
			if (weight < GetElementMatrixInput(Num[j], i))
				weight = GetElementMatrixInput(Num[j], i);
		}
		SetElementMatrixInput(MAXP - 1, i, weight);

		weight = 0;
		for (j = 0; j < number.size(); j++)
		{
			if (weight < GetElementMatrixOutput(Num[j], i))
				weight = GetElementMatrixOutput(Num[j], i);
		}
		SetElementMatrixOutput(MAXP - 1, i, weight);
	}
	for (i = 0; i < number.size(); i++)
	{
		RemovePosition(number[i]);
	}
	return true;
}
bool Petri_Net::UnionPosition(vector<int> number)
{
	vector<int> Num;
	int i, j;
	if (number.size() < 2)
		return false;
	for (i = 0; i < number.size(); i++)
	{
		if (number[i] >= NaPo.size())
		{
			return false;
		}
	}

	int mark = 0;
	for (i = 0; i < number.size(); i++)
	{
		if (mark < NaPo[number[i]].Marking)
			mark = GetMarkingPositions(GetNumberPosition(number[i]));
	}

	for (i = 0; i < MAXT; i++)
	{
		Num.push_back(0);
		for (j = 0; j < number.size(); j++)
		{
			if (Num[i]<GetElementMatrixInput(number[j],i))
			Num[i] = GetElementMatrixInput(number[j], i);
		}

	}
	for (i = 0; i < number.size(); i++)
	{
		SetMarkingPositions(GetNumberPosition(number[i]), mark);
		for (j = 0; j < MAXT; j++)
		{
			SetElementMatrixInput(number[i], j, Num[j]);
		}

	}
	Num.clear();
	for (i = 0; i < MAXT; i++)
	{
		Num.push_back(0);
		for (j = 0; j < number.size(); j++)
		{
			if (Num[i] < GetElementMatrixOutput(number[j], i))
				Num[i] = GetElementMatrixOutput(number[j], i);
		}

	}
	for (i = 0; i < number.size(); i++)
	{
		for (j = 0; j < MAXT; j++)
		{
			SetElementMatrixOutput(number[i], j, Num[j]);
		}

	}

	return true;
}
bool Petri_Net::UnionTransition(vector<int> number)
{
	vector<int> Num;
	int i, j;
	if (number.size() < 2)
		return false;
	for (i = 0; i < number.size(); i++)
	{
		if (number[i] >= NaTr.size())
		{
			return false;
		}
	}

	for (i = 0; i < MAXP; i++)
	{
		Num.push_back(0);
		for (j = 0; j < number.size(); j++)
		{
			if (Num[i] < GetElementMatrixInput(i, number[j]))
				Num[i] = GetElementMatrixInput(i, number[j]);
		}

	}
	for (i = 0; i < number.size(); i++)
	{
		for (j = 0; j < MAXP; j++)
		{
			SetElementMatrixInput(j, number[i], Num[j]);
		}

	}
	Num.clear();
	for (i = 0; i < MAXP; i++)
	{
		Num.push_back(0);
		for (j = 0; j < number.size(); j++)
		{
			if (Num[i] < GetElementMatrixOutput(i, number[j]))
				Num[i] = GetElementMatrixOutput(i, number[j]);
		}

	}
	for (i = 0; i < number.size(); i++)
	{
		for (j = 0; j < MAXP; j++)
		{
			SetElementMatrixOutput(j, number[i], Num[j]);
		}

	}
	return true;
}
bool Petri_Net::UnionTra(vector<int> number)
{
	vector<int> Num;
	int i, j;
	if (number.size() < 2)
		return false;
	for (i = 0; i < number.size(); i++)
	{
		if (GetNumberTra(number[i]) == -1)
		{
			return false;
		}
		Num.push_back(GetNumberTra(number[i]));
	}
	vec.clear();
	for (i = 0; i < number.size(); i++)
	{
		vec.push_back(number[i]);
	}


	string name;
	for (i = 0; i < number.size(); i++)
	{
		name += GetNameTransition(number[i]);
		name += "_";
	}

	i = MAXT + 1;

	while (!AddTransition(i, vec, name))
	{
		i++;
	}

	for (int i = 0; i < MAXP; i++)
	{
		int weight = 0;
		for (j = 0; j < number.size(); j++)
		{
			if (weight < GetElementMatrixInput(i, Num[j]))
				weight = GetElementMatrixInput(i, Num[j]);
		}
		SetElementMatrixInput(i, MAXT - 1, weight);

		weight = 0;
		for (j = 0; j < number.size(); j++)
		{
			if (weight < GetElementMatrixOutput(i, Num[j]))
				weight = GetElementMatrixOutput(i, Num[j]);
		}
		SetElementMatrixOutput(i, MAXT - 1, weight);
	}
	for (i = 0; i < number.size(); i++)
	{
		RemoveTransition(number[i]);
	}
	return true;
}
vector<string> Petri_Net::GetNamePosition(int number, int level)
{
	Petri_Net Clone;
	Clone.GetClone(this, false);
	vector<string>vec1;
	vector<string>vec11;
	vector<int>vec2;
	vector<int>vec3;
	bool EnableNames;
	if (level == GetLevelNet())
	{
		vec1.push_back(GetNamePosition(number));
		return vec1;
	}
	if (level > GetLevelNet())
	{
		return vec1;
	}
	int i, j, lev = GetLevelNet();
	vec2.push_back(number);
	bool Enakl = false;
	vec11.push_back(GetNamePosition(number));
	while (lev != level)
	{
		vector<string>vecZapStr = vec11;
		vector<int>vecZapInt = vec2;
		for (i = MassNameOnLevelForPosition.size() - 1; i != -1; i--)
		{
			vec3.clear();
			vec1.clear();
			EnableNames = false;
			NaPo;
			EL = MassNameOnLevelForPosition[i];
			for (int q = 0; q < vec2.size(); q++)
			{
				if (EL.NumberName == vec2[q])
				{
					EnableNames = true;
				}
			}
			for (j = EL.NumberParent.size() - 1; j != -1; j--)
			{
				if (EnableNames == true)
				{
					if (AddPosition(0, EL.NumberParent[j], EL.NameParent[j]))//Добавили родителей
					{

						vec1.push_back(EL.NameParent[j]); //Все имена родителей
						vec3.push_back(EL.NumberParent[j]); //Все номера родителей
					}
				}
			}
			if (RemovePosition(EL.NumberName))//Убили ребёнка
			{

				for (int q = 0; q < vec2.size(); q++)
				{
					if (vec2[q] == EL.NumberName)
					{
						vec2.erase(vec2.begin() + q);
						vec11.erase(vec11.begin() + q);
					}
				}
				for (int q = 0; q < vec3.size(); q++)
				{
					vec2.push_back(vec3[q]);
					vec11.push_back(vec1[q]);
				}
			}
		}
		vecZapStr.clear();
		vecZapInt.clear();
		lev--;
		MassNameOnLevelForPosition.clear();
		MassNameOnLevelForPosition = MappingForPosition[lev];
	}
	GetClone(&Clone, false);
	return vec11;
}
vector<string> Petri_Net::GetNameTransition(int number, int level)
{
	Petri_Net Clone;
	Clone.GetClone(this, false);
	vector<string>vec1;
	vector<string>vec11;
	vector<int>vec2;
	vector<int>vec3;
	bool EnableNames;
	if (level == GetLevelNet())
	{
		vec1.push_back(GetNameTransition(number));
		return vec1;
	}
	if (level > GetLevelNet())
	{
		return vec1;
	}
	int i, j, lev = GetLevelNet();
	vec2.push_back(number);
	bool Enakl = false;
	vec11.push_back(GetNameTransition(number));
	while (lev != level)
	{
		vector<string>vecZapStr = vec11;
		vector<int>vecZapInt = vec2;
		for (i = MassNameOnLevelForTransition.size() - 1; i != -1; i--)
		{
			vec3.clear();
			vec1.clear();
			EnableNames = false;
			NaPo;
			EL = MassNameOnLevelForTransition[i];
			for (int q = 0; q < vec2.size(); q++)
			{
				if (EL.NumberName == vec2[q])
				{
					EnableNames = true;
				}
			}
			for (j = EL.NumberParent.size() - 1; j != -1; j--)
			{
				if (EnableNames == true)
				{
					if (AddTransition(EL.NumberParent[j], EL.NameParent[j]))//Добавили родителей
					{

						vec1.push_back(EL.NameParent[j]); //Все имена родителей
						vec3.push_back(EL.NumberParent[j]); //Все номера родителей
					}
				}
			}
			if (RemoveTransition(EL.NumberName))//Убили ребёнка
			{

				for (int q = 0; q < vec2.size(); q++)
				{
					if (vec2[q] == EL.NumberName)
					{
						vec2.erase(vec2.begin() + q);
						vec11.erase(vec11.begin() + q);
					}
				}
				for (int q = 0; q < vec3.size(); q++)
				{
					vec2.push_back(vec3[q]);
					vec11.push_back(vec1[q]);
				}
			}
		}
		vecZapStr.clear();
		vecZapInt.clear();
		lev--;
		MassNameOnLevelForTransition.clear();
		MassNameOnLevelForTransition = MappingForTrans[lev];
	}
	GetClone(&Clone, false);
	return vec11;
}
int Petri_Net::GetLevelNet() //Получить уровень текущей сети
{
	return NumberLevel;
}
bool Petri_Net::AddPosition(int Marking, int Number, string Name)
{
	if (Marking < 0 || Marking > MAXINT)
		return false;
	int i;
	for (i = 0; i < strlen(Name.c_str()); i++)
	{
		if (Name[i] == ' ')
			return false;
	}
	if (Number < 0 || Number > MAXINT)
		return false;
	if (Name == "-1")
	{
		Name = "p";
		Name += to_string(Number + 1);
	}
	for (iNaPo = NaPo.begin(); iNaPo != NaPo.end(); iNaPo++)
	{
		NamePos M1 = *iNaPo;
		if (M1.Number == Number || M1.Name == Name)
		{
			return false;
		}
	}
	MAXP++;
	NP.Marking = Marking;
	NP.Name = Name;
	NP.Number = Number;
	NaPo.push_back(NP);
	Get_Matrix_Input();
	Get_Matrix_Output();
	Get_Matrix_D();
	Elementvector EL1;
	EL1.NameParent.clear();

	vector<int> a;
	vector<string> b;
	a.push_back(-5);
	b.push_back("AAA AAA");
	EL1.NameParent = b;
	EL1.NumberParent = a;
	EL1.NumberName = Number;
	MassNameOnLevelForPosition.push_back(EL1);
	return true;
}
bool Petri_Net::AddTransition(int Number, string Name)
{
	int i;
	for (i = 0; i < strlen(Name.c_str()); i++)
	{
		if (Name[i] == ' ')
			return false;
	}
	if (Number < 0 || Number > MAXINT)
		return false;
	if (Name == "-1")
	{
		Name = "t";
		Name += to_string(Number + 1);
	}
	for (iNaTr = NaTr.begin(); iNaTr != NaTr.end(); iNaTr++)
	{
		NameTrans M1 = *iNaTr;
		if (M1.Number == Number || M1.Name == Name)
		{
			return false;
		}
	}
	MAXT++;
	NT.Name = Name;
	NT.Number = Number;
	NaTr.push_back(NT);
	Get_Matrix_Input();
	Get_Matrix_Output();
	Get_Matrix_D();
	Elementvector EL1;
	EL1.NameParent.clear();

	vector<int> a;
	vector<string> b;
	a.push_back(-5);
	b.push_back("AAA AAA");
	EL1.NameParent = b;
	EL1.NumberParent = a;
	EL1.NumberName = Number;
	MassNameOnLevelForTransition.push_back(EL1);
	return true;
}
bool Petri_Net::AddArc(int Arkweight, string StartPoint, string EndPoint)
{
	int i;
	for (i = 0; i < strlen(StartPoint.c_str()); i++)
	{
		if (StartPoint[i] == ' ')
			return false;
	}
	for (i = 0; i < strlen(EndPoint.c_str()); i++)
	{
		if (EndPoint[i] == ' ')
			return false;
	}
	if (Arkweight <= 0 || Arkweight > MAXINT)
		return false;
	bool Exist = false;
	for (iNaAr = NaAr.begin(); iNaAr != NaAr.end(); iNaAr++)
	{
		NameArc M = *iNaAr;
		if (M.EndPoint == EndPoint && M.StartPoint == StartPoint)
		{
			return Exist;
			break;
		}
	}
	for (iNaPo = NaPo.begin(); iNaPo != NaPo.end(); iNaPo++)
	{
		NamePos M1 = *iNaPo;
		if (M1.Name == StartPoint || M1.Name == EndPoint)
		{
			Exist = true;
			break;
		}
	}
	if (Exist == false)
	{
		return false;
	}
	Exist = false;
	for (iNaTr = NaTr.begin(); iNaTr != NaTr.end(); iNaTr++)
	{
		NameTrans M1 = *iNaTr;
		if (M1.Name == StartPoint || M1.Name == EndPoint)
		{
			Exist = true;
			break;
		}
	}
	if (Exist == false)
	{
		return false;
	}
	if (StartPoint == EndPoint)
		return false;

	NA.Arkweight = Arkweight;
	NA.StartPoint = StartPoint;
	NA.EndPoint = EndPoint;
	NaAr.push_back(NA);
	Kolvo++;
	Get_Matrix_Input();
	Get_Matrix_Output();
	Get_Matrix_D();
	return true;
}
bool Petri_Net::AddArc(int Arkweight, int StartPoint, int EndPoint, bool OnePos)
{
	int i;
	string start;
	string end;
	if (StartPoint < 0 || StartPoint > MAXINT)
		return false;
	if (EndPoint < 0 || EndPoint > MAXINT)
		return false;
	if (Arkweight <= 0 || Arkweight > MAXINT)
		return false;
	bool Exist = false;
	for (iNaAr = NaAr.begin(); iNaAr != NaAr.end(); iNaAr++)
	{
		NameArc M = *iNaAr;
		if (GetNumberPosition(M.EndPoint) == EndPoint && GetNumberTtransition(M.StartPoint) == StartPoint)
		{
			return Exist;
			break;
		}
		if (GetNumberTtransition(M.EndPoint) == EndPoint && GetNumberPosition(M.StartPoint) == StartPoint)
		{
			return Exist;
			break;
		}
	}
	for (iNaPo = NaPo.begin(); iNaPo != NaPo.end(); iNaPo++)
	{
		NamePos M1 = *iNaPo;
		if (OnePos == true)
		{
			if (GetNumberPosition(M1.Name) == StartPoint)
			{
				start = GetNamePosition(StartPoint);
				Exist = true;
				break;
			}
		}
		else{
			if (GetNumberPosition(M1.Name) == EndPoint)
			{
				end = GetNamePosition(EndPoint);
				Exist = true;
				break;
			}

		}


	}
	if (Exist == false)
	{
		return false;
	}
	Exist = false;
	for (iNaTr = NaTr.begin(); iNaTr != NaTr.end(); iNaTr++)
	{
		NameTrans M1 = *iNaTr;
		if (OnePos == false)
		{
			if (GetNumberTtransition(M1.Name) == StartPoint)
			{
				start = GetNameTransition(StartPoint);
				Exist = true;
				break;
			}
		}
		else
		{
			if (GetNumberTtransition(M1.Name) == EndPoint)
			{
				end = GetNameTransition(EndPoint);
				Exist = true;
				break;
			}
		}

	}
	if (Exist == false)
	{
		return false;
	}
	if (start == end)
		return false;

	NA.Arkweight = Arkweight;
	NA.StartPoint = start;
	NA.EndPoint = end;
	NaAr.push_back(NA);
	Kolvo++;
	Get_Matrix_Input();
	Get_Matrix_Output();
	Get_Matrix_D();
	return true;
}
void Petri_Net::CleaningPetriNet()
{
	MAXT = 0;
	MAXP = 0;
	Kolvo = 0;
	NaAr.clear();
	NaPo.clear();
	NaTr.clear();
}
int Petri_Net::GetNumberOfTransitions()
{
	return MAXT;
}
int Petri_Net::GetNumberOfPositions()
{
	return MAXP;
}
int Petri_Net::GetElementMatrixInput(int col, int row)
{
	if (col < 0 || col > NaPo.size())
		return -1;
	if (row < 0 || row > NaTr.size())
		return -1;
	return get_value_Input(col, row);
}
int Petri_Net::GetElementMatrixOutput(int col, int row)
{
	if (col < 0 || col > NaPo.size())
		return -1;
	if (row < 0 || row > NaTr.size())
		return -1;
	return get_value_Output(col, row);
}
int Petri_Net::GetElementMatrixD(int col, int row)
{
	if (col < 0 || col > NaPo.size())
		return -1;
	if (row < 0 || row > NaTr.size())
		return -1;
	return get_value_D(col, row);
}
bool Petri_Net::SetElementMatrixInput(int col, int row, int weight)
{
	if (col < 0 || col > NaPo.size())
		return false;
	if (row < 0 || row > NaTr.size())
		return false;
	if (weight < 0 || weight > MAXINT)
		return false;
	bool Find = false;
	set_value_Input(col, row, weight);
	set_value_D(col, row, get_value_Output(col, row) - get_value_Input(col, row));
	for (iNaAr = NaAr.begin(); iNaAr != NaAr.end(); iNaAr++)
	{
		NameArc M = *iNaAr;
		if (M.StartPoint == NaPo[col].Name && M.EndPoint == NaTr[row].Name)
		{
			iNaAr->Arkweight = weight;
			if (weight == 0)
				RemoveArc(M.StartPoint, M.EndPoint);
			Find = true;
			break;
		}
	}
	if (Find == false)
	{
		AddArc(weight, NaPo[col].Name, NaTr[row].Name);
	}
	return true;
}
bool Petri_Net::SetElementMatrixOutput(int col, int row, int weight)
{
	if (col < 0 || col > NaPo.size())
		return false;
	if (row < 0 || row > NaTr.size())
		return false;
	if (weight < 0 || weight > MAXINT)
		return false;
	bool Find = false;
	set_value_Output(col, row, weight);
	set_value_D(col, row, get_value_Output(col, row) - get_value_Input(col, row));
	for (iNaAr = NaAr.begin(); iNaAr != NaAr.end(); iNaAr++)
	{
		NameArc M = *iNaAr;
		if (M.EndPoint == NaPo[col].Name && M.StartPoint == NaTr[row].Name)
		{
			iNaAr->Arkweight = weight;
			if (weight == 0)
				RemoveArc(M.StartPoint, M.EndPoint);
			Find = true;
			break;
		}
	}
	if (Find == false)
	{
		AddArc(weight, NaTr[row].Name, NaPo[col].Name);
	}
	return true;
}
string Petri_Net::GetNamePosition(int number)
{
	if (number < 0)
		return " ";
	bool en = false;
	for (iNaPo = NaPo.begin(); iNaPo != NaPo.end(); iNaPo++)
	{
		NamePos M1 = *iNaPo;
		if (M1.Number == number)
		{
			en = true;
			return M1.Name;
		}
	}
	if (en == false)
		return "-1";
}
int Petri_Net::GetNumberPosition(int number)
{
	if (number < 0 || number > NaPo.size())
		return -1;
	return NaPo[number].Number;
}
int Petri_Net::GetNumberPosition(string Name)
{
	int i;
	for (i = 0; i < strlen(Name.c_str()); i++)
	{
		if (Name[i] == ' ')
			return false;
	}
	bool en = false;
	for (iNaPo = NaPo.begin(); iNaPo != NaPo.end(); iNaPo++)
	{
		NamePos M1 = *iNaPo;
		if (M1.Name == Name)
		{
			en = true;
			return M1.Number;
		}
	}
	if (en == false)
		return -1;
}
int Petri_Net::GetMarkingPositions(int number)
{
	if (number < 0)
		return -1;
	bool en = false;
	for (iNaPo = NaPo.begin(); iNaPo != NaPo.end(); iNaPo++)
	{
		NamePos M1 = *iNaPo;
		if (M1.Number == number)
		{
			en = true;
			return M1.Marking;
		}
	}
	if (en == false)
		return -1;
}
int Petri_Net::GetMarkingPositions(string Name)
{
	int i;
	for (i = 0; i < strlen(Name.c_str()); i++)
	{
		if (Name[i] == ' ')
			return false;
	}
	bool en = false;
	for (iNaPo = NaPo.begin(); iNaPo != NaPo.end(); iNaPo++)
	{
		NamePos M1 = *iNaPo;
		if (M1.Name == Name)
		{
			en = true;
			return M1.Marking;
		}
	}
	if (en == false)
		return -1;
}
bool Petri_Net::SetMarkingPositions(string Name, int mark)
{
	int i;
	for (i = 0; i < strlen(Name.c_str()); i++)
	{
		if (Name[i] == ' ')
			return false;
	}
	if (mark < 0 || mark > MAXINT)
		return false;
	bool Enable = false;
	for (iNaPo = NaPo.begin(); iNaPo != NaPo.end(); iNaPo++)
	{
		NamePos M1 = *iNaPo;
		if (M1.Name == Name)
		{
			Enable = true;
			M1.Marking = mark;
			iNaPo->Marking = mark;
			break;
		}
	}
	return Enable;
}
bool Petri_Net::SetMarkingPositions(int number, int mark)
{
	if (number < 0)
		return false;
	if (mark < 0 || mark > MAXINT)
		return false;
	bool Enable = false;
	for (iNaPo = NaPo.begin(); iNaPo != NaPo.end(); iNaPo++)
	{
		NamePos M1 = *iNaPo;
		if (M1.Number == number)
		{
			Enable = true;
			M1.Marking = mark;
			iNaPo->Marking = mark;
			break;
		}
	}
	return Enable;
}
string Petri_Net::GetNameTransition(int number)
{
	if (number < 0)
		return " ";
	bool Enable = false;
	for (iNaTr = NaTr.begin(); iNaTr != NaTr.end(); iNaTr++)
	{
		NameTrans M0 = *iNaTr;
		if (M0.Number == number)
		{
			Enable = true;
			return M0.Name;
		}
	}
	if (Enable == false)
		return "-1";
}
int Petri_Net::GetNumberTtransition(int number)
{
	if (number < 0 || number > NaTr.size())
		return -1;
	return NaTr[number].Number;
}
int Petri_Net::GetNumberTtransition(string Name)
{
	int i;
	for (i = 0; i < strlen(Name.c_str()); i++)
	{
		if (Name[i] == ' ')
			return false;
	}
	bool Enable = false;
	for (iNaTr = NaTr.begin(); iNaTr != NaTr.end(); iNaTr++)
	{
		NameTrans M0 = *iNaTr;
		if (M0.Name == Name)
		{
			Enable = true;
			return M0.Number;
		}
	}
	if (Enable == false)
		return -1;
}
string Petri_Net::GetNameEnd(int number)
{
	if (number < 0 || number > NaAr.size())
		return " ";
	return NaAr[number].EndPoint;
}
string Petri_Net::GetNameStart(int number)
{
	if (number < 0 || number > NaAr.size())
		return " ";
	return NaAr[number].StartPoint;
}
int Petri_Net::GetWeightArc(int number)
{
	if (number < 0 || number > NaAr.size())
		return -1;
	return NaAr[number].Arkweight;
}
int Petri_Net::GetNumberOfArc()
{
	return Kolvo;
}
bool Petri_Net::SetNamePosition(int NumberPos, string NewName)
{
	int i;
	for (i = 0; i < strlen(NewName.c_str()); i++)
	{
		if (NewName[i] == ' ')
			return false;
	}
	bool Enable = true;
	string OldName;
	for (iNaPo = NaPo.begin(); iNaPo != NaPo.end(); iNaPo++)
	{
		NamePos M1 = *iNaPo;
		if (M1.Name == NewName)
		{
			Enable = false;
			break;
		}
	}
	for (iNaTr = NaTr.begin(); iNaTr != NaTr.end(); iNaTr++)
	{
		NameTrans M0 = *iNaTr;
		if (M0.Name == NewName)
		{
			Enable = false;
			break;
		}
	}
	if (Enable == false)
	{
		return false;
	}
	Enable = false;
	for (iNaPo = NaPo.begin(); iNaPo != NaPo.end(); iNaPo++)
	{
		NamePos M2 = *iNaPo;
		if (M2.Number == NumberPos)
		{
			Enable = true;
			OldName = M2.Name;
			M2.Name = NewName;
			break;
		}
	}
	for (iNaAr = NaAr.begin(); iNaAr != NaAr.end(); iNaAr++)
	{
		NameArc M3 = *iNaAr;
		if (M3.StartPoint == OldName)
		{
			M3.StartPoint = NewName;
		}
		if (M3.EndPoint == OldName)
		{
			M3.EndPoint = NewName;
		}
	}
	return Enable;
}
bool Petri_Net::SetNameTransition(int NumberTrans, string NewName)
{
	int i;
	for (i = 0; i < strlen(NewName.c_str()); i++)
	{
		if (NewName[i] == ' ')
			return false;
	}
	bool Enable = true;
	string OldName;
	for (iNaTr = NaTr.begin(); iNaTr != NaTr.end(); iNaTr++)
	{
		NameTrans M1 = *iNaTr;
		if (M1.Name == NewName)
		{
			Enable = false;
			break;
		}
	}
	for (iNaPo = NaPo.begin(); iNaPo != NaPo.end(); iNaPo++)
	{
		NamePos M0 = *iNaPo;
		if (M0.Name == NewName)
		{
			Enable = false;
			break;
		}
	}
	if (Enable == false)
	{
		return false;
	}
	Enable = false;
	for (iNaTr = NaTr.begin(); iNaTr != NaTr.end(); iNaTr++)
	{
		NameTrans M2 = *iNaTr;
		if (M2.Number == NumberTrans)
		{
			Enable = true;
			OldName = M2.Name;
			M2.Name = NewName;
			break;
		}
	}
	for (iNaAr = NaAr.begin(); iNaAr != NaAr.end(); iNaAr++)
	{
		NameArc M3 = *iNaAr;
		if (M3.StartPoint == OldName)
		{
			M3.StartPoint = NewName;
		}
		if (M3.EndPoint == OldName)
		{
			M3.EndPoint = NewName;
		}
	}
	return Enable;
}
bool Petri_Net::RemovePosition(string Name)
{
	bool Ecsess = false;
	for (iNaPo = NaPo.begin(); iNaPo != NaPo.end(); iNaPo++)
	{
		NamePos M2 = *iNaPo;
		if (M2.Name == Name)
		{
			NaPo.erase(iNaPo);
			Ecsess = true;
			break;
		}
	}
	if (Ecsess == false)
	{
		return false;
	}
	bool enab = false;
	for (iNaAr = NaAr.begin(); iNaAr != NaAr.end(); iNaAr++)
	{
		if (enab == true)
		{
			iNaAr = NaAr.begin();
			enab = false;
		}
		NameArc M1 = *iNaAr;

		if (M1.StartPoint == Name || M1.EndPoint == Name)
		{
			iNaAr = NaAr.erase(iNaAr);
			Kolvo--;
			if (iNaAr != NaAr.begin())
			{
				iNaAr--;

			}
			enab = true;
		}
	}
	MAXP--;
	Get_Matrix_Input();
	Get_Matrix_Output();
	Get_Matrix_D();
	return true;
}
bool Petri_Net::RemovePosition(int Number)
{
	bool Ecsess = false;
	string NameDeleting;
	for (iNaPo = NaPo.begin(); iNaPo != NaPo.end(); iNaPo++)
	{
		NamePos M2 = *iNaPo;
		if (M2.Number == Number)
		{
			NameDeleting = M2.Name;
			NaPo.erase(iNaPo);
			Ecsess = true;
			break;
		}
	}
	if (Ecsess == false)
	{
		return false;
	}
	bool enab = false;
	for (iNaAr = NaAr.begin(); iNaAr != NaAr.end(); iNaAr++)
	{
		if (enab == true)
		{
			iNaAr = NaAr.begin();
			enab = false;
		}
		NameArc M1 = *iNaAr;

		if (M1.StartPoint == NameDeleting || M1.EndPoint == NameDeleting)
		{
			iNaAr = NaAr.erase(iNaAr);
			Kolvo--;
			if (iNaAr != NaAr.begin())
			{
				iNaAr--;

			}
			enab = true;
		}
	}
	MAXP--;
	Get_Matrix_Input();
	Get_Matrix_Output();
	Get_Matrix_D();
	return true;
}
bool Petri_Net::RemoveTransition(string Name)
{
	bool Ecsess = false;
	for (iNaTr = NaTr.begin(); iNaTr != NaTr.end(); iNaTr++)
	{
		NameTrans M2 = *iNaTr;
		if (M2.Name == Name)
		{
			NaTr.erase(iNaTr);
			Ecsess = true;
			break;
		}
	}
	if (Ecsess == false)
	{
		return false;
	}
	bool enab = false;
	for (iNaAr = NaAr.begin(); iNaAr != NaAr.end(); iNaAr++)
	{
		if (enab == true)
		{
			iNaAr = NaAr.begin();
			enab = false;
		}
		NameArc M1 = *iNaAr;

		if (M1.StartPoint == Name || M1.EndPoint == Name)
		{
			iNaAr = NaAr.erase(iNaAr);
			Kolvo--;
			if (iNaAr != NaAr.begin())
			{
				iNaAr--;

			}
			enab = true;
		}
	}
	MAXT--;
	Get_Matrix_Input();
	Get_Matrix_Output();
	Get_Matrix_D();
	return true;
}
bool Petri_Net::RemoveTransition(int Number)
{
	bool Ecsess = false;
	string NameDeleting;
	for (iNaTr = NaTr.begin(); iNaTr != NaTr.end(); iNaTr++)
	{
		NameTrans M2 = *iNaTr;
		if (M2.Number == Number)
		{
			NameDeleting = M2.Name;
			NaTr.erase(iNaTr);
			Ecsess = true;
			break;
		}
	}
	if (Ecsess == false)
	{
		return false;
	}
	bool enab = false;
	for (iNaAr = NaAr.begin(); iNaAr != NaAr.end(); iNaAr++)
	{
		if (enab == true)
		{
			iNaAr = NaAr.begin();
			enab = false;
		}
		NameArc M1 = *iNaAr;

		if (M1.StartPoint == NameDeleting || M1.EndPoint == NameDeleting)
		{
			iNaAr = NaAr.erase(iNaAr);
			Kolvo--;
			if (iNaAr != NaAr.begin())
			{
				iNaAr--;

			}
			enab = true;
		}
	}
	MAXT--;
	Get_Matrix_Input();
	Get_Matrix_Output();
	Get_Matrix_D();
	return true;
}
bool Petri_Net::RemoveArc(string StartName, string EdnName)
{
	bool Ecsess = false;
	for (iNaAr = NaAr.begin(); iNaAr != NaAr.end(); iNaAr++)
	{
		NameArc M2 = *iNaAr;
		if (M2.StartPoint == StartName && M2.EndPoint == EdnName)
		{
			NaAr.erase(iNaAr);
			Ecsess = true;
			break;
		}
	}
	if (Ecsess == false)
	{
		return false;
	}
	Kolvo--;
	Get_Matrix_Input();
	Get_Matrix_Output();
	Get_Matrix_D();
	return true;
}
void Petri_Net::Matrix_Input(int MAXP, int MAXT)
{
	memory_Input = new double[MAXP*MAXT];
}
double Petri_Net::get_value_Input(int col, int row)
{
	return memory_Input[MAXT*col + row];
}
void Petri_Net::set_value_Input(int col, int row, double value)
{
	memory_Input[MAXT*col + row] = value;
}
void Petri_Net::Matrix_Output(int MAXP, int MAXT)
{
	memory_Output = new double[MAXP*MAXT];
}
double Petri_Net::get_value_Output(int col, int row)
{
	return memory_Output[MAXT*col + row];
}
void Petri_Net::set_value_Output(int col, int row, double value)
{
	memory_Output[MAXT*col + row] = value;
}
void Petri_Net::Matrix_D(int MAXP, int MAXT)
{
	memory_D = new double[MAXP*MAXT];
}
double Petri_Net::get_value_D(int col, int row)
{
	return memory_D[MAXT*col + row];
}
void Petri_Net::set_value_D(int col, int row, double value)
{
	memory_D[MAXT*col + row] = value;
}
double* Petri_Net::Get_Matrix_Input()
{
	Matrix_Input(MAXP, MAXT);
	for (int i = 0; i < MAXP; i++)
	{
		for (int j = 0; j < MAXT; j++)
		{
			set_value_Input(i, j, 0);
		}
	}


	for (iNaAr = NaAr.begin(); iNaAr != NaAr.end(); iNaAr++)
	{
		NameArc M1 = *iNaAr;
		int i = 0;
		int j = 0;
		for (iNaPo = NaPo.begin(); iNaPo != NaPo.end(); iNaPo++)
		{
			j = 0;
			NamePos M2 = *iNaPo;
			if (M2.Name == M1.StartPoint)
			{

				for (iNaTr = NaTr.begin(); iNaTr != NaTr.end(); iNaTr++)
				{
					NameTrans M3 = *iNaTr;
					if (M3.Name == M1.EndPoint)
					{
						set_value_Input(i, j, M1.Arkweight);
					}
					j++;
				}
			}
			i++;
		}
	}

	return memory_Input;
}
double* Petri_Net::Get_Matrix_Output()
{
	Matrix_Output(MAXP, MAXT);
	for (int i = 0; i < MAXP; i++)
	{
		for (int j = 0; j < MAXT; j++)
		{
			set_value_Output(i, j, 0);
		}
	}
	for (iNaAr = NaAr.begin(); iNaAr != NaAr.end(); iNaAr++)
	{
		NameArc M1 = *iNaAr;
		int i = 0;
		int j = 0;
		for (iNaPo = NaPo.begin(); iNaPo != NaPo.end(); iNaPo++)
		{
			j = 0;
			NamePos M2 = *iNaPo;
			if (M2.Name == M1.EndPoint)
			{
				for (iNaTr = NaTr.begin(); iNaTr != NaTr.end(); iNaTr++)
				{
					NameTrans M3 = *iNaTr;
					if (M3.Name == M1.StartPoint)
					{
						set_value_Output(i, j, M1.Arkweight);
					}
					j++;
				}
			}
			i++;
		}
	}
	return memory_Output;
}
double* Petri_Net::Get_Matrix_D()
{
	Matrix_Input(MAXP, MAXT);
	Matrix_Output(MAXP, MAXT);
	Matrix_D(MAXP, MAXT);
	memory_Input = Get_Matrix_Input();
	memory_Output = Get_Matrix_Output();
	for (int i = 0; i < MAXP; i++)
	{
		for (int j = 0; j < MAXT; j++)
		{
			set_value_D(i, j, get_value_Output(i, j) - get_value_Input(i, j));
		}
	}
	return memory_D;
}