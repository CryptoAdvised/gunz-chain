#include "stdafx.h"
#include "MMatchServer.h"
#include "MMatchStage.h"
#include "MMatchRule.h"
#include "MMatchRuleQuest.h"
#include "MMatchGameType.h"
#include "MMatchConfig.h"
#include "MBlobArray.h"
#include "MMatchShop.h"
#include "MSharedCommandTable.h"
#include "MErrorTable.h"

void MMatchServer::OnRequestNPCDead(const MUID& uidSender, const MUID& uidKiller, MUID& uidNPC, MVector& pos)
{
#ifdef _QUEST
	MMatchObject* pSender = GetObject(uidSender);
	if (!IsEnabledObject(pSender)) return;

	// killer �� npc �� ���� �ִ�.
//	MMatchObject* pKiller = GetObject(uidKiller);
//	if (!IsEnabledObject(pKiller)) return;

	MMatchStage* pStage = FindStage(pSender->GetStageUID());
	if (pStage == NULL) 
	{
		ASSERT( 0 );
		return;
	}

	if (MGetGameTypeMgr()->IsQuestDerived(pStage->GetStageSetting()->GetGameType()))
	{
		MMatchRuleBaseQuest* pQuestRule = (MMatchRuleBaseQuest*)pStage->GetRule();
		pQuestRule->OnRequestNPCDead((MUID&)uidSender, (MUID&)uidKiller, uidNPC, pos);
	}
	else
	{
		ASSERT( 0 );
	}
#endif
}


void MMatchServer::OnQuestRequestDead(const MUID& uidVictim)
{
#ifdef _QUEST
	MMatchObject* pVictim = GetObject(uidVictim);
	if (pVictim == NULL) return;

	MMatchStage* pStage = FindStage(pVictim->GetStageUID());
	if (pStage == NULL) return;

	if ( !MGetGameTypeMgr()->IsQuestDerived(pStage->GetStageSetting()->GetGameType())) return;

	MMatchRuleBaseQuest* pQuestRule = (MMatchRuleBaseQuest*)pStage->GetRule();
	pQuestRule->OnRequestPlayerDead((MUID&)uidVictim);

	// ������ ������ �˰��־��µ� �� �׾��ٰ� �Ű���°�� �׾��ٴ� �޽����� ������Ѵ�
	if (pVictim->CheckAlive() == false) {	
		MCommand* pNew = CreateCommand(MC_MATCH_RESPONSE_SUICIDE, MUID(0,0));
		int nResult = MOK;
		pNew->AddParameter(new MCommandParameterInt(nResult));
		pNew->AddParameter(new MCommandParameterUID(pVictim->GetUID()));
		RouteToBattle(pStage->GetUID(), pNew);
		return;
	}

	pVictim->OnDead();


	// �׾��ٴ� �޼��� ����
	MCommand* pCmd = CreateCommand(MC_MATCH_QUEST_PLAYER_DEAD, MUID(0,0));
	pCmd->AddParameter(new MCommandParameterUID(uidVictim));
	RouteToBattle(pStage->GetUID(), pCmd);	

#endif
}



void MMatchServer::OnQuestTestRequestNPCSpawn(const MUID& uidPlayer, int nNPCType, int nNPCCount)
{
#ifndef _DEBUG
	return;
#endif

	if (MGetServerConfig()->GetServerMode() != MSM_TEST) return;

	MMatchObject* pPlayer = GetObject(uidPlayer);
	if (pPlayer == NULL) return;
	MMatchStage* pStage = FindStage(pPlayer->GetStageUID());
	if (pStage == NULL) return;

#ifndef _DEBUG
	if (!IsAdminGrade(pPlayer)) return;
#endif

	if (MGetGameTypeMgr()->IsQuestDerived(pStage->GetStageSetting()->GetGameType()))
	{
		MMatchRuleBaseQuest* pQuestRule = (MMatchRuleBaseQuest*)pStage->GetRule();
		pQuestRule->OnRequestTestNPCSpawn(nNPCType, nNPCCount);
	}

}

