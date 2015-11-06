/**
* @file SynthesisProgrammGenerator.h
* ����������� ������ ��������� �������� �������
* @author Lena @date 02.11.2015
*/

#pragma once

#include <queue>
#include <map>
#include <stack>

// ���������, ����������� ��������� ������ ��������� ��������� �������
struct SynthesisWorkItem{

	SynthesisWorkItem(SynthesysVector ProgSynthesys, int nIndex, int nGroupIndex, int nMaxGroupIndex)
		:m_ProgSynthesys(ProgSynthesys), m_nCurrentIndex(nIndex), m_nGroupIndex(nGroupIndex), m_nMaxGroupIndex(nMaxGroupIndex){}

	// ������ �������� �������� 
	int m_nCurrentIndex;

	// ������� ����� ������
	int m_nGroupIndex;

	// ����������� ��������� ����� ������
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

	// ������� ������� ��������� �������
	int m_nNodeElement;

	int m_nMaxValue;

	int nCurrentDependentNode;

	// ������ ����������� ���������
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
	* ������������� ����������
	* @param[in] nVectorSize - ������ �������
	*/
	SynthesisProgrammGenerator(int nVectorSize);

	/**
	* ������������� ����������
	* @param[in] nVectorSize - ������ �������
	* @param[in] Restrictions - ������ �����������
	*/
	SynthesisProgrammGenerator(LbfVector Restrictions);

	/**
	* �������� ��������� ��������� �������
	* @param[in] SynthesisProgramm - ������, ������� ����� ��������
	*/
	bool GetNextSynthesisProgramm(SynthesysVector &SynthesisProgramm);

	bool GetNextTreeSynthesisProgramm(SynthesysVector &SynthesisProgramm);

	void Reset();

	/**
	* ��������� ������������ ����� ������
	*/
	bool BranchEnable(PSythesysTreeNode pCurrentNode, PSythesysTreeNode pChildNode, int nCurrentDepth, LbfVector Restrictions);


	// ��� �������: ����� ����������� �������
	void PrintSeq(SynthesysVector &ProgSynthesis, int nIndex);

private:
	/**
	* ������������ ��������� �������
	* @param[in] ProgSynthesys - ������� ��������� �������
	* @param[in] nIndex - ������ �������� �������� ��������� �������
	* @remarks ������� ����������
	*/
	bool GenerateSynthesisProgramm();

	bool GenerateTreeSynthesisProgramm();

	/**
	* ����� ������������ ������� �������
	* @param[in] ProgSynthesys - ������������� ������
	*/
	int MaxVectorElement(SynthesysVector &ProgSynthesys);

	/**
	* ������� �� �� ������� ������� ������� ������������� ��������
	* @param[in] Vector - ������������� ������
	* @param[in] nStartIndex - ������ ������� �������� �� �������
	* @param[in] nSize - ����� �������
	*/
	bool IsMatch(SynthesysVector &Vector, int nStartIndex, int nSize);

	/**
	* �������� �� ��������� ������� ����������
	* @param[in] ProgSynthesys - ������������� ������
	*/
	bool IsEnable(SynthesysVector &ProgSynthesys);

	void BuildTree(PSythesysTreeNode pCurrentNode, int nDepth, int nMaxGroupsCount);

	void ResetTree();

	//////////////////////////////////////////////////////////////////////////

	// ������ �����������
	LbfVector RestrictionsVector;

	int m_nElementsCount;

	// ���������� ���������� �������� �������
	int nEnable;

	// ����� ���������� �������� �������
	int nCount;

	// ������� ��������� �������
	SynthesysVector m_ProgSynthesys;

	// ������� �������
	queue<PSynthesisWorkItem> m_WorkingQueue;

	SythesysTreeNode m_TreeHead;

	vector<SynthesysVector> m_SynthProgVector;	

	//map< PSythesysTreeNode, ENodeState> m_TreeState;

	stack<PSythesysTreeNode> TreeNodesStack;

	int nDepth;
};

