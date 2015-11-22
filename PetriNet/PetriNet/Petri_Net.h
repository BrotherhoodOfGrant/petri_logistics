/**
* @file Petri_Net.h
* ���������� ������, ���������������� ���� �����
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
	//��������� ���,��� ��������� �������, ����������� �������
	bool AddArc(int Arkweight, string StartPoint, string EndPoint); //��������� ����
	//��������� ����. � �������� ���������� ��������� ��� ����, ��������� � �������� �����. ��� 
	//OnePos = true �� ���� ��� �� ������� � �������, ����� ��������
	bool AddArc(int Arkweight, int StartPoint, int EndPoint, bool OnePos);  
	bool AddPosition(int Marking, int Number, string Name = "-1"); //��������� �������
	bool AddTransition(int Number, string Name = "-1");    //��������� �������
	void CleaningPetriNet();							//������� ���� �����
	int GetElementMatrixD(int col, int row);      //��������� �������� �������� �������
	int GetElementMatrixInput(int col, int row);     //��������� �������� ������� �������
	int GetElementMatrixOutput(int col, int row);     //��������� �������� �������� �������
	int GetMarkingPositions(int number);       //��������� ���������� �������
	int GetMarkingPositions(string Name);       //��������� ���������� �������
	string GetNameEnd(int number);         //��������� ��������� ����� ����
	string GetNamePosition(int number);        //��������� ����� �������
	string GetNameStart(int number);        //��������� ���������� ����� ����
	string GetNameTransition(int number);       //��������� ����� ��������
	int GetNumberPosition(int number);        //��������� ����������� ������ �������
	int GetNumberPosition(string Name);        //��������� ������ �������
	int GetNumberTtransition(int number);       //��������� ����������� ������ ��������
	int GetNumberTtransition(string Name);       //��������� ������ ��������
	int GetNumberOfPositions();          //��������� ���������� �������
	int GetNumberOfTransitions();         //��������� ���������� ���������
	int GetNumberOfArc();           //��������� ���������� ���
	int GetWeightArc(int number);         //��������� ���� ����
	void NewPetriNet(int MAXT1, int MAXP1);       //�������� ����� ���� ����� ��������� �������
	bool RemoveArc(string StartName, string EdnName);    //�������� ����
	bool RemovePosition(string Name);        //�������� �������
	bool RemovePosition(int Number);        //�������� �������
	bool RemoveTransition(string Name);        //�������� ��������
	bool RemoveTransition(int Number);        //�������� ��������
	bool SetElementMatrixInput(int col, int row, int weight);  //������ �������� ������� �������
	bool SetElementMatrixOutput(int col, int row, int weight);  //������ �������� �������� �������
	bool SetMarkingPositions(string Name, int mark);    //���������� ���������� ��� �������
	bool SetMarkingPositions(int number, int mark);     //���������� ���������� ��� �������
	bool SetNamePosition(int NumberPos, string NewName);   //���������� ��� �������
	bool SetNameTransition(int NumberTrans, string NewName);  //���������� ��� ��������
	bool SetElementMatrixD(int col, int row, int weight);   //�������� ������� ������� D
	bool GetClone(Petri_Net *BeginNet, bool LevelUp); 
	bool GetCloneMeta(Petri_Net *BeginNet, vector<int>matrixD, bool LevelUp);//������������ ������� � �������� �����������
	bool DecompositionPos(int Number, int Number1);//����� ������� � �� ������� ������ �����
	bool DecompositionTra(int Number, int Number1);//����� ������� � �� ������� ������ �����
	bool UnionPos(vector<int> number);//����������� ������� �� ������
	bool UnionTra(vector<int> number);//����������� ��������� �� ������
	vector<string> GetNamePosition(int number, int level);// ��������������� ��� ������� �� �������� ������ ��� ����� ���. ���������� ������� ������ � ������ �������
	vector<string> GetNameTransition(int number, int level);// ��������������� ��� ������� �� �������� ������ ��� ����� ���. ���������� ������� ������ � ������ �������
	int GetLevelNet(); //�������� ������� ������� ����
	bool UnionPosition(vector<int> number);//����������� ������� �� ������ � ���������� ���� �������
	bool UnionTransition(vector<int> number);//����������� ��������� �� ������ � ���������� ���� ���������
	bool Separate();	//�������, ������ ������ �������� ������
	void GetMToLBF(bool newMethod);

private:
	vector<int> vec;
	bool AddPosition(int Marking, int Number, vector<int>NumberParent, string Name = "-1"); //��������� ������� c ����������� � �����������
	bool AddTransition(int Number, vector<int>NumberParent, string Name = "-1");//��������� ������� c ����������� ��� �����������

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