void MMatchServer::OnQuestTestRequestClearNPC(const MUID& uidPlayer)
{
#ifndef _DEBUG
	return;
#endif

	if (MGetServerConfig()->GetServerMode() != MSM_TEST) return;

	MMatchObject* pPlayer = GetObject(uidPlayer);
	if (pPlayer == NULL) return;
	MMatchStage* pStage = FindStage(pPlayer->GetStageUID());
	if (pStage == NULL) return;

#ifndef _DEBUG
	if (!IsAdminGrade(pPlayer)) return;
#endif

	if (MGetGameTypeMgr()->IsQuestDerived(pStage->GetStageSetting()->GetGameType()))
	{
		MMatchRuleBaseQuest* pQuestRule = (MMatchRuleBaseQuest*)pStage->GetRule();
		pQuestRule->OnRequestTestClearNPC();
	}

}


void MMatchServer::OnQuestTestRequestSectorClear(const MUID& uidPlayer)
{
#ifndef _DEBUG
	return;
#endif

	if (MGetServerConfig()->GetServerMode() != MSM_TEST) return;

	MMatchObject* pPlayer = GetObject(uidPlayer);
	if (pPlayer == NULL) return;
	MMatchStage* pStage = FindStage(pPlayer->GetStageUID());
	if (pStage == NULL) return;

#ifndef _DEBUG
	if (!IsAdminGrade(pPlayer)) return;
#endif

	if (pStage->GetStageSetting()->GetGameType() == MMATCH_GAMETYPE_QUEST)
	{
		MMatchRuleQuest* pQuestRule = (MMatchRuleQuest*)pStage->GetRule();
		pQuestRule->OnRequestTestSectorClear();
	}

}

void MMatchServer::OnQuestTestRequestQuestFinish(const MUID& uidPlayer)
{
#ifndef _DEBUG
	return;
#endif

	if (MGetServerConfig()->GetServerMode() != MSM_TEST) return;

	MMatchObject* pPlayer = GetObject(uidPlayer);
	if (pPlayer == NULL) return;
	MMatchStage* pStage = FindStage(pPlayer->GetStageUID());
	if (pStage == NULL) return;

#ifndef _DEBUG
	if (!IsAdminGrade(pPlayer)) return;
#endif

	if (pStage->GetStageSetting()->GetGameType() == MMATCH_GAMETYPE_QUEST)
	{
		MMatchRuleQuest* pQuestRule = (MMatchRuleQuest*)pStage->GetRule();
		pQuestRule->OnRequestTestFinish();
	}

}



void MMatchServer::OnQuestRequestMovetoPortal(const MUID& uidPlayer)
{
	MMatchObject* pPlayer = GetObject(uidPlayer);
	if (pPlayer == NULL) return;
	MMatchStage* pStage = FindStage(pPlayer->GetStageUID());
	if (pStage == NULL) return;

	if (pStage->GetStageSetting()->GetGameType() != MMATCH_GAMETYPE_QUEST) return;

	MMatchRuleQuest* pQuestRule = (MMatchRuleQuest*)pStage->GetRule();
	pQuestRule->OnRequestMovetoPortal(uidPlayer);
}

void MMatchServer::OnQuestReadyToNewSector(const MUID& uidPlayer)
{
	MMatchObject* pPlayer = GetObject(uidPlayer);
	if (pPlayer == NULL) return;
	MMatchStage* pStage = FindStage(pPlayer->GetStageUID());
	if (pStage == NULL) return;

	if (pStage->GetStageSetting()->GetGameType() != MMATCH_GAMETYPE_QUEST) return;

	MMatchRuleQuest* pQuestRule = (MMatchRuleQuest*)pStage->GetRule();
	pQuestRule->OnReadyToNewSector(uidPlayer);

}


