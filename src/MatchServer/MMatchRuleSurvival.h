#ifndef _MMATCHRULE_SURVIVAL_H
#define _MMATCHRULE_SURVIVAL_H

#include "MMatchRule.h"
#include "MMatchRuleBaseQuest.h"
#include "MMatchNPCObject.h"
#include "MMatchQuestRound.h"

class MMatchRuleSurvival : public MMatchRuleBaseQuest {
protected:
	u64							m_nRountStartTime;
	MMatchQuestRound			m_QuestRound;
	bool						m_bReservedNextRound;
	u64							m_nReversedNextRoundTime;
protected:
	virtual void OnBegin();
	virtual void OnEnd();
	virtual bool OnRun();
//	virtual void OnRoundBegin();						// ���� ������ ��
//	virtual void OnRoundEnd();							// ���� ���� ��
//	virtual bool OnCheckRoundFinish();					// ���尡 �������� üũ
//	virtual void OnRoundTimeOut();						// ���尡 Ÿ�Ӿƿ����� ����� �� OnRoundEnd() ���̴�.
//	virtual bool RoundCount();							// ���� ī��Ʈ. ��� ���尡 ������ false�� ��ȯ�Ѵ�.
//	virtual bool OnCheckEnableBattleCondition();		// ���� �������� üũ

	virtual void OnCommand(MCommand* pCommand);			// ����Ʈ������ ����ϴ� Ŀ�ǵ� ó��


	virtual void ProcessNPCSpawn();
	virtual bool CheckNPCSpawnEnable();					// NPC�� ���� �������� ����
	virtual void RouteGameInfo();
	virtual void RouteStageGameInfo();			///< ����� ������������ �ٲ� ���� ������ �����ش�.
	virtual void RouteCompleted() {}
	virtual void RouteFailed() {}
	virtual void DistributeReward();


	void ProcessRound();
	void QuestRoundStart();
public:
	void RouteQuestRoundStart();
public:
	MMatchRuleSurvival(MMatchStage* pStage);
	virtual ~MMatchRuleSurvival();
	virtual MMATCH_GAMETYPE GetGameType() { return MMATCH_GAMETYPE_SURVIVAL; }
};











#endif