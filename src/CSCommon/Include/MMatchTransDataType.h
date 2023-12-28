#ifndef _MMATCHTRANSDATATYPE_H
#define _MMATCHTRANSDATATYPE_H

#include "MMatchGlobal.h"
#include "MMatchItem.h"
#include "MMatchStageSetting.h"
#include "MMatchGameType.h"

#pragma pack(push, old)
#pragma pack(1)

struct MTD_AccountCharInfo
{
	char				szName[MATCHOBJECT_NAME_LENGTH];
	char				nCharNum;
	unsigned char		nLevel;
};


struct MTD_CharInfo
{
	char				szName[32];
	char				szClanName[CLAN_NAME_LENGTH];
	MMatchClanGrade		nClanGrade;
	unsigned short		nClanContPoint;
	char				nCharNum;
	unsigned short		nLevel;
	char				nSex;
	char				nHair;
	char				nFace;
	u32	nXP;
	int					nBP;
	float				fBonusRate;
	unsigned short		nPrize;
	unsigned short		nHP;
	unsigned short		nAP;
	unsigned short		nMaxWeight;
	unsigned short		nSafeFalls;
	unsigned short		nFR;
	unsigned short		nCR;
	unsigned short		nER;
	unsigned short		nWR;

	u32					nEquipedItemDesc[MMCIP_END];

	MMatchUserGradeID	nUGradeID;

	unsigned int		nClanCLID;
};

struct MTD_MyExtraCharInfo
{
	char	nLevelPercent;
};

struct MTD_SimpleCharInfo
{
	char				szName[32];
	char				nLevel;
	char				nSex;
	char				nHair;
	char				nFace;
	u32	nEquipedItemDesc[MMCIP_END];
};


struct MTD_MySimpleCharInfo
{
	unsigned char		nLevel;
	u32	nXP;
	int					nBP;
};

struct MTD_CharLevelInfo
{
	unsigned char		nLevel;
	u32	nCurrLevelExp;
	u32	nNextLevelExp;
};

struct MTD_RoundPeerInfo
{
	MUID			uidChar;
	unsigned char	nHP;
	unsigned char	nAP;
};

struct MTD_RoundKillInfo
{
	MUID	uidAttacker;
	MUID	uidVictim;
};

struct MTD_ItemNode
{
	MUID				uidItem;
	u32	nItemID;
	int					nRentMinutePeriodRemainder;		// �Ⱓ�� ������ ��밡�ɽð�(�ʴ���), RENT_MINUTE_PERIOD_UNLIMITED�̸� ������
};

struct MTD_AccountItemNode
{
	int					nAIID;
	u32	nItemID;
	int					nRentMinutePeriodRemainder;		// �Ⱓ�� ������ ��밡�ɽð�(�ʴ���), RENT_MINUTE_PERIOD_UNLIMITED�̸� ������
};

// ���Ӿ� ���� ����
struct MTD_GameInfoPlayerItem
{
	MUID	uidPlayer;
	bool	bAlive;
	int		nKillCount;
	int		nDeathCount;
};

struct MTD_GameInfo
{
	char	nRedTeamScore;		// ���������� ����ϴ� ����������
	char	nBlueTeamScore;		// ���������� ����ϴ� ����������

	short	nRedTeamKills;		// ������������ġ������ ����ϴ� ������ų��
	short	nBlueTeamKills;		// ������������ġ������ ����ϴ� ������ų��
};

struct MTD_RuleInfo	
{
	unsigned char	nRuleType;
};

struct MTD_RuleInfo_Assassinate : public MTD_RuleInfo
{
	MUID	uidRedCommander;
	MUID	uidBlueCommander;
};

struct MTD_RuleInfo_Berserker : public MTD_RuleInfo
{
	MUID	uidBerserker;
};


enum MTD_PlayerFlags {
	MTD_PlayerFlags_AdminHide	= 1,
	MTD_PlayerFlags_BridgePeer	= 1<<1,
	MTD_PlayerFlags_Premium		= 1<<2,
	MTD_PlayerFlags_Bot			= 1<<3,
};

struct MTD_ChannelPlayerListNode 
{
	MUID			uidPlayer;
	char			szName[MATCHOBJECT_NAME_LENGTH];
	char			szClanName[CLAN_NAME_LENGTH];
	char			nLevel;
	MMatchPlace		nPlace;
	unsigned char	nGrade;			// �κ񿡼��� uid �� ĳ������ ����� �˼��� ���..
	unsigned char	nPlayerFlags;	// �÷��̾� �Ӽ�(��ڼ����) - MTD_PlayerFlags ���
	unsigned int	nCLID;			// ClanID
	unsigned int	nEmblemChecksum;// Emblem Checksum
};


struct MTD_ClanMemberListNode 
{
	MUID				uidPlayer;
	char				szName[MATCHOBJECT_NAME_LENGTH];
	char				nLevel;
	MMatchClanGrade		nClanGrade;
	MMatchPlace			nPlace;
};