void MMatchServer::OnRequestCharQuestItemList( const MUID& uidSender )
{
#ifdef _QUEST_ITEM
	if( MSM_TEST != MGetServerConfig()->GetServerMode() ) 
		return;

	OnResponseCharQuestItemList( uidSender );
#endif
}
void MMatchServer::OnResponseCharQuestItemList( const MUID& uidSender )
{
	MMatchObject* pPlayer = GetObject( uidSender );
	if( !IsEnabledObject(pPlayer) )
		return;

	// ������ ��� �＼���� ���߾����� ��񿡼� ����Ʈ ������ ������ �����´�
	if( !pPlayer->GetCharInfo()->m_QuestItemList.IsDoneDbAccess() )
	{
		if( !GetDBMgr()->GetCharQuestItemInfo(pPlayer->GetCharInfo()) )
		{
			mlog( "DB Query(ResponseCharacterItemList > GetcharQuestItemInfo) failed\n" );
			return;
		}
	}

	MCommand* pNewCmd = CreateCommand( MC_MATCH_RESPONSE_CHAR_QUEST_ITEM_LIST, MUID(0, 0) );
	if( 0 == pNewCmd )
	{
		mlog( "MMatchServer::OnResponseCharQuestItemList - Command���� ����.\n" );
		return;
	}

	// ���� �ִ� ����Ʈ ������ ����Ʈ ����.
	int					nIndex			= 0;
	MTD_QuestItemNode*	pQuestItemNode	= 0;
	void*				pQuestItemArray = MMakeBlobArray( static_cast<int>(sizeof(MTD_QuestItemNode)), 
														  static_cast<int>(pPlayer->GetCharInfo()->m_QuestItemList.size()) );

	MQuestItemMap::iterator itQItem, endQItem;
	endQItem = pPlayer->GetCharInfo()->m_QuestItemList.end();
	for( itQItem = pPlayer->GetCharInfo()->m_QuestItemList.begin(); itQItem != endQItem; ++itQItem )
	{
		pQuestItemNode = reinterpret_cast< MTD_QuestItemNode* >( MGetBlobArrayElement(pQuestItemArray, nIndex++) );
		Make_MTDQuestItemNode( pQuestItemNode, itQItem->second->GetItemID(), itQItem->second->GetCount() );
	}

	pNewCmd->AddParameter( new MCommandParameterBlob(pQuestItemArray, MGetBlobArraySize(pQuestItemArray)) );
	MEraseBlobArray( pQuestItemArray );

	RouteToListener( pPlayer, pNewCmd );
}


