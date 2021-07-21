#ifndef _ZQUEST_H
#define _ZQUEST_H

#include "ZGlobal.h"
#include "MBaseQuest.h"
#include "ZQuestMap.h"
#include "ZQuestGameInfo.h"
#include "ZMyItemList.h"

#include <set>

enum ZQuestCheetType
{
	ZQUEST_CHEET_GOD			= 0,		// �������
	ZQUEST_CHEET_WEAKNPCS		= 1,		// �������� 1
	ZQUEST_CHEET_AMMO			= 2,		// �Ѿ˸���
	ZQUEST_CHEET_MAX
};

// ����Ʈ ���� ���� Ŭ����
class ZQuest : public MBaseQuest
{
private:
	set<MUID>	m_CharactersGone;	// �������ͷ� �̵��� ĳ���͵�

	ZQuestGameInfo		m_GameInfo;
	bool	m_Cheet[ZQUEST_CHEET_MAX];
	bool	m_bCreatedOnce;
	bool	m_bLoaded;
	bool	m_bIsQuestComplete;
	bool	m_bIsRoundClear;
	DWORD	m_tRemainedTime;					// ���尡 ������ ���� ����� �Ѿ����� ���� �ð�
	float	m_fLastWeightTime;

	MQuestCombatState	m_QuestCombatState;


#ifdef _QUEST_ITEM
	int				m_nRewardXP;				// ����Ʈ���� ȹ���� ����ġ.
	int				m_nRewardBP;				// ����Ʈ���� ȹ���� �ٿ�Ƽ.
	
    bool OnRewardQuest( MCommand* pCmd );
	bool OnNewMonsterInfo( MCommand* pCmd );	// ���� �𰨿� ��ϵ� ���� ������ ���� ����.

	void GetQuestTotalSpawnItemList( void* pObtainQuestItemKindListBlob );
	void GetMyObtainQuestItemList( int nRewardXP, int nRewardBP, void* pMyObtainQuestItemListBlob, void* pMyObtainZItemListBlob );

public :
	int GetRewardXP( void)							{ return m_nRewardXP; }
	int GetRewardBP( void)							{ return m_nRewardBP; }
	bool IsQuestComplete( void)						{ return m_bIsQuestComplete; }
	bool IsRoundClear( void)						{ return m_bIsRoundClear; }
	DWORD GetRemainedTime( void)					{ return m_tRemainedTime; }

	MQuestCombatState GetQuestState()				{ return m_QuestCombatState; }

#endif

	bool OnNPCSpawn(MCommand* pCommand);
	bool OnNPCDead(MCommand* pCommand);
	bool OnPeerNPCDead(MCommand* pCommand);
	bool OnEntrustNPCControl(MCommand* pCommand);
	bool OnPeerNPCBasicInfo(MCommand* pCommand);
	bool OnPeerNPCHPInfo(MCommand* pCommand);
	bool OnPeerNPCAttackMelee(MCommand* pCommand);
	bool OnPeerNPCAttackRange(MCommand* pCommand);
	bool OnPeerNPCSkillStart(MCommand* pCommand);
	bool OnPeerNPCSkillExecute(MCommand* pCommand);
	bool OnRefreshPlayerStatus(MCommand* pCommand);
	bool OnClearAllNPC(MCommand* pCommand);
	bool OnQuestRoundStart(MCommand* pCommand);
	bool OnQuestPlayerDead(MCommand* pCommand);
	bool OnQuestGameInfo(MCommand* pCommand);
	bool OnQuestCombatState(MCommand* pCommand);
	bool OnMovetoPortal(MCommand* pCommand);
	bool OnReadyToNewSector(MCommand* pCommand);
	bool OnSectorStart(MCommand* pCommand);
	bool OnObtainQuestItem(MCommand* pCommand);
	bool OnObtainZItem(MCommand* pCommand);
	bool OnSectorBonus(MCommand* pCommand);
	bool OnQuestCompleted(MCommand* pCommand);
	bool OnQuestFailed(MCommand* pCommand);
	bool OnQuestPing(MCommand* pCommand);


	ZQuestMap			m_Map;
	void LoadNPCMeshes();
	void LoadNPCSounds();
	void MoveToNextSector();
	void UpdateNavMeshWeight(float fDelta);
protected:
	virtual bool OnCreate();
	virtual void OnDestroy();
	bool OnCreateOnce();
	void OnDestroyOnce();
public:
	ZQuest();
	virtual ~ZQuest();
public:
	void OnGameCreate();
	void OnGameDestroy();
	void OnGameUpdate(float fElapsed);
	bool OnCommand(MCommand* pCommand);				///< ���� �̿ܿ� ������� Ŀ�ǵ� ó��
	bool OnGameCommand(MCommand* pCommand);			///< ������ ������� Ŀ�ǵ� ó��

	void SetCheet(ZQuestCheetType nCheetType, bool bValue);
	bool GetCheet(ZQuestCheetType nCheetType);

	void Reload();
	bool Load();


	// interface
	ZQuestGameInfo* GetGameInfo()		{ return &m_GameInfo; }

	// ���¿� ������� ���ɼ� �ִ� ����Ʈ ���õ� Ŀ�ǵ�.
	bool OnSetMonsterBibleInfo( MCommand* pCmd );


	bool OnPrePeerNPCAttackMelee(MCommand* pCommand);	// ������ ó���ϴ°� ��Ÿ�̹� �ʴ�
	
};




/////////////////////////////////////////////////////////////////////

inline void ZQuest::SetCheet(ZQuestCheetType nCheetType, bool bValue) 
{ 
	m_Cheet[nCheetType] = bValue; 
}

inline bool ZQuest::GetCheet(ZQuestCheetType nCheetType) 
{ 
	if (!ZIsLaunchDevelop()) return false;
	return m_Cheet[nCheetType];
}



#endif