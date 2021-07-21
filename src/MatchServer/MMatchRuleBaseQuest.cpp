#include "stdafx.h"
#include "MMatchRuleBaseQuest.h"
#include "MMath.h"
#include "MBlobArray.h"
#include "MQuestFormula.h"
#include "MQuestLevelGenerator.h"


const int NPC_ASSIGN_DELAY = 5000;
const int LATENCY_CHECK_DELAY = 5000;
const int PING_LOST_LIMIT = 2000;


//////////////////////////////////////////////////////////////////////////////////
MMatchRuleBaseQuest::MMatchRuleBaseQuest(MMatchStage* pStage) 
		:	MMatchRule(pStage), m_nLastNPCSpawnTime(0), m_nNPCSpawnCount(0),
			m_nSpawnTime(500), m_nFirstPlayerCount(1)
{
	
}

MMatchRuleBaseQuest::~MMatchRuleBaseQuest()
{
	
}

void MMatchRuleBaseQuest::OnBegin()
{
	m_PlayerManager.Create(m_pStage);
	m_NPCManager.Create(m_pStage, &m_PlayerManager);
m_nFirstPlayerCount = (int)m_pStage->GetObjCount();
	m_nNPCSpawnCount=0;

	// ���� ������ �� �������� ������.
	RouteGameInfo();

	m_bQuestCompleted = false;
}

void MMatchRuleBaseQuest::OnEnd()
{
	m_NPCManager.Destroy();
	m_PlayerManager.Destroy();
}

bool MMatchRuleBaseQuest::OnRun()
{
	if (GetRoundState() == MMATCH_ROUNDSTATE_PLAY)
	{
		SendClientLatencyPing();
		ReAssignNPC();
	}

	return MMatchRule::OnRun();
}

void MMatchRuleBaseQuest::OnRoundBegin()
{
	MMatchRule::OnRoundBegin();

	m_nLastNPCAssignCheckTime = MMatchServer::GetInstance()->GetGlobalClockCount();
	m_nLastPingTime = MMatchServer::GetInstance()->GetGlobalClockCount();
}

void MMatchRuleBaseQuest::OnRoundEnd()
{
	MMatchRule::OnRoundEnd();

}

bool MMatchRuleBaseQuest::OnCheckRoundFinish()
{
	if (CheckPlayersAlive() == false)
	{
		/// �� ������ ������. => ���� ����� �뺸�ϴ� ������� �����Ǿ�� ��. - by �߱���.

		// �� �׾������� �׳� ������ ���� ����Ʈ�� ���е� ������ ������ �Ǿ�� �Ѵ�.
		// ����� �� �׾������� ������ �׳� ������ ���������� ����Ʈ�� ���������� ���� ������ ó���� �Ѵ�.

#ifdef _QUEST_ITEM
		// ����Ʈ ���и� ���⼭ �ٷ� ó������.
		OnFailed();
#endif

		return true;
	}

	// Quest Completed�Ǿ����� ���� �ð��� ����ȴ�. ������ �׳� �ٷ�..-_-��
	if (m_bQuestCompleted)
	{
		return true;
	}



	return false;
}

void MMatchRuleBaseQuest::OnRoundTimeOut()
{
	MMatchRule::OnRoundTimeOut();
}

// ��ȯ���� false�̸� ������ ������.
bool MMatchRuleBaseQuest::RoundCount()
{
	if (++m_nRoundCount < 1) return true;
	return false;
}

bool MMatchRuleBaseQuest::OnCheckEnableBattleCondition()
{
	return true;
}

void MMatchRuleBaseQuest::OnLeaveBattle(MUID& uidChar)
{
	if (GetRoundState() == MMATCH_ROUNDSTATE_PLAY)
	{
	}
	MMatchObject* pObj = MMatchServer::GetInstance()->GetObject(uidChar);
	if (IsAdminGrade(pObj) && pObj->CheckPlayerFlags(MTD_PlayerFlags_AdminHide)) return;

	m_NPCManager.OnDelPlayer(uidChar);
	m_PlayerManager.DelPlayer(uidChar);
}