void MMatchServer::OnRequestBuyQuestItem( const MUID& uidSender, const u32 nItemID )
{
#ifdef _QUEST_ITEM
	if (MGetServerConfig()->GetServerMode() == MSM_TEST)
	{
		OnResponseBuyQeustItem( uidSender, nItemID );
	}
#endif
}
void MMatchServer::OnResponseBuyQeustItem( const MUID& uidSender, const u32 nItemID )
{
	MMatchObject* pPlayer = GetObject( uidSender );
	if( !IsEnabledObject(pPlayer) )
		return;

	MQuestItemDescManager::iterator itQItemDesc = GetQuestItemDescMgr().find( nItemID );
	if( GetQuestItemDescMgr().end() == itQItemDesc )
	{
		mlog( "MMatchServer::OnResponseBuyQuestItem - %d������ description�� ã�� ���߽��ϴ�.\n", nItemID );
		return;
	}

	MQuestItemDesc* pQuestItemDesc = itQItemDesc->second;
	if( 0 == pQuestItemDesc )
	{
		mlog( "MMatchServer::OnRequestBuyQuestItem - %d�� item description�� ���������Դϴ�.\n", nItemID );
		return;
	}

	// �������� �Ǹŵǰ� �ִ� ���������� �˻�.
	if( !MGetMatchShop()->IsSellItem(pQuestItemDesc->m_nItemID) )
	{
		mlog( "MMatchServer::OnRequestBuyQuestItem - %d�� �������� �Ǹŵǰ� �ִ� �������� �ƴ�.\n", pQuestItemDesc->m_nItemID );
		return;
	}

	// ����� �ٿ�Ƽ�� �Ǵ��� �˻�.
	if( pPlayer->GetCharInfo()->m_nBP < itQItemDesc->second->m_nPrice )
	{
		// �ٿ�Ƽ�� �����Ѵٴ� ������ �˷���� ��.
		// �ӽ÷� MMatchItem���� ����ϴ°� �������.
		// �ʿ��ϸ� Quest item�� �´� Ŀ�ǵ�� �����ؾ� ��.
		MCommand* pBPLess = CreateCommand( MC_MATCH_RESPONSE_BUY_QUEST_ITEM, MUID(0,0) );
		pBPLess->AddParameter( new MCmdParamInt(MERR_TOO_EXPENSIVE_BOUNTY) );
		pBPLess->AddParameter( new MCmdParamInt(pPlayer->GetCharInfo()->m_nBP) );
		RouteToListener(pPlayer, pBPLess);
		return;
	}

	MQuestItemMap::iterator itQItem = pPlayer->GetCharInfo()->m_QuestItemList.find( nItemID );
	if( pPlayer->GetCharInfo()->m_QuestItemList.end() != itQItem )
	{
#ifdef _DEBUG
		int n = itQItem->second->GetCount();
#endif
		// �ִ� ������ �Ѵ��� �˻�.
		if( MAX_QUEST_ITEM_COUNT >= itQItem->second->GetCount() )
		{
			// ���� ����
			itQItem->second->Increase();
		}
		else
		{
			// ������ �ִ� �������� �ִ� ���� �Ѿ��.
			// �ӽ÷� MMatchItem���� ����ϴ°� �������.
			// �ʿ��ϸ� Quest item�� �´� Ŀ�ǵ�� �����ؾ� ��.
			MCommand* pTooMany = CreateCommand( MC_MATCH_RESPONSE_BUY_QUEST_ITEM, MUID(0,0) );
			pTooMany->AddParameter( new MCmdParamInt(MERR_TOO_MANY_ITEM) );
			pTooMany->AddParameter( new MCmdParamInt(pPlayer->GetCharInfo()->m_nBP) );
			RouteToListener(pPlayer, pTooMany);
			return;
		}
	}
	else
	{
		MQuestItem* pNewQuestItem = new MQuestItem();
		if( 0 == pNewQuestItem )
		{
			mlog( "MMatchServer::OnResponseBuyQuestItem - ���ο� ����Ʈ ������ ���� ����.\n" );
			return;
		}

		if( !pNewQuestItem->Create(nItemID, 1, GetQuestItemDescMgr().FindQItemDesc(nItemID)) )
		{
			delete pNewQuestItem;
			mlog( "MMatchServer::OnResponseBuyQeustItem - %d��ȣ ������ Create( ... )�Լ� ȣ�� ����.\n" );
			return;
		}

		pPlayer->GetCharInfo()->m_QuestItemList.insert( MQuestItemMap::value_type(nItemID, pNewQuestItem) );
	}

	// ĳ���� ���� ĳ�� ������Ʈ�� ���� ���ش�.
	UpdateCharDBCachingData( pPlayer );	

	// ��� �ٿ�Ƽ �����ش�
	int nPrice = pQuestItemDesc->m_nPrice;

	if (!GetDBMgr()->UpdateCharBP(pPlayer->GetCharInfo()->m_nCID, -nPrice))
	{
		/*
		MCommand* pNew = CreateCommand(MC_MATCH_RESPONSE_SELL_ITEM, MUID(0,0));
		pNew->AddParameter(new MCmdParamInt(MERR_CANNOT_SELL_ITEM));
		RouteToListener(pObj, pNew);

		return false;
		*/
		return;
	}

	pPlayer->GetCharInfo()->m_nBP -= nPrice;

	// ������ �ŷ� ī��Ʈ ����. ���ο��� ��� ������Ʈ ����.
	pPlayer->GetCharInfo()->GetDBQuestCachingData().IncreaseShopTradeCount();

	MCommand* pNewCmd = CreateCommand( MC_MATCH_RESPONSE_BUY_QUEST_ITEM, MUID(0, 0) );
	if( 0 == pNewCmd )
	{
		mlog( "MMatchServer::OnResponseBuyQuestItem - new Command����.\n" );
		return;
	}
	pNewCmd->AddParameter( new MCmdParamInt(MOK) );
	pNewCmd->AddParameter( new MCmdParamInt(pPlayer->GetCharInfo()->m_nBP) );
	RouteToListener( pPlayer, pNewCmd );

	// ����Ʈ ������ ����Ʈ�� �ٽ� ������.
	OnRequestCharQuestItemList( pPlayer->GetUID() );
}


