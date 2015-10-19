//пока последняя версия
//ИЗМЕНЕНИЯ:
//Form1.h - много чего изменено в загрузке матрицы в xml и обратно
//Petri_Net.h - добавлены функции, исправлены ошибки в функциях получения входной и выходной матриц
//Matrix.h - доработан конструктор с 3 параметрами
//Del.cpp - исправлена ошибка получения отрицательных значений при решении системы уравнений
//PetriNet.h - файл исключен из проекта
// Сохранение и загрузку матрицы в cpt не смотрел. Больно долго разбирался с классом и решением уравнений.
#pragma once
#define BUFFER_SIZE (1024*64)
#include "resource.h"
#include "Save.h"
#include "GenericMatrix.h"
#include "Petri_Net.h"
#include "del.h"

Petri_Net Petri;
namespace WindowsFormsApplication1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для Form1
	/// </summary>
	int MAXT = 0, MAXP = 0;
	bool Enab = true;
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::DataGridView^  dataGridView1;
	private: System::Windows::Forms::DataGridView^  dataGridView2;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;

	private: System::Windows::Forms::Label^  label4;

	private: System::Windows::Forms::DataGridView^  dataGridView4;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::Button^  button6;
	private: System::Windows::Forms::DataGridView^  dataGridView5_vector;

	private: System::Windows::Forms::Label^  label5;

	private: System::Windows::Forms::DataGridView^  dataGridView5;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::DataGridView^  dataGridView6;
	private: System::Windows::Forms::Button^  button7;





	protected:

	private:
		/// <summary>
		/// Требуется переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Обязательный метод для поддержки конструктора - не изменяйте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->dataGridView2 = (gcnew System::Windows::Forms::DataGridView());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->dataGridView4 = (gcnew System::Windows::Forms::DataGridView());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->dataGridView5_vector = (gcnew System::Windows::Forms::DataGridView());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->dataGridView5 = (gcnew System::Windows::Forms::DataGridView());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->dataGridView6 = (gcnew System::Windows::Forms::DataGridView());
			this->button7 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView5_vector))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView5))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView6))->BeginInit();
			this->SuspendLayout();
			// 
			// dataGridView1
			// 
			this->dataGridView1->AllowUserToAddRows = false;
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			resources->ApplyResources(this->dataGridView1, L"dataGridView1");
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::AutoSizeToAllHeaders;
			this->dataGridView1->CellValueChanged += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &Form1::dataGridView1_CellValueChanged);
			// 
			// dataGridView2
			// 
			this->dataGridView2->AllowUserToAddRows = false;
			this->dataGridView2->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			resources->ApplyResources(this->dataGridView2, L"dataGridView2");
			this->dataGridView2->Name = L"dataGridView2";
			this->dataGridView2->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::AutoSizeToAllHeaders;
			this->dataGridView2->CellValueChanged += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &Form1::dataGridView2_CellValueChanged);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// label1
			// 
			resources->ApplyResources(this->label1, L"label1");
			this->label1->Name = L"label1";
			// 
			// label2
			// 
			resources->ApplyResources(this->label2, L"label2");
			this->label2->Name = L"label2";
			// 
			// label4
			// 
			resources->ApplyResources(this->label4, L"label4");
			this->label4->Name = L"label4";
			// 
			// dataGridView4
			// 
			this->dataGridView4->AllowUserToAddRows = false;
			this->dataGridView4->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			resources->ApplyResources(this->dataGridView4, L"dataGridView4");
			this->dataGridView4->Name = L"dataGridView4";
			this->dataGridView4->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::AutoSizeToAllHeaders;
			// 
			// button2
			// 
			resources->ApplyResources(this->button2, L"button2");
			this->button2->Name = L"button2";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// button3
			// 
			resources->ApplyResources(this->button3, L"button3");
			this->button3->Name = L"button3";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// button4
			// 
			resources->ApplyResources(this->button4, L"button4");
			this->button4->Name = L"button4";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &Form1::button4_Click);
			// 
			// button5
			// 
			this->button5->BackColor = System::Drawing::SystemColors::ControlLight;
			resources->ApplyResources(this->button5, L"button5");
			this->button5->Name = L"button5";
			this->button5->UseVisualStyleBackColor = false;
			this->button5->Click += gcnew System::EventHandler(this, &Form1::button5_Click);
			// 
			// button6
			// 
			resources->ApplyResources(this->button6, L"button6");
			this->button6->Name = L"button6";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &Form1::button6_Click);
			// 
			// dataGridView5_vector
			// 
			this->dataGridView5_vector->AllowUserToAddRows = false;
			this->dataGridView5_vector->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			resources->ApplyResources(this->dataGridView5_vector, L"dataGridView5_vector");
			this->dataGridView5_vector->Name = L"dataGridView5_vector";
			this->dataGridView5_vector->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::AutoSizeToAllHeaders;
			this->dataGridView5_vector->CellValueChanged += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &Form1::dataGridView5_vector_CellValueChanged);
			// 
			// label5
			// 
			resources->ApplyResources(this->label5, L"label5");
			this->label5->Name = L"label5";
			// 
			// dataGridView5
			// 
			this->dataGridView5->AllowUserToAddRows = false;
			this->dataGridView5->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			resources->ApplyResources(this->dataGridView5, L"dataGridView5");
			this->dataGridView5->Name = L"dataGridView5";
			this->dataGridView5->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::AutoSizeToAllHeaders;
			this->dataGridView5->CellValueChanged += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &Form1::dataGridView5_CellValueChanged);
			// 
			// label6
			// 
			resources->ApplyResources(this->label6, L"label6");
			this->label6->Name = L"label6";
			// 
			// button1
			// 
			resources->ApplyResources(this->button1, L"button1");
			this->button1->Name = L"button1";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// label3
			// 
			resources->ApplyResources(this->label3, L"label3");
			this->label3->Name = L"label3";
			// 
			// dataGridView6
			// 
			this->dataGridView6->AllowUserToAddRows = false;
			this->dataGridView6->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			resources->ApplyResources(this->dataGridView6, L"dataGridView6");
			this->dataGridView6->Name = L"dataGridView6";
			this->dataGridView6->ReadOnly = true;
			// 
			// button7
			// 
			resources->ApplyResources(this->button7, L"button7");
			this->button7->Name = L"button7";
			this->button7->UseVisualStyleBackColor = true;
			this->button7->Click += gcnew System::EventHandler(this, &Form1::button7_Click_1);
			// 
			// Form1
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->BackColor = System::Drawing::SystemColors::ControlLight;
			resources->ApplyResources(this, L"$this");
			this->Controls->Add(this->button7);
			this->Controls->Add(this->dataGridView6);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->dataGridView5);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->dataGridView5_vector);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->dataGridView4);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->dataGridView2);
			this->Controls->Add(this->dataGridView1);
			this->Name = L"Form1";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView5_vector))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView5))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView6))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		void RisMatrix(void)
		{
			Enab = false;
			int i = 0;
			do {
				DataGridViewTextBoxColumn^ myC = gcnew DataGridViewTextBoxColumn();
				dataGridView1->Columns->Add(myC);
				DataGridViewTextBoxColumn^ myC1 = gcnew DataGridViewTextBoxColumn();
				dataGridView2->Columns->Add(myC1);
				DataGridViewTextBoxColumn^ myC2 = gcnew DataGridViewTextBoxColumn();
				dataGridView5_vector->Columns->Add(myC2);
				DataGridViewTextBoxColumn^ myC3 = gcnew DataGridViewTextBoxColumn();
				dataGridView5->Columns->Add(myC3);
				DataGridViewTextBoxColumn^ myC4 = gcnew DataGridViewTextBoxColumn();
				dataGridView4->Columns->Add(myC4);
				i++;

			} while (i < MAXP);
			i = 0;
			dataGridView5_vector->Rows->Add();
			dataGridView5->Rows->Add();
			do {
				dataGridView1->Rows->Add();
				dataGridView2->Rows->Add();

				dataGridView4->Rows->Add();
				DataGridViewTextBoxColumn^ myC2 = gcnew DataGridViewTextBoxColumn();
				dataGridView6->Columns->Add(myC2);
				this->dataGridView6->Columns[i]->Width = 30;
				dataGridView6->Columns[i]->HeaderCell->Value = "t" + Convert::ToString(i + 1);
				i++;
			} while (i < MAXT);
			dataGridView6->Rows->Add();
			for (int i = 0; i < MAXT; i++)
			{
				for (int j = 0; j < MAXP; j++)
				{
					dataGridView1->Rows[i]->Cells[j]->Value = 0;
					dataGridView1->Columns[j]->HeaderCell->Value = "p" + Convert::ToString(j + 1);
					dataGridView1->Rows[i]->HeaderCell->Value = "t" + Convert::ToString(i + 1);
					dataGridView2->Rows[i]->Cells[j]->Value = 0;
					dataGridView2->Columns[j]->HeaderCell->Value = "p" + Convert::ToString(j + 1);
					dataGridView2->Rows[i]->HeaderCell->Value = "t" + Convert::ToString(i + 1);
					this->dataGridView1->Columns[j]->Width = 30;
					this->dataGridView2->Columns[j]->Width = 30;

					dataGridView4->Rows[i]->Cells[j]->Value = 0;
					dataGridView4->Columns[j]->HeaderCell->Value = "p" + Convert::ToString(j + 1);
					dataGridView4->Rows[i]->HeaderCell->Value = "t" + Convert::ToString(i + 1);
					this->dataGridView4->Columns[j]->Width = 30;
				}
			}
			for (i = 0; i < MAXP; i++)
			{
				dataGridView5_vector->Rows[0]->Cells[i]->Value = 0;
				dataGridView5_vector->Columns[i]->HeaderCell->Value = "p" + Convert::ToString(i + 1);
				dataGridView5_vector->Columns[i]->Width = 30;
				dataGridView5->Columns[i]->HeaderCell->Value = "p" + Convert::ToString(i + 1);
				dataGridView5->Columns[i]->Width = 30;
				dataGridView5->Rows[0]->Cells[i]->Value = 0;
			}
			Enab = true;
		}
		void DeleteDataFromMatrix(void)
		{
			this->dataGridView1->Rows->Clear();
			this->dataGridView2->Rows->Clear();
			this->dataGridView4->Rows->Clear();
			this->dataGridView5->Rows->Clear();
			this->dataGridView6->Rows->Clear();
			this->dataGridView5_vector->Rows->Clear();
			this->dataGridView4->Columns->Clear();
			this->dataGridView2->Columns->Clear();
			this->dataGridView1->Columns->Clear();
			this->dataGridView5->Columns->Clear();
			this->dataGridView6->Columns->Clear();
			this->dataGridView5_vector->Columns->Clear();
		}
		void Matrix_D()//нахождение матрицы D
		{		
			for (int i = 0; i < MAXP; i++)
			{

				for (int j = 0; j < MAXT; j++)
				{
					dataGridView4->Rows[j]->Cells[i]->Value = Petri.GetElementMatrixD(i, j);
				}

			}
		}
		void Vivod()
		{
		MAXT = Petri.GetNumberOfTransitions();
		MAXP = Petri.GetNumberOfPositions();

		RisMatrix();
		for (int i = 0; i < MAXP; i++)
		{
			for (int j = 0; j < MAXT; j++)
			{
				dataGridView1->Rows[j]->Cells[i]->Value = Petri.GetElementMatrixInput(i, j);
			}
		}

		for (int i = 0; i < MAXP; i++)
		{
			for (int j = 0; j < MAXT; j++)
			{
				dataGridView2->Rows[j]->Cells[i]->Value = Petri.GetElementMatrixOutput(i, j);
			}
		}

		for (int i = 0; i < MAXP; i++)
		{
			dataGridView5_vector->Rows[0]->Cells[i]->Value = Petri.GetMarkingPositions(Petri.GetNumberPosition(i));
			dataGridView5->Rows[0]->Cells[i]->Value = Petri.GetMarkingPositions(Petri.GetNumberPosition(i));
		}
		}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				 Enab = false;
				 openFileDialog1->Filter = "XML файл (*.xml)|*.xml";
				 if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				 {
					 DeleteDataFromMatrix();
					 Petri.CleaningPetriNet();
					 String^ Path = openFileDialog1->FileName;
					 char BUF1[BUFFER_SIZE];
					 memset(BUF1, 0, BUFFER_SIZE);
					 char* readh;
					 DWORD dwFileSizeHigh;
					 readh = BUF1;
					 string  XLM;
					 XLM.clear();
					 DWORD BytesRead;

					 HANDLE hFile = CreateFile((char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(Path), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL);
					 __int64 qwFileSize = GetFileSize(hFile, &dwFileSizeHigh);
					 do{
						 ReadFile(hFile, readh, BUFFER_SIZE, &BytesRead, NULL);
						 XLM += readh;
						 dwFileSizeHigh -= BUFFER_SIZE;
					 } while (dwFileSizeHigh < BUFFER_SIZE);
					 CloseHandle(hFile);
					 int num = 0;
					 num = XLM.find("Name");
					 XLM[num + 1] = 'A';
					 num = XLM.find("Name");
					 XLM[num + 1] = 'A';
					 int Marking;
					 string Name;
					 int Number;
					 while (1)
					 {
						 Marking = 0;
						 Name.clear();
						 Number = 0;
						 num = XLM.find("Mark");
						 if (num == -1)
							 break;
						 XLM[num + 1] = 'A';
						 num += 6;
						 do {
							 Marking = Marking * 10 + (XLM[num] - 48);
							 num++;
						 } while (XLM[num] != 34);
						 num = XLM.find("Name");
						 XLM[num + 1] = 'A';
						 num += 6;
						 do{
							 Name += XLM[num];
							 num++;
						 } while (XLM[num] != 34);
						 XLM[num + 4] = 'A';
						 num += 7;
						 do{
							 Number = Number * 10 + (XLM[num] - 48);
							 num++;
						 } while (XLM[num] != 34);
						 Petri.AddPosition(Marking, Number, Name);
					 }
					 num = XLM.find("Num");
					 XLM[num + 1] = 'A';
					 while (1) 
					 {
						 Number = 0;
						 Name.clear();
						 num = XLM.find("trans X");
						 if (num == -1)
							 break;
						 XLM[num + 1] = 'A';
						 num = XLM.find(" Num");
						 XLM[num + 1] = 'A';
						 num += 6;
						 do{
							 Number = Number * 10 + (XLM[num] - 48);
							 num++;
						 } while (XLM[num] != 34);
						 num = XLM.find("Name");
						 XLM[num + 1] = 'A';
						 num += 6;
						 do{
							 Name += XLM[num];
							 num++;
						 } while (XLM[num] != 34);
						 Petri.AddTransition(Number, Name);
					 }
					 int Arkweight;
					 string StartPoint;
					 string EndPoint;
					 while (1) 
					 {
						 Arkweight = 0;
						 StartPoint.clear();
						 EndPoint.clear();
						 num = XLM.find("EndPoint");
						 if (num == -1)
							 break;
						 XLM[num + 1] = 'A';
						 num += 10;
						 do{
							 EndPoint += XLM[num];
							 num++;
						 } while (XLM[num] != 34);

						 num = XLM.find("StartPoint");
						 XLM[num + 1] = 'A';
						 num += 12;
						 do{
							 StartPoint += XLM[num];
							 num++;
						 } while (XLM[num] != 34);

						 num = XLM.find("ArcWeight");
						 XLM[num + 1] = 'A';
						 num += 11;
						 do{
							 Arkweight = Arkweight * 10 + (XLM[num] - 48);
							 num++;
						 } while (XLM[num] != 34);
						 Petri.AddArc(Arkweight, StartPoint, EndPoint);
					 }

					 Vivod();
					 Matrix_D();
				 }
				 Enab = true;
	}
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
				 ToolTip^ toolTip1 = gcnew ToolTip;
				 toolTip1->SetToolTip(button1, "Загрузка сети Петри из файла xml");
				 toolTip1->SetToolTip(button3, "Загрузка сети Петри из файла матриц");
				 toolTip1->SetToolTip(button2, "Сохранение сети Петри в файле матриц");
				 toolTip1->SetToolTip(button4, "Сохранение сети Петри в файле xml");
				 toolTip1->SetToolTip(button6, "Создание новой сети Петри");
				 toolTip1->SetToolTip(button5, "Очистка матриц");
				 dataGridView1->BackgroundColor = Color::White;//Установка белого заднего фона
				 dataGridView2->BackgroundColor = Color::White;
				 dataGridView4->BackgroundColor = Color::White;
				 dataGridView5_vector->BackgroundColor = Color::White;
				 dataGridView5->BackgroundColor = Color::White;
				 dataGridView6->BackgroundColor = Color::White;

	}
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
				 if (dataGridView1->ColumnCount == 0)
				 {
					 MessageBox::Show("Отсутствует матрица для сохранения !!!", "Ошибка!", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				 }
				 else
				 {
					 string matrix;
					 int i, j;
					 matrix = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(Convert::ToString(Petri.GetNumberOfTransitions()));
					 matrix += " ";
					 matrix += (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(Convert::ToString(Petri.GetNumberOfPositions()));
					 matrix += " ";
					 matrix += (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(Convert::ToString(Petri.GetNumberOfArc()));
					 matrix += " ";
					 for (i = 0; i < Petri.GetNumberOfPositions(); i++)
					 {
						 matrix += (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(Convert::ToString(Petri.GetMarkingPositions(Petri.GetNumberPosition(i))));
						 matrix += " ";
						 matrix += Petri.GetNamePosition(Petri.GetNumberPosition(i));
						 matrix += " ";
						 matrix += (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(Convert::ToString(Petri.GetNumberPosition(i)));
						 matrix += " ";
					 }
					 for (i = 0; i < Petri.GetNumberOfTransitions(); i++)
					 {
						 matrix += (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(Convert::ToString(Petri.GetNumberTtransition(i)));
						 matrix += " ";
						 matrix += Petri.GetNameTransition(Petri.GetNumberTtransition(i));
						 matrix += " ";
					 }
					 for (i = 0; i < Petri.GetNumberOfArc(); i++)
					 {
						 matrix += (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(Convert::ToString(Petri.GetWeightArc(i)));
						 matrix += " ";
						 matrix += Petri.GetNameEnd(i);
						 matrix += " ";
						 matrix += Petri.GetNameStart(i);
						 matrix += " ";
					 }
					 bool f = false;
					 DWORD BytesWrite;
					 DWORD BytesRead;
					 char BUF1[256];
					 char* readh = BUF1;
					 DWORD dwFileSizeHigh;//Размер файла
					 HANDLE hFile1;
					 do
					 {
						 Save ty;
						 ty.ShowDialog(this);


						 hFile1 = CreateFile("prm.cpt", GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
						 ReadFile(hFile1, readh, 256, &BytesRead, NULL);
						 string pr = BUF1;
						 pr += ".cpt";
						 CloseHandle(hFile1);
						 DeleteFile("prm.cpt");
						 hFile1 = CreateFile(pr.c_str(), GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
						 if (hFile1 != INVALID_HANDLE_VALUE)
						 {
							 f = true;
						 }
						 else
						 {
							 MessageBox::Show("Невозможно сохранить файл с таким именем !!!", "Ошибка!", MessageBoxButtons::OK, MessageBoxIcon::Warning);
						 }
					 } while (f == false);
					 i = 0;
					 do{
						 WriteFile(hFile1, matrix.c_str() + i, BUFFER_SIZE, &BytesWrite, NULL);
						 i += BUFFER_SIZE;
					 } while (i <= strlen(matrix.c_str()));
					 SetFilePointer(hFile1, strlen(matrix.c_str()), NULL, FILE_BEGIN);
					 SetEndOfFile(hFile1);
					 CloseHandle(hFile1);
				 }
	}
	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
				 Enab = false;
				 openFileDialog1->Filter = "Файл матриц (*.cpt)|*.cpt";
				 if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				 {
					 DeleteDataFromMatrix();
					 Petri.CleaningPetriNet();
					 char BUF1[BUFFER_SIZE];
					 char* readh;
					 DWORD dwFileSizeHigh;//Размер файла
					 readh = BUF1;
					 string  Matrix;
					 DWORD BytesRead;//Сколько считали
					 String^ file1 = openFileDialog1->FileName;

					 HANDLE hFile = CreateFile((char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(openFileDialog1->FileName), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL);
					 __int64 qwFileSize = GetFileSize(hFile, &dwFileSizeHigh);
					 do{
						 ReadFile(hFile, readh, BUFFER_SIZE, &BytesRead, NULL);
						 Matrix += readh;
						 dwFileSizeHigh -= BUFFER_SIZE;
					 } while (dwFileSizeHigh < BUFFER_SIZE);
					 CloseHandle(hFile);
					 Petri.CleaningPetriNet();
					 MAXT = 0;
					 MAXP = 0;
					 int Kolvo = 0;
					 int num = 0;
					 do{
						 MAXT = MAXT * 10 + Convert::ToInt32(Matrix[num]) - 48;
						 num++;
					 } while (Matrix[num] != 32);
					 num++;

					 do{
						 MAXP = MAXP * 10 + Convert::ToInt32(Matrix[num]) - 48;
						 num++;
					 } while (Matrix[num] != 32);
					 num++;
					 do{
						 Kolvo = Kolvo * 10 + Convert::ToInt32(Matrix[num]) - 48;
						 num++;
					 } while (Matrix[num] != 32);
					 num++;
					 int Marking = 0;
					 string Name = "";
					 int Number = 0;
					 for (int i = 0; i < MAXP; i++)
					 {
						 Marking = 0;
						 Name = "";
						 Number = 0;
						 do{
							 Marking = Marking * 10 + Convert::ToInt32(Matrix[num]) - 48;
							 num++;
						 } while (Matrix[num] != 32);
						 num++;
						 do{
							 Name += Matrix[num];
							 num++;
						 } while (Matrix[num] != 32);
						 num++;
						 do{
							 Number = Number * 10 + Convert::ToInt32(Matrix[num]) - 48;
							 num++;
						 } while (Matrix[num] != 32);
						 num++;
						 Petri.AddPosition(Marking, Number, Name);
					 }
					 Name = "";
					 Number = 0;
					 for (int i = 0; i < MAXT; i++)
					 {
						 Name = "";
						 Number = 0;
						 do{
							 Number = Number * 10 + Convert::ToInt32(Matrix[num]) - 48;
							 num++;
						 } while (Matrix[num] != 32);
						 num++;
						 do{
							 Name += Matrix[num];
							 num++;
						 } while (Matrix[num] != 32);
						 num++;
						 Petri.AddTransition(Number, Name);
					 }
					 int Arkweight = 0;
					 string EndPoint = "";
					 string StartPoint = "";
					 for (int i = 0; i < Kolvo; i++)
					 {
						 Arkweight = 0;
						 EndPoint = "";
						 StartPoint = "";
						 do{
							 Arkweight = Arkweight * 10 + Convert::ToInt32(Matrix[num]) - 48;
							 num++;
						 } while (Matrix[num] != 32);
						 num++;
						 do{
							 EndPoint += Matrix[num];
							 num++;
						 } while (Matrix[num] != 32);
						 num++;
						 do{
							 StartPoint += Matrix[num];
							 num++;
						 } while (Matrix[num] != 32);
						 num++;
						 Petri.AddArc(Arkweight, StartPoint, EndPoint);
					 }
					 Vivod();
					 Matrix_D();
				 }
				 Enab = true;
	}
	private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
				 if (dataGridView1->ColumnCount == 0)
				 {
					 MessageBox::Show("Отсутствует матрица для сохранения !!!", "Ошибка!", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				 }
				 else
				 {
					 bool f = false;
					 DWORD BytesWrite;
					 DWORD BytesRead;
					 char BUF1[256];
					 char* readh = BUF1;
					 DWORD dwFileSizeHigh;
					 HANDLE hFile1;
					 string pr;
					 do
					 {
						 Save ty;
						 ty.ShowDialog(this);

						 hFile1 = CreateFile("prm.cpt", GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
						 ReadFile(hFile1, readh, 256, &BytesRead, NULL);

						 pr = BUF1;
						 pr += ".xml";
						 CloseHandle(hFile1);
						 DeleteFile("prm.cpt");
						 hFile1 = CreateFile(pr.c_str(), GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
						 if (hFile1 != INVALID_HANDLE_VALUE)
						 {
							 f = true;
						 }
						 else
						 {
							 MessageBox::Show("Невозможно сохранить файл с таким именем !!!", "Ошибка!", MessageBoxButtons::OK, MessageBoxIcon::Warning);
						 }
					 } while (f == false);
					 CloseHandle(hFile1);
					 int i, j;
					 ofstream save(pr.c_str(), ios::trunc);
					 save << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
					 save << "<FBType xmlns:xsi=\"http:/";
					 save << "/www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"F:\Vive_039\\";
					 save << "xmlSchema\NCESModuleNetworkExtended.xsd\" X=\"0\" Y=\"0\" Num=\"0\" LocNum=\"0\" Name=\"New\" Comment=\"_\" Width=\"45.0\" Height=\"58.0\">" << endl;
					 save << "<VersionInfo Copyright=\"\" FileVersion=\"1\" EditorVersion=\"Visual NCES Editor 2.0.0\" Author=\"\" Date=\"2015-09-16\" Description=\"\" />" << endl;
					 save << "<InterfaceList />" << endl;
					 save << "<SNS LeftPageBorder=\"-300.0\" RightPageBorder=\"300.0\">" << endl;

					 j = 0;
					 for (i = 0; i < MAXP; i++) // метки
					 {
						 save << "<place X=\"";
						 save << i * 100 - 250;
						 save << "\" Y=\"";
						 save << j * 200 - 250;
						 save << "\" Diameter=\"30.0\" Name=\"";
						 save << Petri.GetNamePosition(Petri.GetNumberPosition(i));
						 save << "\" Num=\"" << Petri.GetNumberPosition(i);
						 save << "\" LocNum=\"" << Petri.GetNumberPosition(i);
						 save << "\" Mark=\"";
						 save << Petri.GetMarkingPositions(Petri.GetNumberPosition(i));
						 save << "\" Clock=\"0\" Capacity=\"1\" Comment=\"_\">" << endl;
						 save << "<CommentBox X=\"0\" Y=\"0\" Width=\"20\" Height=\"20\" />" << endl;
						 save << "</place>" << endl;
						 if (i % 3 == 0 && i != 0)
							 j++;

					 }

					 j = 0;
					 for (i = 0; i < MAXT; i++) // переходы
					 {
						 save << "<trans X=\"";
						 save << i * 100 - 200;
						 save << "\" Y=\"";
						 save << j * 200 - 175;
						 save << "\" Width=\"30\" Height=\"20\" Num=\"" << Petri.GetNumberTtransition(i);
						 save << "\" LocNum=\"" << Petri.GetNumberTtransition(i);
						 save << "\" Name=\"";
						 save << Petri.GetNameTransition(Petri.GetNumberPosition(i));
						 save << "\" Type=\"OR\" TransInscription=\"_\" SwitchMode=\"s\" Comment=\"_\">" << endl;
						 save << " <CommentBox X=\"0\" Y=\"0\" Width=\"20\" Height=\"20\" />" << endl;
						 save << "</trans>" << endl;
						 if (i % 3 == 0 && i != 0)
							 j++;
					 }

					 for (i = 0; i < Petri.GetNumberOfArc(); i++) //дуги
					 {

						 save << "<arc StartPoint=\"";
						 save << Petri.GetNameStart(i);
						 save << "\" EndPoint=\"";
						 save << Petri.GetNameEnd(i);
						 save << "\" ArcWeight=\"";
						 save << Petri.GetWeightArc(i);
						 save << "\" TimeValue=\"\" Comment=\"_\">" << endl;
						 save << "<Point Num=\"1\" X=\"0\" Y=\"0\" />" << endl;
						 save << "<Point Num=\"2\" X=\"0\" Y=\"0\" />" << endl;
						 save << "</arc>" << endl;
					 }
					 save << "</SNS>" << endl;
					 save << "</FBType>";
					 save.close();
				 }
	}
	private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) {
				 DeleteDataFromMatrix();
				 Petri.CleaningPetriNet();
	}
	private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e) {
				 DeleteDataFromMatrix();
				 Petri.CleaningPetriNet();
				 GenericMatrix gm;
				 gm.ShowDialog(this);
				 DWORD BytesRead;
				 char BUF1[256];
				 char* readh = BUF1;
				 HANDLE hFile1;
				 string pr;
				 hFile1 = CreateFile("prm.cpt", GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
				 if (hFile1 != INVALID_HANDLE_VALUE)
				 {
					 ReadFile(hFile1, readh, 256, &BytesRead, NULL);
					 pr = BUF1;
					 CloseHandle(hFile1);
					 DeleteFile("prm.cpt");
					 int num = 0;
					 MAXP = 0;
					 do{
						 MAXP = MAXP * 10 + pr[num] - 48;
						 num++;
					 } while (pr[num] != 32);
					 MAXT = 0;
					 num++;
					 do{
						 MAXT = MAXT * 10 + pr[num] - 48;
						 num++;
					 } while (pr[num] != 32);
					 RisMatrix();
					 Petri.NewPetriNet(MAXT, MAXP);
				 }
	}
			 void FindVector(void)
			 {
				 int i;
				 Matrix D(MAXP, MAXT);

				 for (int i = 0; i < MAXP; i++)
				 {
					 for (int j = 0; j < MAXT; j++)
					 {
						 D.set_value(i, j, Convert::ToInt32(dataGridView2->Rows[j]->Cells[i]->Value) - Convert::ToInt32(dataGridView1->Rows[j]->Cells[i]->Value));

					 }
				 }
				 Matrix U0(MAXP, 1);
				 for (i = 0; i < MAXP; i++)
				 {
					 U0.set_value(i, 0, Convert::ToInt32(dataGridView5_vector->Rows[0]->Cells[i]->Value));
				 }

				 Matrix U1(MAXP, 1);
				 for (i = 0; i < MAXP; i++)
				 {
					 U1.set_value(i, 0, Convert::ToInt32(dataGridView5->Rows[0]->Cells[i]->Value));
				 }
				 Matrix S(find_vec(D, U0, U1));
				 if (S.get_value(0, 0) == -1)
				 {
					 for (int i = 0; i < MAXT; i++)
					 {
						 dataGridView6->Rows[0]->Cells[i]->Value = -1;
					 }
				 }
				 else
				 {
					 for (int i = 0; i < MAXT; i++)
					 {
						 dataGridView6->Rows[0]->Cells[i]->Value = Convert::ToInt32(S.get_value(i, 0));
					 }
				 }
			 }
	private: System::Void button7_Click(System::Object^  sender, System::EventArgs^  e) {
				 if (Enab == true)
					 FindVector();
	}
	private: System::Void dataGridView1_CellValueChanged(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
				 if (Enab == true)
				 {
					 int col = e->ColumnIndex;
					 int row = e->RowIndex;
					 Petri.SetElementMatrixInput(col,row,Convert::ToInt32(dataGridView1->Rows[row]->Cells[col]->Value));
					 FindVector();
				 }	 
	}
	private: System::Void dataGridView2_CellValueChanged(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
				 if (Enab == true)
				 {
					  int col = e->ColumnIndex;
					 int row = e->RowIndex;
					 Petri.SetElementMatrixOutput(col,row,Convert::ToInt32(dataGridView2->Rows[row]->Cells[col]->Value));
					 FindVector();
				 }
	}
	private: System::Void dataGridView5_vector_CellValueChanged(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
				 if (Enab == true)
				 {
					 int col = e->ColumnIndex;
					 Petri.SetMarkingPositions(Petri.GetNumberPosition(col), Convert::ToInt32(dataGridView5_vector->Rows[0]->Cells[col]->Value));
					 FindVector();
				 }
	}
	private: System::Void dataGridView5_CellValueChanged(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
				 if (Enab == true)
					 FindVector();
	}
	private: System::Void button7_Click_1(System::Object^  sender, System::EventArgs^  e) {
				 Form1::Close();
	}
	};
}