void MMatchRuleBaseQuest::OnEnterBattle(MUID& uidChar)
{

}

void MMatchRuleBaseQuest::OnCommand(MCommand* pCommand)
{



}

void MMatchRuleBaseQuest::OnRequestNPCDead(MUID& uidSender, MUID& uidKiller, MUID& uidNPC, MVector& pos)
{
	if (m_NPCManager.IsControllersNPC(uidSender, uidNPC))
	{
		MQuestDropItem DropItem;
		if (m_NPCManager.DestroyNPCObject(uidNPC, DropItem))
		{
			MCommand* pNew = MMatchServer::GetInstance()->CreateCommand(MC_QUEST_NPC_DEAD, uidSender);
			pNew->AddParameter(new MCmdParamUID(uidKiller));
			pNew->AddParameter(new MCmdParamUID(uidNPC));
			MMatchServer::GetInstance()->RouteToBattle(m_pStage->GetUID(), pNew);

			CheckRewards(uidKiller, &DropItem, pos);
		}
	}
	else
	{
		if(m_NPCManager.GetNPCObject(uidNPC)==NULL) {
			// finish�� ���Ŀ��� npc���� Ŭ����� �����̴�
			//_ASSERT(0);
		}else {
			// �������ִ�.
			_ASSERT(0);
		}
	}
}

void MMatchRuleBaseQuest::OnRequestPlayerDead(const MUID& uidVictim)
{

}

void MMatchRuleBaseQuest::CheckRewards(MUID& uidPlayer, MQuestDropItem* pDropItem, MVector& pos)
{
	MMatchObject* pPlayer = MMatchServer::GetInstance()->GetObject(uidPlayer);
	if (!pPlayer) return;

	switch (pDropItem->nDropItemType)
	{
	case QDIT_WORLDITEM:
		{
			int nSpawnItemID = pDropItem->nID;
			int nWorldItemExtraValues[WORLDITEM_EXTRAVALUE_NUM];
			for (int i = 0; i < WORLDITEM_EXTRAVALUE_NUM; i++) nWorldItemExtraValues[i] = 0;

			m_pStage->SpawnServerSideWorldItem(pPlayer, nSpawnItemID, pos.x, pos.y, pos.z, 
											   QUEST_DYNAMIC_WORLDITEM_LIFETIME, nWorldItemExtraValues );
		};
		break;
	case QDIT_QUESTITEM:
		{
			int nSpawnItemID		= QUEST_WORLDITEM_ITEMBOX_ID;

			int nQuestItemID		= pDropItem->nID;
			int nRentPeriodHour		= 0;

			int nWorldItemExtraValues[WORLDITEM_EXTRAVALUE_NUM];
			nWorldItemExtraValues[0] = nQuestItemID;
			nWorldItemExtraValues[1] = nRentPeriodHour;

			m_pStage->SpawnServerSideWorldItem(pPlayer, nSpawnItemID, pos.x, pos.y, pos.z, 
											   QUEST_DYNAMIC_WORLDITEM_LIFETIME, nWorldItemExtraValues );
		}
		break;
	case QDIT_ZITEM:
		{
			int nSpawnItemID		= QUEST_WORLDITEM_ITEMBOX_ID;
			int nQuestItemID		= pDropItem->nID;
			int nRentPeriodHour		= pDropItem->nRentPeriodHour;

			int nWorldItemExtraValues[WORLDITEM_EXTRAVALUE_NUM];
			nWorldItemExtraValues[0] = nQuestItemID;
			nWorldItemExtraValues[1] = nRentPeriodHour;

			m_pStage->SpawnServerSideWorldItem(pPlayer, nSpawnItemID, pos.x, pos.y, pos.z, 
											   QUEST_DYNAMIC_WORLDITEM_LIFETIME, nWorldItemExtraValues );
		}
		break;
	};
}