enum MTD_WorldItemSubType
{
	MTD_Dynamic = 0,
	MTD_Static  = 1,
};

// ������ ���� ����
struct MTD_WorldItem
{
	unsigned short	nUID;
	unsigned short	nItemID;
	unsigned short  nItemSubType;
	short			x;
	short			y;
	short			z;
/*
	float			x;
	float			y;
	float			z;
*/
};


// �ٷΰ����ϱ� ���͸� ����
struct MTD_QuickJoinParam
{
	u32	nMapEnum;		// ���ϴ� ���� ��Ʈ���
	u32	nModeEnum;		// ���ϴ� ���Ӹ���� ��Ʈ���
};


// ĳ������ Ŭ�� ������Ʈ ����
struct MTD_CharClanInfo
{
	char				szClanName[CLAN_NAME_LENGTH];		// Ŭ�� �̸�
	MMatchClanGrade		nGrade;
};


// ���� ��������
struct MTD_CharInfo_Detail
{
	char				szName[32];						// �̸�
	char				szClanName[CLAN_NAME_LENGTH];	// Ŭ���̸�
	MMatchClanGrade		nClanGrade;						// Ŭ����å
	int					nClanContPoint;					// Ŭ�� �⿩��
	unsigned short		nLevel;							// ����
	char				nSex;							// ����
	char				nHair;							// �Ӹ� �ڽ���
	char				nFace;							// �� �ڽ���
	u32	nXP;							// xp
	int					nBP;							// bp

	int					nKillCount;
	int					nDeathCount;

	// ���ӻ�Ȳ

	u32	nTotalPlayTimeSec;				// �� �÷��� �ð�
	u32	nConnPlayTimeSec;				// ���� ���� �ð�


	u32	nEquipedItemDesc[MMCIP_END];	// ������ ����

	MMatchUserGradeID	nUGradeID;						// account UGrade

	// ClanCLID
	unsigned int		nClanCLID;
};


/// �� ����Ʈ �޶�� ��û�Ҷ� ������ ����ü
struct MTD_StageListNode
{
	MUID			uidStage;							///< �� UID
	unsigned char	nNo;								///< ���ȣ
	char			szStageName[STAGENAME_LENGTH];		///< ���̸�
	char			nPlayers;							///< �����ο�
	char			nMaxPlayers;						///< �ִ��ο�
	STAGE_STATE		nState;								///< �������
	MMATCH_GAMETYPE nGameType;							///< ���� Ÿ��
	char			nMapIndex;							///< ��
	int				nSettingFlag;						///< �� ���� �÷���(����, ��й�, ��������)
	char			nMasterLevel;						///< ���� ����
	char			nLimitLevel;						///< ���ѷ���
};

/// Ŭ���̾�Ʈ�� �˾ƾ��� ��Ÿ���� : AdminHide ���¸� ���������� ��ȯ & ��ȭ���Ͽ� ����
struct MTD_ExtendInfo
{
	char			nTeam;
	unsigned char	nPlayerFlags;	// �÷��̾� �Ӽ�(��ڼ����) - MTD_PlayerFlags ���
	unsigned char	nReserved1;		// ����
	unsigned char	nReserved2;
};

struct MTD_PeerListNode
{
	MUID			uidChar;
	u32			dwIP;
	unsigned int	nPort;
	MTD_CharInfo	CharInfo;
	MTD_ExtendInfo	ExtendInfo;
};


// ���� �亯��
struct MTD_ReplierNode
{
	char szName[MATCHOBJECT_NAME_LENGTH];
};


// ���� ���� ��û �� �׷�
struct MTD_LadderTeamMemberNode
{
	char szName[MATCHOBJECT_NAME_LENGTH];

};

// Ŭ�� ����
struct MTD_ClanInfo
{
	char				szClanName[CLAN_NAME_LENGTH];		// Ŭ�� �̸�
	short				nLevel;								// ����
	int					nPoint;								// ����Ʈ
	int					nTotalPoint;						// ��Ż����Ʈ
	int					nRanking;							// ��ŷ
	char				szMaster[MATCHOBJECT_NAME_LENGTH];	// Ŭ�� ������
	unsigned short		nWins;								// ���� - �¼�
	unsigned short		nLosses;							// ���� - �м�
	unsigned short		nTotalMemberCount;					// ��ü Ŭ������
	unsigned short		nConnedMember;						// ���� ���ӵ� Ŭ������
	unsigned int		nCLID;								// ClanID
	unsigned int		nEmblemChecksum;					// Emblem Checksum
};

