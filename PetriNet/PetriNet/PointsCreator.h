#pragma once
struct PointD
{
	double F1;
	double F2;
	double F3;
	double F4;
	double F5;

	PointD(double _F1, double _F2, double _F3, double _F4, double _F5)
	{
		this->F1 = _F1;
		this->F2 = _F2;
		this->F3 = _F3;
		this->F4 = _F4;
		this->F5 = _F5;
	};
	PointD() {};
};
static class PointsCreator
{
private:
	//функция расчета суммы весов входных и выходных позиций сети
	static int FindSumPositionsWeight(Petri_Net* pNet);
	static bool OpenFile(LPCWSTR filePath, HANDLE &hFile);
	static bool CloseFile(HANDLE hFile);
	//расчет и запись точек в файл
	static bool WriteToFile(HANDLE hFile, AlternativeNest* altNets, vector<int> UniteOperationsVector, bool newMethod);
	
	PointsCreator();
	~PointsCreator();

public:
	static bool CreatePoints(AlternativeNest* altNets, vector<int> UniteOperationsVector, LPCWSTR filePath, bool fNewMethd);
};

