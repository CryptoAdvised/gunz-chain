#ifndef _MMATCHQUEST_H
#define _MMATCHQUEST_H

#include "MBaseQuest.h"
#include "MQuestScenario.h"


/// ������ ����Ʈ �ְ� ���� Ŭ����
class MMatchQuest : public MBaseQuest
{
protected:
	virtual bool OnCreate();				///< �ʱ�ȭ
	virtual void OnDestroy();				///< ����
	

	MQuestNPCSetCatalogue		m_NPCSetCatalogue;						///< NPC Set ����
	MQuestScenarioCatalogue		m_ScenarioCatalogue;					///< �ó����� ����

public:
	MMatchQuest();														///< ������
	virtual ~MMatchQuest();												///< �Ҹ���

	inline MQuestNPCSetInfo* GetNPCSetInfo(int nID);					///< NPC Set ���� ��ȯ
	inline MQuestNPCSetInfo* GetNPCSetInfo(const char* szName);			///< NPC Set ���� ��ȯ
	inline MQuestScenarioCatalogue* GetScenarioCatalogue();				///< �ó����� ���� ��ȯ
	inline MQuestScenarioInfo*		GetScenarioInfo(int nScenarioID);	///< �ó����� ���� ��ȯ

};




inline MQuestNPCSetInfo* MMatchQuest::GetNPCSetInfo(int nID)
{
	return m_NPCSetCatalogue.GetInfo(nID);
}

inline MQuestNPCSetInfo* MMatchQuest::GetNPCSetInfo(const char* szName)
{
	return m_NPCSetCatalogue.GetInfo(szName);
}

inline MQuestScenarioCatalogue* MMatchQuest::GetScenarioCatalogue()
{
	return &m_ScenarioCatalogue;
}

inline MQuestScenarioInfo* MMatchQuest::GetScenarioInfo(int nScenarioID)
{
	return m_ScenarioCatalogue.GetInfo(nScenarioID);
}


#endif