// Ŭ���� ������� Ŭ�� ����Ʈ
struct MTD_StandbyClanList
{
	char				szClanName[CLAN_NAME_LENGTH];		// Ŭ�� �̸�
	short				nPlayers;							// ������� �ο���
	short				nLevel;								// ����
	int					nRanking;							// ��ŷ - 0�̸� unranked
	unsigned int		nCLID;								// ClanID
	unsigned int		nEmblemChecksum;					// Emblem Checksum
};


// ����Ʈ, �����̹��� ���� ����
struct MTD_QuestGameInfo
{
	unsigned short		nQL;												// ����Ʈ ����
	float				fNPC_TC;											// NPC ���̵� ���� ���
	unsigned short		nNPCCount;											// ���ʹ� ������ NPC����

	unsigned char		nNPCInfoCount;										// ������ NPC ���� ����
	unsigned char		nNPCInfo[MAX_QUEST_NPC_INFO_COUNT];					// ������ NPC ����
	unsigned short		nMapSectorCount;									// �� ��� ����
	unsigned short		nMapSectorID[MAX_QUEST_MAP_SECTOR_COUNT];			// �� ��� ID
	char				nMapSectorLinkIndex[MAX_QUEST_MAP_SECTOR_COUNT];	// �� ����� Link Index

};

// ����Ʈ, ���� ����
struct MTD_QuestReward
{
	MUID				uidPlayer;	// �ش� �÷��̾� UID
	int					nXP;		// �ش� �÷��̾ ���� XP
	int					nBP;		// �ش� �÷��̾ ���� BP
};

// ����Ʈ ������ ���� ����
struct MTD_QuestItemNode
{
	int		m_nItemID;
	int		m_nCount;
};

// ����Ʈ �Ϲ� ������ ���� ����
struct MTD_QuestZItemNode
{
	unsigned int		m_nItemID;
	int					m_nRentPeriodHour;
};


struct MTD_ServerStatusInfo
{
	u32			m_dwIP;
	int				m_nPort;
	unsigned char	m_nServerID;
	short			m_nMaxPlayer;
	short			m_nCurPlayer;
	char			m_nType;
	bool			m_bIsLive;
};

struct MTD_ResetTeamMembersData
{
	MUID			m_uidPlayer;		// �ش� �÷��̾�
	char			nTeam;				// ��
};


// ��� ť ����

struct MTD_DuelQueueInfo
{
	MUID			m_uidChampion;
	MUID			m_uidChallenger;
	MUID			m_WaitQueue[14];				// ��
	char			m_nQueueLength;
	char			m_nVictory;						// ���¼�
	bool			m_bIsRoundEnd;					// ���� �������ΰ�
};

struct MTD_GunGameWeaponInfo
{
	u32 WeaponIDs[5];
};

struct MTD_ClientSettings
{
	bool DebugOutput = false;
};

struct MTD_PingInfo
{
	MUID UID;
	uint16_t Ping;
};

struct MFRIENDLISTNODE {
	unsigned char	nState;
	char			szName[MATCHOBJECT_NAME_LENGTH];
	char			szDescription[MATCH_SIMPLE_DESC_LENGTH];
};

struct ZACTOR_BASICINFO {
	float			fTime;
	MUID			uidNPC;
	short			posx, posy, posz;
	short			velx, vely, velz;
	short			dirx, diry, dirz;
	u8			anistate;
};

struct ZPACKEDSHOTINFO {
	float	fTime;
	short	posx, posy, posz;
	short	tox, toy, toz;
	u8	sel_type;
	std::string zItemCRC32;
};

struct ZPACKEDDASHINFO {
	short	posx, posy, posz;
	short	dirx, diry, dirz;
	u8	seltype;
};

#pragma pack(pop, old)


// admin ����
enum ZAdminAnnounceType
{
	ZAAT_CHAT = 0,
	ZAAT_MSGBOX
};



/////////////////////////////////////////////////////////
void Make_MTDItemNode(MTD_ItemNode* pout, const MUID& uidItem, u32 nItemID, int nRentMinutePeriodRemainder);
void Make_MTDAccountItemNode(MTD_AccountItemNode* pout, int nAIID, u32 nItemID, int nRentMinutePeriodRemainder);

void Make_MTDQuestItemNode( MTD_QuestItemNode* pOut, const u32 nItemID, const int nCount );

// ����ġ, ����ġ ������ 4byte�� ����
// ���� 2����Ʈ�� ����ġ, ���� 2����Ʈ�� ����ġ�� �ۼ�Ʈ�̴�.
inline u32 MakeExpTransData(int nAddedXP, int nPercent)
{
	u32 ret = 0;
	ret |= (nAddedXP & 0x0000FFFF) << 16;
	ret |= nPercent & 0xFFFF;
	return ret;
}
inline int GetExpFromTransData(u32 nValue)
{
	return (int)((nValue & 0xFFFF0000) >> 16);

}
inline int GetExpPercentFromTransData(u32 nValue)
{
	return (int)(nValue & 0x0000FFFF);
}



#endif
