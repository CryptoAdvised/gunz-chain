/***********************************************************************
  ZStageInterface.h
  
  ��  �� : �������� �������̽��� �����ϴ� Ŭ����. �ڵ� �������� ���� ����
           �и�����(��� ���� ������ �� �и� ������. -_-;).
  �ۼ��� : 11, MAR, 2004
  �ۼ��� : �ӵ�ȯ
************************************************************************/


#ifndef _ZSTAGEINTERFACE_H
#define _ZSTAGEINTERFACE_H

#define SACRIFICEITEM_SLOT0		0
#define SACRIFICEITEM_SLOT1		1

#include "MListBox.h"



// ������ ���Կ� �ִ� ������ ����
class SacrificeItemSlotDesc
{
protected:
	MUID		m_uidUserID;
	int			m_nItemID;
	MBitmap*	m_pIconBitmap;
	char		m_szItemName[25];
	int			m_nQL;
	bool		m_bExist;
    

public:
	SacrificeItemSlotDesc()
	{
		m_nItemID = 0;
		m_pIconBitmap = NULL;
		m_szItemName[ 0] = 0;
		m_nQL = 0;
		m_bExist = false;
	}

public:
	void SetSacrificeItemSlot( const MUID& uidUserID, const u32 nItemID, MBitmap* pBitmap, const char* szItemName, const int nQL);
	void RemoveItem( void)						{ m_bExist = false; }

	MUID GetUID( void)							{ return m_uidUserID; }
	MBitmap* GetIconBitmap( void)				{ return m_pIconBitmap; }
	u32 GetItemID( void)			{ return m_nItemID; }
	const char* GetName( void)					{ return m_szItemName; }
	int GetQL( void)							{ return m_nQL; }
	bool IsExist( void)							{ return m_bExist; }
};


// ��� �����۹ڽ� ����Ʈ ������
class SacrificeItemListBoxItem : public MListItem
{
protected:
	u32		m_nItemID;
	MBitmap*			m_pBitmap;
	char				m_szName[ 128];
	int					m_nCount;
	char				m_szDesc[ 256];

public:
	SacrificeItemListBoxItem( const u32 nItemID, MBitmap* pBitmap, const char* szName, int nCount, const char* szDesc)
	{
		m_nItemID = nItemID;
		m_pBitmap = pBitmap;
		m_nCount  = nCount;
		strcpy_safe( m_szName, szName);
		strcpy_safe( m_szDesc, szDesc);
	}
	virtual const char* GetString( void)
	{
		return m_szName;
	}
	virtual const char* GetString( int i)
	{
		if ( i == 1)
			return m_szName;

		return NULL;
	}
	virtual MBitmap* GetBitmap( int i)
	{
		if ( i == 0)
			return m_pBitmap;

		return NULL;
	}
	virtual bool GetDragItem(MBitmap** ppDragBitmap, char* szDragString, int maxlen1, char* szDragItemString, int maxlen2)
	{
		*ppDragBitmap = GetBitmap(0);
		strcpy_safe( szDragString, maxlen1, m_szName);
		strcpy_safe( szDragItemString, maxlen2, m_szName);

		return true;
	}

	u32 GetItemID( void)		{ return m_nItemID; }
	const char* GetItemName( void)		{ return m_szName; }
	int GetItemCount( void)				{ return m_nCount; }
	const char* GetItemDesc( void)		{ return m_szDesc; }
};

struct SpecialScenario
{
	char Title[32];
	char MapSet[32];
	int ID;
};

struct ScenarioManager
{
	std::vector<std::array<char, 32>> MapNames;
	std::vector<SpecialScenario> SpecialScenarios;
	bool Loaded{};

	bool Load();
	const SpecialScenario* GetSpecialScenario(int ID) const;
};

inline ScenarioManager& GetScenarioManager() { static ScenarioManager sm; return sm; }

// Class : ZStageInterface
class ZStageInterface
{
protected:	// protected varialbes
	bool			m_bDrawStartMovieOfQuest;
	DWORD			m_dwClockOfStartMovie;
	int				m_nPosOfItem0, m_nPosOfItem1;
	MMATCH_GAMETYPE		m_nGameType;
	bool			m_bPrevQuest;								// ���� ���� Ÿ���� ����Ʈ������ �ƴ���...
	MBitmapR2*		m_pTopBgImg;								// ��� �� �̹���
	MBitmapR2*		m_pStageFrameImg;							// ������ �̹���
	MBitmapR2*		m_pItemListFrameImg;						// ������ ����Ʈ ������ �̹���

protected:	// protected functions
	void UpdateSacrificeItem( void);
	void UpdateStageGameInfo(const int nQL, const int nMapsetID, const int nScenarioID);

public:		// public variables
	SacrificeItemSlotDesc	m_SacrificeItem[ 2];				// ������ ������ ���Կ� �ִ� �����ۿ� ���� ������ ����
	
	int				m_nListFramePos;							// ������ ����Ʈ ������ ��ġ
	int				m_nStateSacrificeItemBox;					// ������ ����Ʈ ������ ����

public:		// public functions
	// Initialize
	ZStageInterface( void);										// Constructor
	virtual ~ZStageInterface( void);							// Destructor
	void OnCreate( void);										// On create
	void OnDestroy( void);										// On destroy
	void OpenSacrificeItemBox( void);
	void CloseSacrificeItemBox( void);
	void HideSacrificeItemBox( void);
	void GetSacrificeItemBoxPos( void);


	// Game stage interface
	void ChangeStageButtons( bool bForcedEntry, bool bMaster, bool bReady);
	void ChangeStageGameSetting( MSTAGE_SETTING_NODE* pSetting);
	void ChangeStageEnableReady( bool bReady);
	void SetMapName(const char* szMapName);

	void OnStageInterfaceSettup( void);							// Change map combobox
	void OnSacrificeItem0( void);								// Push a button : sacrifice item 0
	void OnSacrificeItem1( void);								// Push a button : sacrifice item 1
	void OnDropSacrificeItem( int nSlotNum);					// Drop sacrifice item
	void OnRemoveSacrificeItem( int nSlotNum);					// Remove sacrifice item

	// Start Movie
	void OnDrawStartMovieOfQuest( void);
	void StartMovieOfQuest( void);
	bool IsShowStartMovieOfQuest( void);


	// Sacrifice item list box
	void SerializeSacrificeItemListBox( void);					// ������ �ڽ� ������Ʈ
	bool ReadSenarioNameXML( void);

#ifdef _QUEST_ITEM
	bool OnResponseDropSacrificeItemOnSlot( const int nResult, const MUID& uidRequester, const int nSlotIndex, const int nItemID );
	bool OnResponseCallbackSacrificeItem( const int nResult, const MUID& uidRequester, const int nSlotIndex, const int nItemID );
	bool OnResponseQL( const int nQL );
	bool OnResponseSacrificeSlotInfo( const MUID& uidOwner1, const u32 nItemID1, 
									  const MUID& uidOwner2, const u32 nItemID2 );
	bool OnNotAllReady();
	bool OnQuestStartFailed( const int nState );
	bool OnStageGameInfo( const int nQL, const int nMapsetID, const unsigned int nScenarioID );
#endif

	bool OnStopVote();
};

void OnDropCallbackRemoveSacrificeItem( void* pSelf, MWidget* pSender, MBitmap* pBitmap, const char* szString, const char* szItemString);

// Listner
MListener* ZGetSacrificeItemListBoxListener( void);


#endif