void MMatchServer::OnRequestSellQuestItem( const MUID& uidSender, const u32 nItemID, const int nCount )
{
#ifdef _QUEST_ITEM
	if (MGetServerConfig()->GetServerMode() == MSM_TEST)
	{
		OnResponseSellQuestItem( uidSender, nItemID, nCount );
	}
#endif
}


void MMatchServer::OnResponseSellQuestItem( const MUID& uidSender, const u32 nItemID, const int nCount )
{
	MMatchObject* pPlayer = GetObject( uidSender );
	if( !IsEnabledObject(pPlayer) )
	{
		mlog( "MMatchServer::OnResponseSellQuestItem - ������ ã�µ� �����߽��ϴ�. UserName:%s\n", pPlayer->GetCharInfo()->m_szName );
		return;
	}

	MQuestItemDescManager::iterator itQItemDesc = GetQuestItemDescMgr().find( nItemID );
	if( GetQuestItemDescMgr().end() == itQItemDesc )
	{
		mlog( "MMatchServer::OnResponseSellQuestItem - %d�� ������ description�� ã�� ���߽��ϴ�. UserName:%s\n", nItemID, pPlayer->GetCharInfo()->m_szName );
		return;
	}
	
	MQuestItemDesc* pQItemDesc = itQItemDesc->second;
	if( 0 == pQItemDesc )
	{
		mlog( "MMatchServer::OnResponseSellQuestItem - %d �������� decription�� �������Դϴ�. CharName:%s\n", nItemID, pPlayer->GetCharInfo()->m_szName );
		return;
	}

	// ������ ī��Ʈ �˻�.
	MQuestItemMap::iterator itQItem = pPlayer->GetCharInfo()->m_QuestItemList.find( nItemID );
	if( pPlayer->GetCharInfo()->m_QuestItemList.end() != itQItem )
	{
		if( nCount > itQItem->second->GetCount() )
		{
			// �ѹ� ȹ���� �ߴ� ������������, ���� ������ �ȷ��� �ϴ� �������� ������.
			return;
		}

		// ĳ���� ���� ĳ�� ������Ʈ�� ���� ���ش�.
		UpdateCharDBCachingData( pPlayer );	

		// ��� �ٿ�Ƽ �����ش�
		int nPrice = ( nCount * pQItemDesc->GetBountyValue() );
		if (!GetDBMgr()->UpdateCharBP(pPlayer->GetCharInfo()->m_nCID, nPrice))
		{
			/*
			MCommand* pNew = CreateCommand(MC_MATCH_RESPONSE_SELL_ITEM, MUID(0,0));
			pNew->AddParameter(new MCmdParamInt(MERR_CANNOT_SELL_ITEM));
			RouteToListener(pObj, pNew);

			return false;
			*/
			return;
		}

		itQItem->second->Decrease( nCount );

		pPlayer->GetCharInfo()->m_nBP += nPrice;		// ���Ƚô� 1/4�� ������ ����.

	}
	else
	{
		// �������� �ʴ� �������� �ȷ��� �Ͽ���.
		mlog( "MMatchServer::OnResponseSellQuestItem - %d�� ������ ���� ���� �������� �Ǹ��Ϸ���. CharName:%s\n", nItemID, pPlayer->GetCharInfo()->m_szName );
		ASSERT( 0 );
		return;
	}

	// ������ �ŷ� ī��Ʈ ����. ���ο��� ��� ������Ʈ ����.
	pPlayer->GetCharInfo()->GetDBQuestCachingData().IncreaseShopTradeCount();

	MCommand* pCmd = CreateCommand( MC_MATCH_RESPONSE_SELL_QUEST_ITEM, MUID(0, 0) );
	if( 0 == pCmd )
	{
		return;
	}

	pCmd->AddParameter( new MCmdParamInt(MOK) );
	pCmd->AddParameter( new MCmdParamInt(pPlayer->GetCharInfo()->m_nBP) );
	RouteToListener( pPlayer, pCmd );

	// ����Ʈ ������ ����Ʈ�� �ٽ� ������.
	OnRequestCharQuestItemList( pPlayer->GetUID() );
}


