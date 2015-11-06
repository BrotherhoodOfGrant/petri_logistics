/**
* @file SynthesisProgrammGenerator.h
* Определение класса генерации программ синтеза
* @author Lena @date 02.11.2015
*/

#pragma once

#include <queue>
#include <map>
#include <stack>

// Структура, описывающая единичную задачу генерации программы синтеза
struct SynthesisWorkItem{

	SynthesisWorkItem(SynthesysVector ProgSynthesys, int nIndex, int nGroupIndex, int nMaxGroupIndex)
		:m_ProgSynthesys(ProgSynthesys), m_nCurrentIndex(nIndex), m_nGroupIndex(nGroupIndex), m_nMaxGroupIndex(nMaxGroupIndex){}

	// Индекс текущего элемента 
	int m_nCurrentIndex;

	// Текущий номер группы
	int m_nGroupIndex;

	// Максимально возможный номер группы
	int m_nMaxGroupIndex;

	SynthesysVector m_ProgSynthesys;
};
typedef SynthesisWorkItem * PSynthesisWorkItem;

enum ENodeState{
	NodeStateNotVisited,
	NodeStateVisited,
	NodeStateClosed
};

struct SythesysTreeNode{

	SythesysTreeNode(int nElement, int nMaxValue)
		: m_nNodeElement(nElement), m_nMaxValue(nMaxValue), nCurrentDependentNode(0), m_NodeState(NodeStateNotVisited){}

	SythesysTreeNode()
		: m_nNodeElement(1), m_nMaxValue(1), nCurrentDependentNode(0), m_NodeState(NodeStateNotVisited){}

	// Текущий элемент программы синтеза
	int m_nNodeElement;

	int m_nMaxValue;

	int nCurrentDependentNode;

	// массив подчиненных элементов
	vector<SythesysTreeNode *> m_NextNodes;

	ENodeState m_NodeState;
};
typedef SythesysTreeNode * PSythesysTreeNode;

class SynthesisProgrammGenerator
{
public:
	SynthesisProgrammGenerator();
	~SynthesisProgrammGenerator();

	/**
	* Инициализация генератора
	* @param[in] nVectorSize - Размер вектора
	*/
	SynthesisProgrammGenerator(int nVectorSize);

	/**
	* Инициализация генератора
	* @param[in] nVectorSize - Размер вектора
	* @param[in] Restrictions - Вектор ограничений
	*/
	SynthesisProgrammGenerator(LbfVector Restrictions);

	/**
	* Получить следующую программу синтеза
	* @param[in] SynthesisProgramm - Вектор, который будет заполнен
	*/
	bool GetNextSynthesisProgramm(SynthesysVector &SynthesisProgramm);

	bool GetNextTreeSynthesisProgramm(SynthesysVector &SynthesisProgramm);

	void Reset();

	/**
	* Проверить допустимость ветки дерева
	*/
	bool BranchEnable(PSythesysTreeNode pCurrentNode, PSythesysTreeNode pChildNode, int nCurrentDepth, LbfVector Restrictions);


	// Для отладки: самый рекурсивный вариеат
	void PrintSeq(SynthesysVector &ProgSynthesis, int nIndex);

private:
	/**
	* Сформировать программу синтеза
	* @param[in] ProgSynthesys - Текущая программа синтеза
	* @param[in] nIndex - Индекс текущего элемента программы синтеза
	* @remarks Функция рекурсивна
	*/
	bool GenerateSynthesisProgramm();

	bool GenerateTreeSynthesisProgramm();

	/**
	* Найти максимальный элемент вектора
	* @param[in] ProgSynthesys - Анализируемый вектор
	*/
	int MaxVectorElement(SynthesysVector &ProgSynthesys);

	/**
	* Имеются ли на данному отрезке вектора повторяющиеся элементы
	* @param[in] Vector - Анализируемый вектор
	* @param[in] nStartIndex - Индекс первого элемента на отрезке
	* @param[in] nSize - Длина отрезка
	*/
	bool IsMatch(SynthesysVector &Vector, int nStartIndex, int nSize);

	/**
	* Является ли программа синтеза допустимой
	* @param[in] ProgSynthesys - Анализируемый вектор
	*/
	bool IsEnable(SynthesysVector &ProgSynthesys);

	void BuildTree(PSythesysTreeNode pCurrentNode, int nDepth, int nMaxGroupsCount);

	void ResetTree();

	//////////////////////////////////////////////////////////////////////////

	// Вектор ограничений
	LbfVector RestrictionsVector;

	int m_nElementsCount;

	// Количество допустимых программ синтеза
	int nEnable;

	// Общее количество программ синтеза
	int nCount;

	// Текущая программа синтеза
	SynthesysVector m_ProgSynthesys;

	// Очередь заданий
	queue<PSynthesisWorkItem> m_WorkingQueue;

	SythesysTreeNode m_TreeHead;

	vector<SynthesysVector> m_SynthProgVector;	

	//map< PSythesysTreeNode, ENodeState> m_TreeState;

	stack<PSythesysTreeNode> TreeNodesStack;

	int nDepth;
};