void MMatchRuleBaseQuest::RefreshPlayerStatus()
{
	for (auto i=m_pStage->GetObjBegin(); i!=m_pStage->GetObjEnd(); i++)
	{
		MMatchObject* pObj = i->second;
		if (pObj->GetEnterBattle() == false) continue;	// ��Ʋ�����ϰ� �ִ� �÷��̾ üũ
		if (IsAdminGrade(pObj) && pObj->CheckPlayerFlags(MTD_PlayerFlags_AdminHide)) continue;

		// ��� ��Ȱ
		pObj->SetAlive(true);
	}

	MCommand* pCmd = MMatchServer::GetInstance()->CreateCommand(MC_QUEST_REFRESH_PLAYER_STATUS, MUID(0,0));
	MMatchServer::GetInstance()->RouteToStage(GetStage()->GetUID(), pCmd);
}

void MMatchRuleBaseQuest::ClearAllNPC()
{
	m_NPCManager.ClearNPC();
	m_nNPCSpawnCount = 0;

	MCommand* pCmd = MMatchServer::GetInstance()->CreateCommand(MC_QUEST_NPC_ALL_CLEAR, MUID(0,0));
	MMatchServer::GetInstance()->RouteToStage(GetStage()->GetUID(), pCmd);
}


bool MMatchRuleBaseQuest::CheckPlayersAlive()
{
	int nAliveCount = 0;
	MMatchObject* pObj;
	for (auto i=m_pStage->GetObjBegin(); i!=m_pStage->GetObjEnd(); i++)
	{
		pObj = i->second;
		if (pObj->GetEnterBattle() == false) continue;	// ��Ʋ�����ϰ� �ִ� �÷��̾ üũ
		if (IsAdminGrade(pObj) && pObj->CheckPlayerFlags(MTD_PlayerFlags_AdminHide)) continue;

		if (pObj->CheckAlive()==true)
		{
			++nAliveCount;
		}
	}

	// ��� �׾����� ����
	if (nAliveCount == 0) return false;

	return true;
}



MMatchNPCObject* MMatchRuleBaseQuest::SpawnNPC(MQUEST_NPC nNPC, int nPosIndex)
{
	MMatchNPCObject* pNPCObject = m_NPCManager.CreateNPCObject(nNPC, nPosIndex);
	if (pNPCObject)
	{
		m_nNPCSpawnCount++;
	}

	return pNPCObject;
}


void MMatchRuleBaseQuest::OnRequestTestNPCSpawn(int nNPCType, int nNPCCount)
{
	for (int i = 0; i < nNPCCount; i++)
	{
		int nPosIndex = RandomNumber(0, 26);
        SpawnNPC(MQUEST_NPC(nNPCType), nPosIndex);
	}
}


void MMatchRuleBaseQuest::OnRequestTestClearNPC()
{
	ClearAllNPC();
}


void MMatchRuleBaseQuest::OnCompleted()
{
	m_bQuestCompleted = true;
	DistributeReward();
	RouteCompleted();
}


void MMatchRuleBaseQuest::OnFailed()
{
	RouteFailed();
}

void MMatchRuleBaseQuest::PreProcessLeaveStage( const MUID& uidLeaverUID )
{
}


