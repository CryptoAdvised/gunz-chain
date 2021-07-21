#include "stdafx.h"
#include "DBQuestCachingData.h"
#include "MMatchConfig.h"
#include "MAsyncDBJob.h"

void DBQuestCachingData::IncreasePlayCount(const int nCount)
{
	m_nPlayCount += nCount;
	DoUpdateDBCharQuestItemInfo();
}


void DBQuestCachingData::IncreaseShopTradeCount(const int nCount)
{
	m_nShopTradeCount += nCount;
	DoUpdateDBCharQuestItemInfo();
}


void DBQuestCachingData::IncreaseRewardCount(const int nCount)
{
	m_nRewardCount += nCount;
	DoUpdateDBCharQuestItemInfo();
}


bool DBQuestCachingData::CheckUniqueItem(MQuestItem* pQuestItem)
{
	if ((0 == pQuestItem) || (0 == pQuestItem->GetDesc()))
		return false;

	if (pQuestItem->GetDesc()->m_bUnique)
		m_bEnableUpdate = true;

	DoUpdateDBCharQuestItemInfo();

	return m_bEnableUpdate;
}


void DBQuestCachingData::Reset()
{
	m_dwLastUpdateTime = GetGlobalTimeMS();
	m_nPlayCount = 0;
	m_nShopTradeCount = 0;
	m_bEnableUpdate = false;
	m_nRewardCount = 0;
}


bool DBQuestCachingData::DoUpdateDBCharQuestItemInfo()
{
	// ����Ʈ �������� ���� �˻�.
	if (MSM_TEST != MGetServerConfig()->GetServerMode())
		return false;

	// �������� Object���� �˻�.
	if (!IsEnabledObject(m_pObject))
		return false;

	// ���� ���°� ������Ʈ �������� �˻�.
	if (!IsRequestUpdate())
	{
		// ���� ������Ʈ�� �˻縦 ���ؼ� ������ ������Ʈ �˻� �ð��� ������ ����.
		m_dwLastUpdateTime = GetGlobalTimeMS();
		return false;
	}

	MAsyncDBJob_UpdateQuestItemInfo* pAsyncJob = new MAsyncDBJob_UpdateQuestItemInfo;
	if (0 == pAsyncJob)
	{
		mlog("DBQuestCachingData::DoUpdateDBCharQuestItemInfo - QuestItemUpdate async�۾� ����.\n");
		return false;
	}
	if (!pAsyncJob->Input(m_pObject->GetCharInfo()->m_nCID,
		m_pObject->GetCharInfo()->m_QuestItemList,
		m_pObject->GetCharInfo()->m_QMonsterBible))
	{
		return false;
	}

	MMatchServer::GetInstance()->PostAsyncJob(pAsyncJob);

#ifdef _DEBUG
	{
		// ������Ʈ ������ ���������� �Ǵ��� �α׸� ����.
		char szDbgOut[1000] = { 0 };
		MQuestItemMap::iterator it, end;

		strcat_safe(szDbgOut, "Quest Item Caching UpdateDB\n");
		strcat_safe(szDbgOut, m_pObject->GetName());
		strcat_safe(szDbgOut, "\n");

		it = m_pObject->GetCharInfo()->m_QuestItemList.begin();
		end = m_pObject->GetCharInfo()->m_QuestItemList.end();

		for (; it != end; ++it)
		{
			char tmp[100] = { 0 };
			sprintf_safe(tmp, "%s : %d\n", it->second->GetDesc()->m_szQuestItemName, it->second->GetCount());
			strcat_safe(szDbgOut, tmp);
		}
		strcat_safe(szDbgOut, "\n");
		MMatchServer::GetInstance()->LOG(MMatchServer::LOG_ALL, szDbgOut);
	}
#endif

	// ������Ʈ�� �����ϸ� ���� �˻縦 ���ؼ� �ٽ� ������.
	Reset();

	return true;
}