void MMatchServer::OnRequestDropSacrificeItemOnSlot( const MUID& uidSender, const int nSlotIndex, const u32 nItemID )
{
#ifdef _QUEST_ITEM
	if (MGetServerConfig()->GetServerMode() == MSM_TEST)
	{
		MMatchObject* pPlayer = GetObject( uidSender );
		if( !IsEnabledObject(pPlayer) )
		{
			mlog( "MMatchServer::OnRequestDropSacrificeItemOnSlot - ���������� ����.\n" );
			return;
		}

		MMatchStage* pStage = FindStage( pPlayer->GetStageUID() );
		if( 0 != pStage )
		{
			MSTAGE_SETTING_NODE* pNode = pStage->GetStageSetting()->GetStageSetting();
			if( 0 == pNode )
			{
				mlog( "MMatchServer::CharFinalize - �������� ���� ��� ã�� ����.\n" );
				return;
			}

			if( MGetGameTypeMgr()->IsQuestDerived(pNode->nGameType) )
			{
				MMatchRuleBaseQuest* pRuleQuest = reinterpret_cast< MMatchRuleBaseQuest* >( pStage->GetRule() );
				if( 0 == pRuleQuest )
					return;

				pRuleQuest->OnRequestDropSacrificeItemOnSlot( uidSender, nSlotIndex, nItemID );
			}
		}
	}	
#endif
}


void MMatchServer::OnRequestCallbackSacrificeItem( const MUID& uidSender, const int nSlotIndex, const u32 nItemID )
{
#ifdef _QUEST_ITEM
	if (MGetServerConfig()->GetServerMode() == MSM_TEST)
	{
		MMatchObject* pPlayer = GetObject( uidSender );
		if( !IsEnabledObject(pPlayer) )
		{
			mlog( "MMatchServer::OnRequestDropSacrificeItemOnSlot - ���������� ����.\n" );
			return;
		}

		MMatchStage* pStage = FindStage( pPlayer->GetStageUID() );
		if( 0 != pStage )
		{
			MSTAGE_SETTING_NODE* pNode = pStage->GetStageSetting()->GetStageSetting();
			if( 0 == pNode )
			{
				mlog( "MMatchServer::CharFinalize - �������� ���� ��� ã�� ����.\n" );
				return;
			}

			if( MGetGameTypeMgr()->IsQuestDerived(pNode->nGameType) )
			{
				MMatchRuleBaseQuest* pRuleQuest = reinterpret_cast< MMatchRuleBaseQuest* >( pStage->GetRule() );
				if( 0 == pRuleQuest )
					return;

				pRuleQuest->OnRequestCallbackSacrificeItem( uidSender, nSlotIndex, nItemID );
			}
		}
	}
#endif
}

void MMatchServer::OnRequestQL( const MUID& uidSender )
{
#ifdef _QUEST_ITEM
	if (MGetServerConfig()->GetServerMode() == MSM_TEST)
	{
		MMatchObject* pPlayer = GetObject( uidSender );
		if( !IsEnabledObject(pPlayer) )
		{
			mlog( "MMatchServer::OnRequestDropSacrificeItemOnSlot - ���������� ����.\n" );
			return;
		}

		MMatchStage* pStage = FindStage( pPlayer->GetStageUID() );
		if( 0 != pStage )
		{
			MSTAGE_SETTING_NODE* pNode = pStage->GetStageSetting()->GetStageSetting();
			if( 0 == pNode )
			{
				mlog( "MMatchServer::CharFinalize - �������� ���� ��� ã�� ����.\n" );
				return;
			}

			if( MGetGameTypeMgr()->IsQuestDerived(pNode->nGameType) )
			{
				MMatchRuleBaseQuest* pRuleQuest = reinterpret_cast< MMatchRuleBaseQuest* >( pStage->GetRule() );
				if( 0 == pRuleQuest )
					return;

				pRuleQuest->OnRequestQL( uidSender );
			}
		}
	}	
#endif
}


