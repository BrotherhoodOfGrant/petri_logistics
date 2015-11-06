/**
* @file Petri_Net.h
* ���������� ������, ���������������� ���� �����
* @author ... @date 01.11.2015
*/

class Petri_Net
{

public:
	Petri_Net();
	bool AddArc(int Arkweight, string StartPoint, string EndPoint); //��������� ����
	bool AddPosition(int Marking, int Number, string Name = "-1"); //��������� �������
	bool AddTransition(int Number, string Name = "-1");    //��������� �������
	void CleaningPetriNet();
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

private:

	// ���������� ���������
	int MAXT;

	// ���������� �������
	int MAXP;

	// ���������� ���
	int Kolvo;

	// ��� �������
	struct NamePos
	{
		// ����������
		int Marking;

		// ��� �������
		string Name;

		// ���������� ����� (?)
		int Number;
	}NP;

	// ��� ��������
	struct NameTrans
	{
		// ���������� ����� (?)
		int Number;

		// ��� ��������
		string Name;
	}NT;

	// ��� ����
	struct NameArc
	{
		// ��� ����
		int Arkweight;

		// ��� �������� �������
		string EndPoint;

		// ��� ��������� �������
		string StartPoint;
	}NA;

	// ������ ���� �������
	vector<NamePos> NaPo;
	vector<NamePos>::iterator iNaPo;

	// ������ ���� ���������
	vector<NameTrans> NaTr;
	vector<NameTrans>::iterator iNaTr;

	// ������ ���� ���
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