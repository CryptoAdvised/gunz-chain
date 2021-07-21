/***********************************************************************
  ZMonsterBookInterface.h
  
  ��  �� : ���� ���� �������̽�
  �ۼ��� : 29, MAR, 2004
  �ۼ��� : �ӵ�ȯ
************************************************************************/


#ifndef _ZMONSTERBOOKINTERFACE_H
#define _ZMONSTERBOOKINTERFACE_H



// ����Ʈ ��� ������ ���� ����
struct MQuestItemSimpleDesc
{
	char			m_szName[ 32];								// ����Ʈ ��� ������ �̸�
	// ���� �� �� �������ٰ� �� ����...

	MQuestItemSimpleDesc()
	{
		m_szName[ 0] = 0;
	}
};


// Class : ZMonsterBookInterface
class ZMonsterBookInterface
{
// protected varialbes
protected:
	MBitmapR2*		m_pBookBgImg;								// ��� å �̹���
	MBitmapR2*		m_pIllustImg;								// �Ϸ���Ʈ ��Ʈ�� �̹���

	map< int, MQuestItemSimpleDesc>	 m_QuestItemDesc;			// ����Ʈ ������ ���� ����Ʈ

//	ZSkillTable		m_SkillTable;

	int				m_nCurrentPage;								// ���� �����ִ� ������ ��ȣ�� ���

	bool			m_bIsFirstPage;								// ù���������� �ƴ���...


// protected functions
protected:
	void DrawPage( void);										// �������� �׸���
	void DrawFirstPage( void);									// ù�������� �׸���
	void DrawComplete( void);									// �޼����� ǥ���Ѵ�

	bool ReadQuestItemXML( void);								// ����Ʈ ��� ������ XML�� �д´�
	bool ReadSimpleQuestItemDesc( int nItemID, map< int, MQuestItemSimpleDesc>::iterator* pIterator);		// ��� ������ ����Ʈ�κ��� ������ ������ ��´�



// public variables
public:


// public functions
public:
	// Initialize
	ZMonsterBookInterface( void);								// Constructor
	virtual ~ZMonsterBookInterface( void);						// Destructor

	void OnCreate( void);										// On Create
	void OnDestroy( void);										// On destroy

	void OnPrevPage( void);										// ���� ������ �ѱ�� ��ư�� ������ ��
	void OnNextPage( void);										// ���� ������ �ѱ�� ��ư�� ������ ��

	bool SetIllustImage( const char* szFileName);				// ���� �������� �ش��ϴ� ���� �Ϸ���Ʈ �̹����� ǥ���Ѵ�
	bool DeleteIllustImage( void);								// �о�Դ� ���� �Ϸ���Ʈ �̹����� �޸𸮿��� �����Ѵ�
};


#endif
