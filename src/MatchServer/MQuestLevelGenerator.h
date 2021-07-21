#pragma once

#include "MQuestConst.h"

class MQuestLevel;


/// ����Ʈ ���� ������ִ� Ŭ���� 
/// - ���� �������� �Ǿ��ִ�.
class MQuestLevelGenerator
{
private:
	int					m_nPlayerQL;
	int					m_nMapsetID;
	int					m_nScenarioID;
	unsigned int		m_nSacriQItemID[MAX_SCENARIO_SACRI_ITEM];

	int MakeScenarioID();
public:
	MQuestLevelGenerator();
	~MQuestLevelGenerator();

	void BuildPlayerQL(int nQL);
	void BuildMapset(int nMapsetID);
	void BuildSacriQItem(unsigned int nItemID);

	int ReturnScenarioID();
	MQuestLevel* MakeLevel();
};