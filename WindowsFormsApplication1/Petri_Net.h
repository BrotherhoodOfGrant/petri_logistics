#include <string>
#include <string.h>
#include <vector>
class Petri_Net
{
public:
Petri_Net();
 bool AddArc(int Arkweight, string StartPoint, string EndPoint); //Добавляем дугу
 bool AddPosition(int Marking, int Number, string Name = "-1"); //Добавляем позицию
 bool AddTransition(int Number, string Name = "-1");    //Добавляем переход
 void CleaningPetriNet();
 int GetElementMatrixD(int col, int row);      //Получение элемента выходной матрицы
 int GetElementMatrixInput(int col, int row);     //Получение элемента входной матрицы
 int GetElementMatrixOutput(int col, int row);     //Получение элемента выходной матрицы
 int GetMarkingPositions(int number);       //Получение маркировки позиции
 int GetMarkingPositions(string Name);       //Получение маркировки позиции
 string GetNameEnd(int number);         //Получение конечного имени дуги
 string GetNamePosition(int number);        //Получение имени позиции
 string GetNameStart(int number);        //Получение начального имени дуги
 string GetNameTransition(int number);       //Получение имени перехода
 int GetNumberPosition(int number);        //Получение порядкового номера позиции
 int GetNumberPosition(string Name);        //Получение номера позиции
 int GetNumberTtransition(int number);       //Получение порядкового номера перехода
 int GetNumberTtransition(string Name);       //Получение номера перехода
 int GetNumberOfPositions();          //Получение количества позиций
 int GetNumberOfTransitions();         //Получение количества переходов
 int GetNumberOfArc();           //Получение количества дуг
 int GetWeightArc(int number);         //Получение веса дуги
 void NewPetriNet(int MAXT1, int MAXP1);       //Создание новой сети Петри заданного размера
 bool RemoveArc(string StartName, string EdnName);    //Удаление дуги
 bool RemovePosition(string Name);        //Удаление позиции
 bool RemovePosition(int Number);        //Удаление позиции
 bool RemoveTransition(string Name);        //Удаление перехода
 bool RemoveTransition(int Number);        //Удаление перехода
 bool SetElementMatrixInput(int col, int row, int weight);  //Запись элемента входной матрицы
 bool SetElementMatrixOutput(int col, int row, int weight);  //Запись элемента выходной матрицы
 bool SetMarkingPositions(string Name, int mark);    //Установить маркировку для позиции
 bool SetMarkingPositions(int number, int mark);     //Установить маркировку для позиции
 bool SetNamePosition(int NumberPos, string NewName);   //Установить имя позиции
 bool SetNameTransition(int NumberTrans, string NewName);  //Установить имя перехода
private:
	int MAXT;
	int MAXP;
	int Kolvo;
	struct NamePos
	{
		int Marking;
		string Name;
		int Number;
	}NP;
	struct NameTrans
	{
		int Number;
		string Name;
	}NT;
	struct NameArc
	{
		int Arkweight;
		string EndPoint;
		string StartPoint;
	}NA;
	vector<NamePos> NaPo;
	vector<NamePos>::iterator iNaPo;
	vector<NameTrans> NaTr;
	vector<NameTrans>::iterator iNaTr;
	vector<NameArc> NaAr;
	vector<NameArc>::iterator iNaAr;
	double *memory_Input;
	void Matrix_Input(int MAXP, int MAXT);
	double get_value_Input(int col, int row);
	void set_value_Input(int col, int row, double value);
	double *memory_Output;
	void Matrix_Output(int MAXP, int MAXT);
	double get_value_Output(int col, int row);
	void set_value_Output(int col, int row, double value);
	double *memory_D;
	void Matrix_D(int MAXP, int MAXT);
	double get_value_D(int col, int row);
	void set_value_D(int col, int row, double value);
	double* Get_Matrix_Input();
	double* Get_Matrix_Output();
	double* Get_Matrix_D();
};
Petri_Net::Petri_Net()
{
	MAXT = 0;
	MAXP = 0;
	Kolvo = 0;
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
bool Petri_Net::AddPosition(int Marking, int Number, string Name)
{
	if (Marking < 0 && Marking > MAXINT)
		return false;
	int i;
	for (i = 0; i < strlen(Name.c_str()); i++)
	{
		if (Name[i] == ' ')
			return false;
	}
	if (Number < 0 && Number > MAXINT)
		return false;
	MAXP++;
	if (Name == "-1")
	{
		Name = "p";
		Name += (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(Convert::ToString(Number + 1));
	}
	for (iNaPo = NaPo.begin(); iNaPo != NaPo.end(); iNaPo++)
	{
		NamePos M1 = *iNaPo;
		if (M1.Number == Number)
		{
			return false;
		}
	}
	NP.Marking = Marking;
	NP.Name = Name;
	NP.Number = Number;
	NaPo.push_back(NP);
	Get_Matrix_Input();
	Get_Matrix_Output();
	Get_Matrix_D();
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
	if (Number < 0 && Number > MAXINT)
		return false;
	MAXT++;
	if (Name == "-1")
	{
		Name ="t";
		Name += (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(Convert::ToString(Number + 1));
	}
	for (iNaTr = NaTr.begin(); iNaTr != NaTr.end(); iNaTr++)
	{
		NameTrans M1 = *iNaTr;
		if (M1.Number == Number)
		{
			return false;
			break;
		}
	}
	NT.Name = Name;
	NT.Number = Number;
	NaTr.push_back(NT);
	Get_Matrix_Input();
	Get_Matrix_Output();
	Get_Matrix_D();
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
	if (Arkweight < 0 && Arkweight > MAXINT)
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
	if (col < 0 && col > NaPo.size())
		return -1;
	if (row < 0 && row > NaTr.size())
		return -1;
	return get_value_Input(col, row);
}
int Petri_Net::GetElementMatrixOutput(int col, int row)
{
	if (col < 0 && col > NaPo.size())
		return -1;
	if (row < 0 && row > NaTr.size())
		return -1;
	return get_value_Output(col, row);
}
int Petri_Net::GetElementMatrixD(int col, int row)
{
	if (col < 0 && col > NaPo.size())
		return -1;
	if (row < 0 && row > NaTr.size())
		return -1;
	return get_value_D(col, row);
}
bool Petri_Net::SetElementMatrixInput(int col, int row, int weight)
{
	if (col < 0 && col > NaPo.size())
		return false;
	if (row < 0 && row > NaTr.size())
		return false;
	if (weight < 0 && weight > MAXINT)
		return false;
	bool Find = false;
	set_value_Input(col, row, weight);
	set_value_D(col, row, get_value_Output(col, row) - get_value_Input(col, row));
	for (iNaAr = NaAr.begin(); iNaAr != NaAr.end(); iNaAr++)
	{
		NameArc M = *iNaAr;
		if (M.StartPoint == NaPo[col].Name && M.EndPoint == NaTr[row].Name)
		{
			M.Arkweight = weight;
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
	if (col < 0 && col > NaPo.size())
		return false;
	if (row < 0 && row > NaTr.size())
		return false;
	if (weight < 0 && weight > MAXINT)
		return false;
	bool Find = false;
	set_value_Output(col, row, weight);
	set_value_D(col, row, get_value_Output(col, row) - get_value_Input(col, row));
	for (iNaAr = NaAr.begin(); iNaAr != NaAr.end(); iNaAr++)
	{
		NameArc M = *iNaAr;
		if (M.EndPoint == NaPo[col].Name && M.StartPoint == NaTr[row].Name)
		{
			M.Arkweight = weight;
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
	if (number < 0 && number > NaPo.size())
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
	if (number < 0 && number > NaPo.size())
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
	if (number < 0 && number > NaPo.size())
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
	if (mark < 0 && mark > MAXINT)
		return false;
	bool Enable = false;
	for (iNaPo = NaPo.begin(); iNaPo != NaPo.end(); iNaPo++)
	{
		NamePos M1 = *iNaPo;
		if (M1.Name == Name)
		{
			Enable = true;
			M1.Marking = mark;
			iNaPo->Marking=mark;
			break;
		}
	}
	return Enable;
}
bool Petri_Net::SetMarkingPositions(int number, int mark)
{
	if (number < 0 && number > NaPo.size())
		return false;
	if (mark < 0 && mark > MAXINT)
		return false;
	bool Enable = false;
	for (iNaPo = NaPo.begin(); iNaPo != NaPo.end(); iNaPo++)
	{
		NamePos M1 = *iNaPo;
		if (M1.Number == number)
		{
			Enable = true;
			M1.Marking = mark;
			iNaPo->Marking=mark;
			break;
		}
	}
	return Enable;
}
string Petri_Net::GetNameTransition(int number)
{
	if (number < 0 && number > NaTr.size())
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
	if (number < 0 && number > NaTr.size())
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
	if (number < 0 && number > NaAr.size())
		return " ";
	return NaAr[number].EndPoint;
}
string Petri_Net::GetNameStart(int number)
{
	if (number < 0 && number > NaAr.size())
		return " ";
	return NaAr[number].StartPoint;
}
int Petri_Net::GetWeightArc(int number)
{
	if (number < 0 && number > NaAr.size())
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
	for (iNaAr = NaAr.begin(); iNaAr != NaAr.end(); iNaAr++)
	{
		NameArc M1 = *iNaAr;

		if (M1.StartPoint == Name || M1.EndPoint == Name)
		{
			iNaAr = NaAr.erase(iNaAr);
			Kolvo--;
			iNaAr--;
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
	for (iNaAr = NaAr.begin(); iNaAr != NaAr.end(); iNaAr++)
	{
		NameArc M1 = *iNaAr;

		if (M1.StartPoint == NameDeleting || M1.EndPoint == NameDeleting)
		{
			iNaAr = NaAr.erase(iNaAr);
			Kolvo--;
			iNaAr--;
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
	for (iNaAr = NaAr.begin(); iNaAr != NaAr.end(); iNaAr++)
	{
		NameArc M1 = *iNaAr;

		if (M1.StartPoint == Name || M1.EndPoint == Name)
		{
			iNaAr = NaAr.erase(iNaAr);
			if (iNaAr == NaAr.end())
				Kolvo--;
			iNaAr--;
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
	for (iNaAr = NaAr.begin(); iNaAr != NaAr.end(); iNaAr++)
	{
		NameArc M1 = *iNaAr;

		if (M1.StartPoint == NameDeleting || M1.EndPoint == NameDeleting)
		{
			iNaAr = NaAr.erase(iNaAr);
			if (iNaAr == NaAr.end())
				Kolvo--;
			iNaAr--;
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