void MMatchRuleBaseQuest::CheckMonsterBible( const MUID& uidUser, const int nMonsterBibleIndex )
{
	if( 0 > nMonsterBibleIndex )
		return;

	MMatchObject* pObj = MMatchServer::GetInstance()->GetObject( uidUser );
	if( !IsEnabledObject(pObj) )
		return;

	if( 0 == MMatchServer::GetInstance()->FindStage(pObj->GetStageUID()) )
		return;

	if( (0 > nMonsterBibleIndex) || (MAX_DB_MONSTERBIBLE_SIZE <= nMonsterBibleIndex) )
		return;

	// ���⼭ ó��.

	MMatchCharInfo* pCharInfo = pObj->GetCharInfo();
	if( 0 == pCharInfo )
		return;
	
	if( pCharInfo->m_QMonsterBible.IsKnownMonster(nMonsterBibleIndex) )
		return;

	pCharInfo->m_QMonsterBible.WriteMonsterInfo( nMonsterBibleIndex );

	PostNewMonsterInfo( pObj->GetUID(), nMonsterBibleIndex );


#ifdef _DEBUG
	// ó�� ȹ���� ���� ����.
	mlog( "MMatchRuleBaseQuest::CheckMonsterBible - New obtain monster info:%d\n", nMonsterBibleIndex );

	// ���� ������ �ִ� ���� ����.
	MQuestMonsterBible qmb = pCharInfo->m_QMonsterBible;
	for( int i = 0; i < MAX_DB_MONSTERBIBLE_SIZE; ++i )
	{
		if( 0 == qmb[ i ] )
			continue;

		MQuestNPCInfo* pNPCInfo = MMatchServer::GetInstance()->GetQuest()->GetNPCIndexInfo( i );
		ASSERT( 0 != pNPCInfo );
		mlog( "MMatchRuleBaseQuest::CheckMonsterBible - Monster name : %s, Bible index : %d\n", pNPCInfo->szName, i );
	}	
#endif
}


void MMatchRuleBaseQuest::PostNewMonsterInfo( const MUID& uidUser, const char nMonIndex )
{
	if( 0 == MMatchServer::GetInstance()->GetObject(uidUser) )
		return;

	if( 0 > nMonIndex )
		return;

	// ���⼭ �ٷ� ó�� ������ ���� ������ ������.
	MCommand* pMonInfoCmd = MMatchServer::GetInstance()->CreateCommand( MC_MATCH_NEW_MONSTER_INFO, uidUser );
	if( 0 == pMonInfoCmd )
	{
		mlog( "MMatchRuleBaseQuest::CheckMonsterBible - ���� ������ ���� ������ �˷��ִ� Ŀ�ǵ� ���� ����.\n" );
		return;
	}
	pMonInfoCmd->AddParameter( new MCmdParamChar(nMonIndex) );

	if( !MMatchServer::GetInstance()->Post(pMonInfoCmd) )
		mlog( "MMatchRuleBaseQuest::CheckMonsterBible - ���� ������ ���� ������ �˷��ִ� Ŀ�ǵ� POST����.\n" );
}


//////////////////////////////////////////////////////////////////////////

void MMatchRuleBaseQuest::ReAssignNPC()
{
	auto nowTime = MMatchServer::GetInstance()->GetGlobalClockCount();

	if (nowTime - m_nLastNPCAssignCheckTime > NPC_ASSIGN_DELAY)
	{
		MMatchStage* pStage = GetStage();
		if (pStage == NULL) return;

		m_nLastNPCAssignCheckTime = nowTime;

		for (auto i=pStage->GetObjBegin(); i!=pStage->GetObjEnd(); i++)
		{
			MMatchObject* pObj = i->second;
			if (pObj->GetEnterBattle() == false) continue;	// ��Ʋ�����ϰ� �ִ� �÷��̾ üũ

			u32 lat = pObj->GetQuestLatency();

			if (lat > PING_LOST_LIMIT)
			{
				m_NPCManager.RemovePlayerControl(pObj->GetUID());
			}
			DMLog("Ping : %s (%d)\n", pObj->GetName(), lat);
		}
	}
}


void MMatchRuleBaseQuest::SendClientLatencyPing()
{
	auto nowTime = MMatchServer::GetInstance()->GetGlobalClockCount();

	if (nowTime - m_nLastPingTime > LATENCY_CHECK_DELAY)
	{
		MMatchStage* pStage = GetStage();

		m_nLastPingTime = nowTime;

		if (pStage == NULL) return;

		for (auto i=pStage->GetObjBegin(); i!=pStage->GetObjEnd(); i++)
		{
			MMatchObject* pObj = i->second;
			if (pObj->GetEnterBattle() == false) continue;

			if (pObj->m_bQuestRecvPong)
			{
				pObj->SetPingTime(nowTime);
				pObj->m_bQuestRecvPong = false;
			}
		}

		MMatchServer::GetInstance()->OnQuestSendPing(pStage->GetUID(), static_cast<u32>(nowTime));
	}
}