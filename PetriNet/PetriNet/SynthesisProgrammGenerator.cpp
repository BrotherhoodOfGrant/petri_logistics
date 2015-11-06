/**
* @file SynthesisProgrammGenerator.cpp
* Реализация класса генерации программ синтеза
* @author Lena @date 02.11.2015
*/

#include "stdafx.h"
#include "SynthesisProgrammGenerator.h"

SynthesisProgrammGenerator::SynthesisProgrammGenerator()
{
}

SynthesisProgrammGenerator::SynthesisProgrammGenerator(int nVectorSize)
{
	m_ProgSynthesys.clear();

	for (int i = 0; i < nVectorSize; i++){
		m_ProgSynthesys.push_back(0);
	}

	m_WorkingQueue.push(new SynthesisWorkItem(
		m_ProgSynthesys,
		0,
		1,
		1));

	m_nElementsCount = nVectorSize;
}

SynthesisProgrammGenerator::SynthesisProgrammGenerator(LbfVector Restrictions)
	: nDepth(0), RestrictionsVector(Restrictions)
{
	int nElementsCount = 0;
	for (unsigned int i = 0; i < Restrictions.size(); i++){
		nElementsCount += Restrictions[i];
	}

	m_ProgSynthesys.clear();

	for (int i = 0; i < nElementsCount; i++){
		m_ProgSynthesys.push_back(0);
	}

	m_WorkingQueue.push(new SynthesisWorkItem(
		m_ProgSynthesys,
		0,
		1,
		1));

	;
	m_nElementsCount = nElementsCount;

	nCount = 0;
	TreeNodesStack.push(&m_TreeHead);
	//m_TreeState.insert(std::pair<PSythesysTreeNode, ENodeState>(&m_TreeHead, NodeStateNotVisited));

	BuildTree(&m_TreeHead, 0, 2);
}


SynthesisProgrammGenerator::~SynthesisProgrammGenerator()
{
}


bool SynthesisProgrammGenerator::GenerateSynthesisProgramm()
{
		
	while ( !m_WorkingQueue.empty() )
	{
		// извлечь из очереди очередное задание
		PSynthesisWorkItem pCurrentWorkItem = m_WorkingQueue.front();

		pCurrentWorkItem->m_ProgSynthesys[pCurrentWorkItem->m_nCurrentIndex] = pCurrentWorkItem->m_nGroupIndex;
		
		// Вектор заполнен
		if (pCurrentWorkItem->m_nCurrentIndex == pCurrentWorkItem->m_ProgSynthesys.size()-1){
			
			// удалить задание
			m_WorkingQueue.pop();

			// Если программа синтеза допустима ...
			if (IsEnable(pCurrentWorkItem->m_ProgSynthesys)){

				m_ProgSynthesys = pCurrentWorkItem->m_ProgSynthesys;
				return true;

			}
			continue;
		}

		// Продолжаем строить вектор
		int nLimitValue = MaxVectorElement(pCurrentWorkItem->m_ProgSynthesys) + 1;

		for (int i = 1; i <= nLimitValue; i++){

			m_WorkingQueue.push(new SynthesisWorkItem(
				pCurrentWorkItem->m_ProgSynthesys,
				pCurrentWorkItem->m_nCurrentIndex + 1,
				i,
				nLimitValue));
		}

		m_WorkingQueue.pop();		
	}

	return false;
}

// Найти максимальный элемент вектора
int SynthesisProgrammGenerator::MaxVectorElement(SynthesysVector &ProgSynthesis)
{
	int nMax = 0;
	for (unsigned int i = 0; i < ProgSynthesis.size(); i++){
		if (ProgSynthesis[i] > nMax){
			nMax = ProgSynthesis[i];
		}
	}
	return nMax;
}

bool SynthesisProgrammGenerator::IsMatch(SynthesysVector &Vector, int nStartIndex, int nSize)
{
	bool fMatch = false;

	if (nSize <= 1){
		return false;
	}

	for (int i = 0; i < nSize - 1; i++){
		for (int j = i + 1; j < nSize; j++){
			if (Vector[i + nStartIndex] == Vector[j + nStartIndex]){
				return true;
			}
		}
	}

	return fMatch;
}

bool SynthesisProgrammGenerator::IsEnable(SynthesysVector &ProgSynthesys)
{
	bool fUnable = false;
	int nCurrentIndex = 0;

	for (unsigned int i = 0; i < RestrictionsVector.size(); i++){

		// Если есть одинаковые числа в рамках группы, вектор не подходит
		if (IsMatch(ProgSynthesys, nCurrentIndex, RestrictionsVector[i])){
			return false;
		}

		// Переход к следующей группе
		nCurrentIndex += RestrictionsVector[i];
	}

	return true;
}

bool SynthesisProgrammGenerator::GetNextSynthesisProgramm(SynthesysVector &SynthesisProgramm)
{
	if (GenerateSynthesisProgramm()){
		SynthesisProgramm = m_ProgSynthesys;
		return true;
	}

	return false;
}

