/**
* @file PetriNetSerializer.cpp
* Реалзация класса сериализации/десериализации сети Петри
* @author ... @date 02.11.2015
*/

#include "stdafx.h"

PetriNetSerializer::PetriNetSerializer()
{
}


PetriNetSerializer::~PetriNetSerializer()
{
}

Petri_Net *PetriNetSerializer::Load(_In_ String sFilePath)
{
	Petri_Net *Petri = new Petri_Net();

	char BUF1[BUFFER_SIZE];
	memset(BUF1, 0, BUFFER_SIZE);
	char* readh;
	DWORD dwFileSizeHigh;
	readh = BUF1;
	string  XLM;
	XLM.clear();
	DWORD BytesRead;

	HANDLE hFile = CreateFile((LPCWSTR)sFilePath.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return NULL;
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
		Petri->AddPosition(Marking, Number, Name);
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
		Petri->AddTransition(Number, Name);
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
		Petri->AddArc(Arkweight, StartPoint, EndPoint);
	}
	return Petri;
}

void PetriNetSerializer::Save(_In_ String sFilePath, _In_ Petri_Net &Net)
{
	int i, j;
	ofstream save(sFilePath.c_str(), ios::trunc);
	save << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
	save << "<FBType xmlns:xsi=\"http:/";
	save << "/www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"xmlSchema\NCESModuleNetworkExtended.xsd\" ";
	save << "X=\"0\" Y=\"0\" Num=\"0\" LocNum=\"0\" Name=\"New\" Comment=\"_\" Width=\"45.0\" Height=\"58.0\">" << endl;
	save << "<VersionInfo Copyright=\"\" FileVersion=\"1\" EditorVersion=\"Visual NCES Editor 2.0.0\" Author=\"\" Date=\"2015-09-16\" Description=\"\" />" << endl;
	save << "<InterfaceList/>" << endl;
	save << "<SNS LeftPageBorder=\"-300.0\" RightPageBorder=\"300.0\">" << endl;

	j = 0;
	for (i = 0; i < Net.GetNumberOfPositions(); i++) // метки
	{
		save << "<place X=\"";
		save << i * 100 - 250;
		save << "\" Y=\"";
		save << j * 200 - 250;
		save << "\" Diameter=\"30.0\" Name=\"";
		save << Net.GetNamePosition(Net.GetNumberPosition(i));
		save << "\" Num=\"" << Net.GetNumberPosition(i);
		save << "\" LocNum=\"" << Net.GetNumberPosition(i);
		save << "\" Mark=\"";
		save << Net.GetMarkingPositions(Net.GetNumberPosition(i));
		save << "\" Clock=\"0\" Capacity=\"1\" Comment=\"_\">" << endl;
		save << "<CommentBox X=\"0\" Y=\"0\" Width=\"20\" Height=\"20\" />" << endl;
		save << "</place>" << endl;
		if (i % 3 == 0 && i != 0)
			j++;

	}

	j = 0;
	for (i = 0; i < Net.GetNumberOfTransitions(); i++) // переходы
	{
		save << "<trans X=\"";
		save << i * 100 - 200;
		save << "\" Y=\"";
		save << j * 200 - 175;
		save << "\" Width=\"30\" Height=\"20\" Num=\"" << Net.GetNumberTtransition(i);
		save << "\" LocNum=\"" << Net.GetNumberTtransition(i);
		save << "\" Name=\"";
		save << Net.GetNameTransition(Net.GetNumberTtransition(i));
		save << "\" Type=\"OR\" TransInscription=\"_\" SwitchMode=\"s\" Comment=\"_\">" << endl;
		save << " <CommentBox X=\"0\" Y=\"0\" Width=\"20\" Height=\"20\" />" << endl;
		save << "</trans>" << endl;
		if (i % 3 == 0 && i != 0)
			j++;
	}

	for (i = 0; i < Net.GetNumberOfArc(); i++) //дуги
	{

		save << "<arc StartPoint=\"";
		save << Net.GetNameStart(i);
		save << "\" EndPoint=\"";
		save << Net.GetNameEnd(i);
		save << "\" ArcWeight=\"";
		save << Net.GetWeightArc(i);
		save << "\" TimeValue=\"\" Comment=\"_\">" << endl;
		save << "<Point Num=\"1\" X=\"0\" Y=\"0\" />" << endl;
		save << "<Point Num=\"2\" X=\"0\" Y=\"0\" />" << endl;
		save << "</arc>" << endl;
	}
	save << "</SNS>" << endl;
	save << "</FBType>";
	save.close();
}