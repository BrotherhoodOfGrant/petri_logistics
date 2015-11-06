/**
* @file Petri_Net.h
* Объявление класса, соответствующего сети Петри
* @author ... @date 01.11.2015
*/

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

	// Количество переходов
	int MAXT;

	// Количество позиций
	int MAXP;

	// Количество дуг
	int Kolvo;

	// Имя позиции
	struct NamePos
	{
		// Маркировка
		int Marking;

		// Имя позиции
		string Name;

		// Порядковый номер (?)
		int Number;
	}NP;

	// Имя перехода
	struct NameTrans
	{
		// Порядковый номер (?)
		int Number;

		// Имя перехода
		string Name;
	}NT;

	// Имя дуги
	struct NameArc
	{
		// Вес дуги
		int Arkweight;

		// Имя конечной вершины
		string EndPoint;

		// Имя начальной вершины
		string StartPoint;
	}NA;

	// Массив имен позиций
	vector<NamePos> NaPo;
	vector<NamePos>::iterator iNaPo;

	// Массив имен переходов
	vector<NameTrans> NaTr;
	vector<NameTrans>::iterator iNaTr;

	// Массив имен дуг
	vector<NameArc> NaAr;
	vector<NameArc>::iterator iNaAr;

	int *memory_Input;
	void Matrix_Input(int MAXP, int MAXT);
	int get_value_Input(int col, int row);
	void set_value_Input(int col, int row, int value);
	int *memory_Output;
	void Matrix_Output(int MAXP, int MAXT);
	int get_value_Output(int col, int row);
	void set_value_Output(int col, int row, int value);
	int *memory_D;
	void Matrix_D(int MAXP, int MAXT);
	int get_value_D(int col, int row);
	void set_value_D(int col, int row, int value);
	int* Get_Matrix_Input();
	int* Get_Matrix_Output();
	int* Get_Matrix_D();

	// added by Lena:
	bool NameUnable(string Name);
};