void SynthesisProgrammGenerator::PrintSeq(SynthesysVector &ProgSynthesis, int nIndex)
{
	// Вектор заполнен -> вывести результат
	if (nIndex == ProgSynthesis.size()){
		bool fUnable = false;

		
		if (IsEnable(ProgSynthesis)){
			m_SynthProgVector.push_back(ProgSynthesis);
		}
		return;
	}

	// Продолжаем строить вектор
	int nLimitValue = MaxVectorElement(ProgSynthesis) + 1;

	// Мистический алгоритм
	for (int i = 1; i <= nLimitValue; i++){
		ProgSynthesis[nIndex] = i;
		PrintSeq(ProgSynthesis, nIndex + 1);
	}

	// Скрываем следы своего пребывания
	ProgSynthesis[nIndex] = 0;
}

void SynthesisProgrammGenerator::BuildTree(PSythesysTreeNode pCurrentNode, int nDepth, int nMaxGroupsCount)
{
	if (m_nElementsCount - 1 == nDepth){
		nCount++;
		return;
	}

	for (int i = 1; i <= nMaxGroupsCount; i++){
		PSythesysTreeNode pNewNode = new SythesysTreeNode(i, max(pCurrentNode->m_nMaxValue, i));

		pCurrentNode->m_NextNodes.push_back(pNewNode);
		BuildTree(pNewNode, nDepth + 1, max(pCurrentNode->m_nMaxValue, pNewNode->m_nMaxValue) + 1);
	}
}

bool SynthesisProgrammGenerator::GetNextTreeSynthesisProgramm(SynthesysVector &SynthesisProgramm)	
{
	if (GenerateTreeSynthesisProgramm()){
		SynthesisProgramm = m_ProgSynthesys;
		return true;
	}

	return false;
}

bool SynthesisProgrammGenerator::GenerateTreeSynthesisProgramm()
{
	while (!TreeNodesStack.empty()){

		PSythesysTreeNode pCurrentNode = TreeNodesStack.top();

		//switch (m_TreeState.at(pCurrentNode))
		switch (pCurrentNode->m_NodeState)
		{
		case NodeStateNotVisited:

			m_ProgSynthesys[nDepth] = pCurrentNode->m_nNodeElement;

			// Достигнут лист дерева -> Программа синтеза получена
			if (pCurrentNode->m_NextNodes.empty()){
				pCurrentNode->m_NodeState = NodeStateClosed;
				TreeNodesStack.pop();
				nDepth--;
				return true;

			}
			else{
				// Если у узла есть зависимые, добавить первый узел в стек

				// Проверить допустимость новой ветки
				if (BranchEnable(pCurrentNode, pCurrentNode->m_NextNodes[0], nDepth, RestrictionsVector)) {
					TreeNodesStack.push(pCurrentNode->m_NextNodes[0]);					
					nDepth++;
				}

				pCurrentNode->nCurrentDependentNode = 1;
				pCurrentNode->m_NodeState = NodeStateVisited;
			}

			break;

		case NodeStateVisited:

			m_ProgSynthesys[nDepth] = pCurrentNode->m_nNodeElement;

			if (pCurrentNode->nCurrentDependentNode < pCurrentNode->m_NextNodes.size()){

				// Проверить допустимость новой ветки
				if (BranchEnable(pCurrentNode, pCurrentNode->m_NextNodes[pCurrentNode->nCurrentDependentNode], nDepth, RestrictionsVector)){
					TreeNodesStack.push(pCurrentNode->m_NextNodes[pCurrentNode->nCurrentDependentNode]);					
					nDepth++;
				}
				pCurrentNode->nCurrentDependentNode++;
			}
			else{
				nDepth--;
				TreeNodesStack.pop();
			}
			break;

		case NodeStateClosed:
			nDepth--;
			TreeNodesStack.pop();
			break;

		default:
			break;
		}

	}

	return false;
}


void SynthesisProgrammGenerator::ResetTree()
{
	if (m_nElementsCount - 1 == nDepth){
		nCount++;
		return;
	}

	for (int i = 1; i <= nMaxGroupsCount; i++){
		
		ResetTree(pNewNode, nDepth + 1, max(pCurrentNode->m_nMaxValue, pNewNode->m_nMaxValue) + 1);
	}
}

void SynthesisProgrammGenerator::Reset()
{
	ResetTree();

	nDepth = 0;
	while (!TreeNodesStack.empty()){
		TreeNodesStack.pop();
	}

	TreeNodesStack.push(&m_TreeHead);
}

bool SynthesisProgrammGenerator::BranchEnable(
	PSythesysTreeNode pCurrentNode, 
	PSythesysTreeNode pChildNode, 
	int nCurrentDepth, 
	LbfVector Restrictions)
{
	int nTotalDepth = Restrictions.at(0);
	int nStart = 0;

	// Найти в векторе ограничений элемент, соответствующий глубине текущего узла
	for (int i = 0; i < Restrictions.size() - 1; i++){

		// Группа найдена
		if (nCurrentDepth < nTotalDepth){
			break;
		}

		nTotalDepth += Restrictions.at(i + 1);
		nStart += Restrictions.at(i);
	}

	// Если подчиненный элемент находится в той же группе, ...
	if (nCurrentDepth + 1 < nTotalDepth){
		// ... они не должны быть равны
		m_ProgSynthesys[nCurrentDepth + 1] = pChildNode->m_nNodeElement;

		if (IsMatch(m_ProgSynthesys, nStart, nDepth + 2 - nStart)){
		//if (pCurrentNode->m_nNodeElement == pChildNode->m_nNodeElement){
			return false;
		}
	}

	// 
	return true;
}

