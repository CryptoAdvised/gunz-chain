#ifndef _MQUEST_LEVEL_H
#define _MQUEST_LEVEL_H

#include "MBaseQuest.h"
#include "MQuestScenario.h"
#include "MQuestItem.h"
#include <vector>
#include <map>
#include <set>
using namespace std;

struct MTD_QuestGameInfo;
struct MQuestNPCSetInfo;




/// ����Ʈ ���巹������ ���� NPC��
class MQuestNPCQueue
{
private:
	vector<MQUEST_NPC>			m_Queue;			///< NPC�� vector���·� ����ִ�.
	int							m_nCursor;
public:
	MQuestNPCQueue();										///< ������
	~MQuestNPCQueue();										///< �Ҹ���

	/// QLD�� NPCSet�� �������� NPCť�� �����.
	/// @param nQLD				QLD
	/// @param pNPCSetInfo		NPC Set ����
	void Make(int nQLD, MQuestNPCSetInfo* pNPCSetInfo, MQUEST_NPC nKeyNPC=NPC_NONE);		
	void Clear();											///< ť �ʱ�ȭ
	bool Pop(MQUEST_NPC& outNPC);							///< ť���� NPC�� �ϳ� ������.
	bool GetFirst(MQUEST_NPC& outNPC);						///< ���� ó�� NPC���� �д´�.
	bool IsEmpty();											///< ť�� ������� üũ
	int GetCount();											///< ť�� ����ִ� NPC�� ��ȯ. Pop���� �̹� ���� NPC�� �����Ѵ�.
};




/// ������ �ʴ� ����Ʈ ���巹�� ����
struct MQuestLevelStaticInfo
{
	MQuestScenarioInfo*				pScenario;			///< �ش� ������ �ó�����
	int								nDice;				///< ���� �ֻ�����
	set<MQUEST_NPC>					NPCs;				///< ���� NPC ����
	vector<MQuestLevelSectorNode>	SectorList;			///< Map Sector ����Ʈ
	int								nQL;				///< ����Ʈ ����
	float							fNPC_TC;			///< NPC ���̵� ���� ���(NPC Toughness Coefficient)
	int								nQLD;				///< ����Ʈ ���� ���̵�
	int								nLMT;				///< �ѹ��� �����Ǵ� ���� ���� ����

	MQuestLevelStaticInfo()
	{
		pScenario=NULL;
		nDice = 0;
		nQL=0;
		fNPC_TC = 1.0f;
		nQLD = 0;
		nLMT = 1;
	}
};

/// ����Ʈ���� ���� ������
struct MQuestLevelItem
{
	u32	nItemID;			///< ����Ʈ ������ ID
	int					nRentPeriodHour;	///< �Ϲ� �������� ��� ��� �Ⱓ
	bool				bObtained;			///< �÷��̾ �Ծ����� ����
	int					nMonsetBibleIndex;	// ���� ������ ���� ���� Ÿ���� ���� �ε���.

	MQuestLevelItem() : nItemID(0), bObtained(false), nRentPeriodHour(0) {}
	bool IsQuestItem() { return IsQuestItemID(nItemID); }
};

/// ����Ʈ���� ���� �����۵�
class MQuestLevelItemMap : public multimap<u32, MQuestLevelItem*>
{
public:
	MQuestLevelItemMap() {}
	~MQuestLevelItemMap() { Clear(); }
	void Clear()
	{
		for (iterator itor = begin(); itor != end(); ++itor)
		{
			delete (*itor).second;
		}
		clear();
	}
};


/// ����Ʈ ���� �����ϸ鼭 ���ϴ� ����
struct MQuestLevelDynamicInfo
{
	int						nCurrSectorIndex;								///< ���� �������� ���� �ε���
	MQuestMapSectorInfo*	pCurrSector;									///< ���� �������� ����
	int						nQLD;											///< ����Ʈ ���� ���̵� ���(QLD)
	bool					bCurrBossSector;								///< ���� ���Ͱ� ���� �������� ����
	MQuestLevelItemMap		ItemMap;										///< ����Ʈ���� ���� �����۵�

	MQuestLevelDynamicInfo()
	{
		nCurrSectorIndex = 0;
		pCurrSector = NULL;
		nQLD = 0;
		bCurrBossSector = false;
	}
};


/// ����Ʈ ���� ���� - ����Ʈ�� ��� ������ ���� �� �ִ�.
class MQuestLevel
{
private:
	/// NPC ���� �ð��� �����ϱ� ���� ����ü
	struct MQuestLevelSpawnInfo
	{
		int					nIndex;								///< ���� �ε���
		u64	nRecentSpawnTime[MAX_SPAWN_COUNT];	///< �ֱٿ� ������ �ð�
	};

	MQuestLevelStaticInfo		m_StaticInfo;					///< ����Ʈ �����ϸ� ������ �ʴ� ����
	MQuestLevelDynamicInfo		m_DynamicInfo;					///< ����Ʈ �����ϸ鼭 ���ϴ� ����
	MQuestNPCQueue				m_NPCQueue;						///< ������ NPC ������Ʈ ť

	MQuestLevelSpawnInfo		m_SpawnInfos[MNST_END];			///< NPC �������� ����

	bool InitSectors();
	bool InitNPCs();											
	void InitStaticInfo();
	void InitCurrSector();

public:
	MQuestLevel();						///< ������
	~MQuestLevel();						///< �Ҹ���

	/// �ó����� ID�� ������� ���巹�� �ʱ�ȭ
	/// @param nScenarioID			�ó����� ID
	/// @param nDice				�ֻ��� ����
	void Init(int nScenarioID, int nDice);
	/// ������ ���巹���� �������� Ŭ���̾�Ʈ�� ������ ���۵���Ÿ�� �����.
	void Make_MTDQuestGameInfo(MTD_QuestGameInfo* pout);
	/// �ʼ��� �� ��ȯ
	/// @return		���� ��
	int GetMapSectorCount();
	/// ���� ���� �ε��� ��ȯ
	/// @return		���� ���� �ε���
	int GetCurrSectorIndex();
	/// ���� ���ͷ� �̵��Ѵ�.
	/// @return		����/���� ����
	bool MoveToNextSector();	
	/// ���� �¾ NPC�� ��ġ�� ��õ�Ѵ�.
	/// @param nSpawnType		NPC�� ����Ÿ��
	/// @param nNowTime			���� �ð�
	int GetRecommendedSpawnPosition(MQuestNPCSpawnType nSpawnType, u64 nNowTime);
	/// ���� NPC�� ������������ Ȯ���Ѵ�.
	/// @param nSpawnType		NPC�� ����Ÿ��
	/// @param nNowTime			���� �ð�
	bool IsEnableSpawnNow(MQuestNPCSpawnType nSpawnType, u64 nNowTime);
	/// ���� ���Ϳ��� ���� ���� ������ ���Ѵ�.
	/// @param nSpawnType		NPC�� ����Ÿ��
	int GetSpawnPositionCount(MQuestNPCSpawnType nSpawnType);

	/// ����Ʈ �������� ������ ��� ȣ��ȴ�.
	/// @nItemID				����Ʈ ������ ID
	/// @nRentPeriodHour		�Ϲ� �������� ��� ��� �Ⱓ
	void OnItemCreated(u32	nItemID, int nRentPeriodHour);
	/// �÷��̾ ����Ʈ ������ �Ծ��� ��� ȣ��ȴ�.
	/// @nItemID				����Ʈ ������ ID
	bool OnItemObtained( MMatchObject* pPlayer, u32	nItemID);		

	MQuestNPCQueue* GetNPCQueue()				{ return &m_NPCQueue; }
	MQuestLevelStaticInfo* GetStaticInfo()		{ return &m_StaticInfo; }
	MQuestLevelDynamicInfo* GetDynamicInfo()	{ return &m_DynamicInfo; }
};






#endif