/**
* @file Petri_Net.h
* Объявление класса, соответствующего сети Петри
* @author Voinov, Senokosov @date 09.11.2015
*/

#include <string>
#include <string.h>
#include <vector>
#include <map>
#include <vector>
#include <algorithm>

class Petri_Net
{
public:
	Petri_Net();
	//параметры вес,имя началькой вершины, имяконечной вершины
	bool AddArc(int Arkweight, string StartPoint, string EndPoint); //Добавляем дугу
	//Добавляем дугу. В качестве параметров указываем вес дуги, начальный и конечный номер. При 
	//OnePos = true то дуга идёт из позиции в переход, иначе наоборот
	bool AddArc(int Arkweight, int StartPoint, int EndPoint, bool OnePos);  
	bool AddPosition(int Marking, int Number, string Name = "-1"); //Добавляем позицию
	bool AddTransition(int Number, string Name = "-1");    //Добавляем переход
	void CleaningPetriNet();							//Очистка сети Петри
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
	bool SetElementMatrixD(int col, int row, int weight);   //Получить элемент матрицы D
	bool GetClone(Petri_Net *BeginNet, bool LevelUp); 
	bool GetCloneMeta(Petri_Net *BeginNet, vector<int>matrixD, bool LevelUp);//Клонирование функции с внешними метаданными
	bool DecompositionPos(int Number, int Number1);//Какую позицию и на сколько частей делим
	bool DecompositionTra(int Number, int Number1);//Какой переход и на сколько частей делим
	bool UnionPos(vector<int> number);//объединение позиций по номеру
	bool UnionTra(vector<int> number);//объединение переходов по номеру
	vector<string> GetNamePosition(int number, int level);// Восстанавливаем имя позиции на заданном уровне без учёта дуг. Возвращаем нулевой вектор в случае неудачи
	vector<string> GetNameTransition(int number, int level);// Восстанавливаем имя позиции на заданном уровне без учёта дуг. Возвращаем нулевой вектор в случае неудачи
	int GetLevelNet(); //Получить уровень текущей сети
	bool UnionPosition(vector<int> number);//объединение позиций по номеру с сохранение всех позиций
	bool UnionTransition(vector<int> number);//объединение переходов по номеру с сохранение всех переходов
	bool Separate();	//Функция, нужная только Краснову Андрею
	void GetMToLBF(bool newMethod);

private:
	vector<int> vec;
	bool AddPosition(int Marking, int Number, vector<int>NumberParent, string Name = "-1"); //Добавляем позицию c сохранением её родословной
	bool AddTransition(int Number, vector<int>NumberParent, string Name = "-1");//Добавляем переход c сохранением его родословной

	struct Elementvector
	{
		int NumberName;
		vector<int>NumberParent;
		vector<string>NameParent;
	}EL;
	vector<Elementvector> MassNameOnLevelForPosition;
	vector<Elementvector> MassNameOnLevelForTransition;
	map <int, vector<Elementvector>> MappingForPosition;
	map <int, vector<Elementvector>> MappingForTrans;
	int MAXT;
	int MAXP;
	int Kolvo;
	int NumberLevel;

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
	int GetNumberPos(int Number);
	int GetNumberTra(int Number);
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