void MMatchServer::OnRequestSacrificeSlotInfo( const MUID& uidSender )
{
#ifdef _QUEST_ITEM
	if (MGetServerConfig()->GetServerMode() == MSM_TEST)
	{
		MMatchObject* pPlayer = GetObject( uidSender );
		if( !IsEnabledObject(pPlayer) )
		{
			mlog( "MMatchServer::OnRequestDropSacrificeItemOnSlot - ���������� ����.\n" );
			return;
		}

		MMatchStage* pStage = FindStage( pPlayer->GetStageUID() );
		if( 0 != pStage )
		{
			MSTAGE_SETTING_NODE* pNode = pStage->GetStageSetting()->GetStageSetting();
			if( 0 == pNode )
			{
				mlog( "MMatchServer::CharFinalize - �������� ���� ��� ã�� ����.\n" );
				return;
			}

			if( MGetGameTypeMgr()->IsQuestDerived(pNode->nGameType) )
			{
				MMatchRuleBaseQuest* pRuleQuest = reinterpret_cast< MMatchRuleBaseQuest* >( pStage->GetRule() );
				if( 0 == pRuleQuest )
					return;

				pRuleQuest->OnRequestSacrificeSlotInfo( uidSender );
			}
		}
	}
#endif
}

void MMatchServer::OnQuestStageMapset(const MUID& uidStage, int nMapsetID)
{
	if (QuestTestServer())
	{



	}
}


void MMatchServer::OnRequestMonsterBibleInfo( const MUID& uidSender )
{
	if (MGetServerConfig()->GetServerMode() == MSM_TEST)
	{
		MMatchObject* pPlayer = GetObject( uidSender );
		if( !IsEnabledObject(pPlayer) )
		{
			mlog( "MMatchServer::OnRequestMonsterBibleInfo - ���������� ����.\n" );
			return;
		}

		OnResponseMonsterBibleInfo( uidSender );
	}
}


void MMatchServer::OnResponseMonsterBibleInfo( const MUID& uidSender )
{
	MMatchObject* pObj = GetObject( uidSender );
	if( !IsEnabledObject(pObj) )
		return;

	MMatchCharInfo* pCharInfo = pObj->GetCharInfo();
	if( 0 == pCharInfo )
		return;

	// ��񿡼� �ɸ��� ����Ʈ ���������� �������ִ��� �˻縦 ��.
	if( !pCharInfo->m_QuestItemList.IsDoneDbAccess() )
	{
		mlog( "MMatchServer::OnResponseMonsterBibleInfo - ���ε� ������ �߻���.\n" );
		return;
	}	

	void* pMonBibleInfoBlob = MMakeBlobArray( MONSTER_BIBLE_SIZE, 1 );
	if( 0 == pMonBibleInfoBlob )
	{
		mlog( "MMatchServer::OnResponseMonsterBibleInfo - Blob���� ����.\n" );
		return;
	}

	MQuestMonsterBible* pMonBible = reinterpret_cast< MQuestMonsterBible * >( MGetBlobArrayElement(pMonBibleInfoBlob, 0) );
	if( 0 == pMonBible )
	{
		mlog( "MMatchServer::OnResponseMonsterBibleInfo - ����ȯ ����.\n" );
		return;
	}

	memcpy( pMonBible, &(pCharInfo->m_QMonsterBible), MONSTER_BIBLE_SIZE );


	MCommand* pCmd = CreateCommand( MC_MATCH_RESPONSE_MONSTER_BIBLE_INFO, MUID(0, 0) );
	if( 0 == pCmd )
	{
		mlog( "MMatchServer::OnResponseMonsterBibleInfo - Ŀ�ǵ� ���� ����.\n" );
		return;
	}

	pCmd->AddParameter( new MCmdParamUID(uidSender) );
	pCmd->AddParameter( new MCommandParameterBlob(pMonBibleInfoBlob, MGetBlobArraySize(pMonBibleInfoBlob)) );

	RouteToListener( pObj, pCmd );

	MEraseBlobArray( pMonBibleInfoBlob );
}


void MMatchServer::OnQuestPong( const MUID& uidSender )
{
	MMatchObject* pObj = GetObject( uidSender );
	pObj->SetQuestLatency(GetGlobalClockCount());
	pObj->m_bQuestRecvPong = true;
}

