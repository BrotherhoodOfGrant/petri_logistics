// PetriNet.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	String filePath;
	String resultDir;
	
	vector<Petri_Net*>* altNets1 = AltStructsSynthesizer::Synthesise(NULL, NULL);


	if (argc > 2)
	{
		filePath = argv[0];
		resultDir = argv[1];
	}
	else
	{
		printf("��������� ����������� � ����������� ��������� ������ : <���� � xml - ����� � ��������� �������� ����> <���� � ����� ��� �������������� ������>");
		return -1;
	}

	// TODO �������� ���� �� xml-����� ����� � ����
	Petri_Net* srcNet = PetriNetSerializer::Load(filePath);

	// TODO ��������� �� ��� ������ � �����
	Petri_Net* lbfNet = SrcToLbfSeparator::Separate(*srcNet);

	// TODO ��������� �� ��������� � ������������ ������� ������ � ������
	Matrix* tensor;

	Petri_Net* primitiveNet = LbfToPrimitiveSeparator::Separate(*lbfNet, tensor);

	// TODO ������ �������������� ������� ����, ����, ��������
	vector<Petri_Net*>* altNets = AltStructsSynthesizer::Synthesise(lbfNet, primitiveNet);

	// TODO �������������� � �������� ������� ��������� ������ � ������
	InverseTransformer::Transform(*altNets, *tensor);

	// TODO �������� ��������������� �������
	EquivalenceChecker::Check(*srcNet, *altNets);

	// TODO ���������� ������������� ����� � xml-����� ����� � ����
	for (int i = 0; i < altNets->size(); i++)
	{
		//Ostringstream stringStream;
		//stringStream << resultDir << "\\" << i << ".xml";
		//String savePath = stringStream.str();
		//PetriNetSerializer::Save(savePath, (altNets[i]));
	}

	//TODO ������ � ���� ������ ��� ���������� ��������


	return 0;
}

