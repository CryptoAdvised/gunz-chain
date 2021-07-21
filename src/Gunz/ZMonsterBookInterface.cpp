/***********************************************************************
  ZMonsterBookInterface.cpp
  
  ��  �� : ���� ���� �������̽�
  �ۼ��� : 29, MAR, 2004
  �ۼ��� : �ӵ�ȯ
************************************************************************/


#include "stdafx.h"							// Include stdafx.h
#include "ZMonsterBookInterface.h"			// Include ZMonsterBookInterface.h
#include "ZGameInterface.h"					// Include ZGameInterface.h
#include "ZQuest.h"							// Include ZQuest.h
#include "ZToolTip.h"						// Include ZToolTip.h


/***********************************************************************
  ZMonsterBookInterface : public
  
  desc : ������
************************************************************************/
ZMonsterBookInterface::ZMonsterBookInterface( void)
{
	m_pBookBgImg = NULL;
	m_pIllustImg = NULL;
}


/***********************************************************************
  ~ZMonsterBookInterface : public
  
  desc : �Ҹ���
************************************************************************/
ZMonsterBookInterface::~ZMonsterBookInterface( void)
{
}


/***********************************************************************
  OnCreate : public
  
  desc : ���� ���� ���̱�
  arg  : none
  ret  : none
************************************************************************/
void ZMonsterBookInterface::OnCreate( void)
{
	// Get resource pointer
	ZIDLResource* pResource = ZApplication::GetGameInterface()->GetIDLResource();


	// ���� �ʱ�ȭ
	m_nCurrentPage = 0;			// 0 �������� �ʱ�ȭ
	m_bIsFirstPage = true;


	// ����Ʈ�� �ʿ��� ���� �ε�
	ZGetQuest()->Load();
	ReadQuestItemXML();


	// �κ� UI ���߱�
	MWidget* pWidget = pResource->FindWidget( "Lobby");
	if ( pWidget)
		pWidget->Show( false);


	// �������� �׸���
	DrawPage();

	// ���� ���� ���̱�
	pWidget = pResource->FindWidget( "MonsterBook");
	if ( pWidget)
		pWidget->Show( true);

	
	// ��Ʈ�� �̹��� �ִϸ��̼�
	MPicture* pPicture = (MPicture*)pResource->FindWidget( "MonsterBook_StripBottom");
 	if( pPicture)
		pPicture->SetAnimation( 0, 1000.0f);
	pPicture = (MPicture*)pResource->FindWidget( "MonsterBook_StripTop");
	if( pPicture)
		pPicture->SetAnimation( 1, 1000.0f);
}


/***********************************************************************
  OnDestroy : public
  
  desc : ���� ���� ���߱�
  arg  : none
  ret  : none
************************************************************************/
void ZMonsterBookInterface::OnDestroy( void)
{
	// Get resource pointer
	ZIDLResource* pResource = ZApplication::GetGameInterface()->GetIDLResource();


	// ���� ���� ���߱�
	MWidget* pWidget = pResource->FindWidget( "MonsterBook");
	if ( pWidget)
		pWidget->Show( false);


	// ��� å �̹����� �޸𸮷κ��� �����Ѵ�
	if ( m_pBookBgImg != NULL)
	{
		// ��� å �̹����� �����ִ� ������ ��Ʈ�� �̹��� �����͸� �����Ѵ�
		MPicture* pPicture = (MPicture*)pResource->FindWidget( "MonsterBook_BookBG");
		if ( pPicture)
			pPicture->SetBitmap( NULL);
	
		delete m_pBookBgImg;
		m_pBookBgImg = NULL;
	}


	// ����Ʈ ������ ����Ʈ ����
	m_QuestItemDesc.clear();


	// �Ϸ���Ʈ �̹��� ����
	DeleteIllustImage();


	// �κ� UI ���̱�
	pWidget = pResource->FindWidget( "Lobby");
	if ( pWidget)
		pWidget->Show( true);
}


/***********************************************************************
  OnPrevPage : public
  
  desc : ���� ������ �ѱ�� ��ư�� ������ ��
  arg  : none
  ret  : none
************************************************************************/
void ZMonsterBookInterface::OnPrevPage( void)
{
	// ������ ������ ��ȣ�� ���Ѵ�
	if ( m_nCurrentPage == 0)
		m_nCurrentPage = ZGetQuest()->GetNumOfPage();
	else
		m_nCurrentPage--;


	// �������� �׸���
	DrawPage();
}


/***********************************************************************
  OnNextPage : public
  
  desc : ���� ������ �ѱ�� ��ư�� ������ ��
  arg  : none
  ret  : none
************************************************************************/
void ZMonsterBookInterface::OnNextPage( void)
{
	// ������ ������ ��ȣ�� ���Ѵ�
	if ( m_nCurrentPage == ZGetQuest()->GetNumOfPage())
		m_nCurrentPage = 0;
	else
		m_nCurrentPage++;


	// �������� �׸���
	DrawPage();
}


/***********************************************************************
  DrawPage : protected
  
  desc : �������� �׸���
  arg  : none
  ret  : none
************************************************************************/
void ZMonsterBookInterface::DrawPage( void)
{
	// ���� ǥ���̸�(0������) �������� �׸���.
	if ( m_nCurrentPage == 0)
	{
		DrawFirstPage();
		return;
	}


	// Get resource pointer
	ZIDLResource* pResource = ZApplication::GetGameInterface()->GetIDLResource();


	// ��� å �̹����� �ε��Ѵ�
	if ( m_bIsFirstPage == true)
	{
		if ( m_pBookBgImg != NULL)
		{
			delete m_pBookBgImg;
			m_pBookBgImg = NULL;
		}

		m_pBookBgImg = new MBitmapR2;
		((MBitmapR2*)m_pBookBgImg)->Create( "monsterIllust.png", RGetDevice(), "interface/MonsterIllust/book_bg.jpg");
		if ( m_pBookBgImg)
		{
			// �о�� ��Ʈ�� �̹��� �����͸� �ش� ������ �Ѱ��༭ ǥ���Ѵ�
			MPicture* pPicture = (MPicture*)pResource->FindWidget( "MonsterBook_BookBG");
			if ( pPicture)
				pPicture->SetBitmap( m_pBookBgImg->GetSourceBitmap());
		}
	}

	// ������ ��ȣ�� ������Ʈ �Ѵ�
	MLabel* pLabel = (MLabel*)pResource->FindWidget( "MonsterBook_PageNumber");
	if ( pLabel)
	{
		char szPageNum[ 20];
		sprintf_safe( szPageNum, "- %d -", m_nCurrentPage);
		pLabel->SetText( szPageNum);
	}


	// �޼���
	pLabel = (MLabel*)pResource->FindWidget( "MonsterBook_Complete");
	if ( pLabel)
		pLabel->SetText( "");


	// ���� �������� ���� ���� ������ ���´�
	MQuestNPCInfo* pMonsterInfo = ZGetQuest()->GetNPCPageInfo( m_nCurrentPage - 1);


	// ������ ��� �����ۿ� ���� ������ ������Ʈ �Ѵ�
	int nCount = 0;
	int nMatchedItem = 0;
	if ( pMonsterInfo)
	{
		MQuestDropSet* pDropItem = ZGetQuest()->GetDropTable()->Find( pMonsterInfo->nDropTableID);

		if ( pDropItem)
		{
			for ( set<int>::iterator i = pDropItem->GetQuestItems().begin();  i != pDropItem->GetQuestItems().end();  i++)
			{
				char szWidgetName[ 50];
				sprintf_safe( szWidgetName, "MonsterBook_DropItem%d", nCount);
				MPicture* pPicture = (MPicture*)pResource->FindWidget( szWidgetName);
				if ( pPicture)
				{
					ZMyQuestItemMap::iterator itr = ZGetMyInfo()->GetItemList()->GetQuestItemMap().find( *i);
					if ( itr != ZGetMyInfo()->GetItemList()->GetQuestItemMap().end())
					{
						map< int, MQuestItemSimpleDesc>::iterator Iterator;
						if ( ReadSimpleQuestItemDesc( *i, &Iterator))
						{
							pPicture->AttachToolTip( (*Iterator).second.m_szName);
							pPicture->SetBitmap( ZApplication::GetGameInterface()->GetQuestItemIcon( *i, true));
							nMatchedItem++;
						}
					}
					else
					{
						pPicture->AttachToolTip( "?????");
						pPicture->SetBitmap( MBitmapManager::Get( "slot_icon_unknown.tga"));
					}
					pPicture->Show( true);
				}
				nCount++;
			}
		}
	}
	
	int nPercentage = (int)( (float)nMatchedItem / (float)nCount * 100.0f + 0.5);
//	if ( nCount == 0)
		nPercentage = 100;

	for ( ;  nCount < 10;  nCount++)
	{
		char szWidgetName[ 50];
		sprintf_safe( szWidgetName, "MonsterBook_DropItem%d", nCount);
		MWidget* pWidget = pResource->FindWidget( szWidgetName);
		if ( pWidget)
			pWidget->Show( false);
	}


	// �ش� ������ �̸��� ������Ʈ �Ѵ�
	pLabel = (MLabel*)pResource->FindWidget( "MonsterBook_MonsterName");
	if (pLabel)
		pLabel->SetText( (pMonsterInfo) ? pMonsterInfo->szName : "");


	// �ش� ������ ����� ������Ʈ �Ѵ�
	pLabel = (MLabel*)pResource->FindWidget( "MonsterBook_MonsterGrade");
	if ( pLabel)
	{
		if ( nPercentage >= 20)
		{
			if  ( pMonsterInfo)
			{
				char szGrade[ 128];
				sprintf_safe( szGrade, "%s : ", ZMsg(MSG_WORD_GRADE));
				switch ( pMonsterInfo->nGrade)
				{
					case NPC_GRADE_REGULAR :
						strcat_safe( szGrade, ZMsg(MSG_WORD_REGULAR));
						break;

					case NPC_GRADE_LEGENDARY :
						strcat_safe( szGrade, ZMsg(MSG_WORD_LEGENDARY));
						break;

					case NPC_GRADE_BOSS :
						strcat_safe( szGrade, ZMsg(MSG_WORD_BOSS));
						break;

					case NPC_GRADE_ELITE :
						strcat_safe( szGrade, ZMsg(MSG_WORD_ELITE));
						break;

					case NPC_GRADE_VETERAN :
						strcat_safe( szGrade, ZMsg(MSG_WORD_VETERAN));
						break;
				}
				pLabel->SetText( szGrade);
			}
			else
				pLabel->SetText( "");
		}
		else
		{
			char szGrade[ 128];
			sprintf_safe( szGrade, "%s : ?????", ZMsg(MSG_WORD_GRADE));
			pLabel->SetText( szGrade);
		}
	}

	MTextArea* pTextArea = (MTextArea*)pResource->FindWidget( "MonsterBook_MonsterDesc");
	if ( pTextArea)
	{
		pTextArea->Clear();

		if ( nPercentage >= 20)
			pTextArea->AddText( (pMonsterInfo) ? pMonsterInfo->szDesc : "", MCOLOR( 0xFF321E00));
		else
			pTextArea->AddText( "?????", MCOLOR( 0xFF321E00));
	}

	pLabel = (MLabel*)pResource->FindWidget( "MonsterBook_MonsterHP");
	if ( pLabel)
	{
		if ( nPercentage >= 50)
		{
			if  ( pMonsterInfo)
			{
				char szHP[ 128];
				strcpy_safe( szHP, "HP : ");

				if ( pMonsterInfo->nMaxHP > 200)
					strcat_safe( szHP, ZMsg(MSG_WORD_VERYHARD));
				else if ( pMonsterInfo->nMaxHP > 120)
					strcat_safe( szHP, ZMsg(MSG_WORD_HARD));
				else if ( pMonsterInfo->nMaxHP > 80)
					strcat_safe( szHP, ZMsg(MSG_WORD_NORAML));
				else if ( pMonsterInfo->nMaxHP > 30)
					strcat_safe( szHP, ZMsg(MSG_WORD_WEAK));
				else
					strcat_safe( szHP, ZMsg(MSG_WORD_VERYWEAK));

				pLabel->SetText( szHP);
			}
			else
				pLabel->SetText( "");
		}
		else
			pLabel->SetText( "HP : ?????");
	}

	pTextArea = (MTextArea*)pResource->FindWidget( "MonsterBook_Attacks");
	if ( pTextArea)
	{
		pTextArea->Clear();

		if ( nPercentage >= 80)
		{
			if ( pMonsterInfo)
			{
				for ( int i = 0;  i < pMonsterInfo->nSkills;  i++)
				{
					ZSkillManager::iterator iterator = ZGetApplication()->GetSkillManager()->find( pMonsterInfo->nSkillIDs[ i]);
					if ( iterator != ZGetApplication()->GetSkillManager()->end())
						pTextArea->AddText( (*iterator).second->szName, MCOLOR( 0xFF321E00));
				}
			}
		}
		else
			pTextArea->AddText( "?????", MCOLOR( 0xFF321E00));
	}

	if ( nPercentage >= 100)
	{
		char szFileName[ 256];
		if ( pMonsterInfo)
			sprintf_safe( szFileName, "monster_Illust%02d.jpg", (int)pMonsterInfo->nID);
		SetIllustImage( (pMonsterInfo) ? szFileName : "");
	}
	else
		DeleteIllustImage();

	MWidget* pWidget = pResource->FindWidget( "MonsterBook_PrevPageButton");
	if ( pWidget)
		pWidget->Show( true);

	pWidget = pResource->FindWidget( "MonsterBook_NextPageButton");
	if ( pWidget)
	{
		if ( m_nCurrentPage == ZGetQuest()->GetNumOfPage())
			pWidget->Show( false);
		else
			pWidget->Show( true);
	}

	m_bIsFirstPage = false;
}

void ZMonsterBookInterface::DrawFirstPage( void)
{
	// Get resource pointer
	ZIDLResource* pResource = ZApplication::GetGameInterface()->GetIDLResource();

	if ( m_pBookBgImg != NULL)
	{
		delete m_pBookBgImg;
		m_pBookBgImg = NULL;
	}

	m_pBookBgImg = new MBitmapR2;
	((MBitmapR2*)m_pBookBgImg)->Create( "monsterIllust.png", RGetDevice(), "interface/MonsterIllust/book_firstbg.jpg");
	if ( m_pBookBgImg)
	{
		MPicture* pPicture = (MPicture*)pResource->FindWidget( "MonsterBook_BookBG");
		if ( pPicture)
			pPicture->SetBitmap( m_pBookBgImg->GetSourceBitmap());
	}

	DeleteIllustImage();

	DrawComplete();

	MLabel* pLabel = (MLabel*)pResource->FindWidget( "MonsterBook_PageNumber");
	if ( pLabel)
		pLabel->SetText( "");

	pLabel = (MLabel*)pResource->FindWidget( "MonsterBook_MonsterName");
	if (pLabel)
		pLabel->SetText( "");

	pLabel = (MLabel*)pResource->FindWidget( "MonsterBook_MonsterGrade");
	if ( pLabel)
		pLabel->SetText( "");

	pLabel = (MLabel*)pResource->FindWidget( "MonsterBook_MonsterHP");
	if ( pLabel)
		pLabel->SetText( "");

	MTextArea* pTextArea = (MTextArea*)pResource->FindWidget( "MonsterBook_MonsterDesc");
	if ( pTextArea)
		pTextArea->Clear();

	pTextArea = (MTextArea*)pResource->FindWidget( "MonsterBook_Attacks");
	if ( pTextArea)
		pTextArea->Clear();

	for ( int i = 0;  i < 10;  i++)
	{
		char szWidgetName[ 128];
		sprintf_safe( szWidgetName, "MonsterBook_DropItem%d", i);
		MWidget* pWidget = pResource->FindWidget( szWidgetName);
		if ( pWidget)
			pWidget->Show( false);
	}

	MWidget* pWidget = pResource->FindWidget( "MonsterBook_PrevPageButton");
	if ( pWidget)
		pWidget->Show( false);

	pWidget = pResource->FindWidget( "MonsterBook_NextPageButton");
	if ( pWidget)
		pWidget->Show( true);


	m_bIsFirstPage = true;
}

bool ZMonsterBookInterface::SetIllustImage( const char* szFileName)
{
	// Get resource pointer
	ZIDLResource* pResource = ZApplication::GetGameInterface()->GetIDLResource();

	DeleteIllustImage();

	// Error check
	if ( strlen( szFileName) == 0)
		return false;

	m_pIllustImg = new MBitmapR2;
	char szFullFileName[256];
	sprintf_safe( szFullFileName, "interface/MonsterIllust/%s", szFileName);
	((MBitmapR2*)m_pIllustImg)->Create( "monsterIllust.png", RGetDevice(), szFullFileName);

	if ( !m_pIllustImg)
		return false;

	MPicture* pPicture = (MPicture*)pResource->FindWidget( "MonsterBook_MonsterIllust");
	if ( pPicture)
		pPicture->SetBitmap( m_pIllustImg->GetSourceBitmap());

	return true;
}


/***********************************************************************
  DeleteIllustImage : public
  
  desc : �о�Դ� ���� �Ϸ���Ʈ �̹����� �޸𸮿��� �����Ѵ�
  arg  : none
  ret  : true(=success) or false(=fail)
************************************************************************/
bool ZMonsterBookInterface::DeleteIllustImage( void)
{
	// Get resource pointer
	ZIDLResource* pResource = ZApplication::GetGameInterface()->GetIDLResource();


	// �Ϸ���Ʈ�� �����ִ� ������ ��Ʈ�� �̹��� �����͸� �����Ѵ�
	MPicture* pPicture = (MPicture*)pResource->FindWidget( "MonsterBook_MonsterIllust");
	if ( pPicture)
		pPicture->SetBitmap( NULL);


	// �Ϸ���Ʈ �̹����� �޸𸮷κ��� �����Ѵ�
	if ( m_pIllustImg)
	{
		delete m_pIllustImg;
		m_pIllustImg = NULL;
	}

	return true;
}


/***********************************************************************
  ReadQuestItemXML : protected
  
  desc : ����Ʈ ��� ������ XML�� �д´�
  arg  : none
  ret  : true(=success) or false(=fail)
************************************************************************/
bool ZMonsterBookInterface::ReadQuestItemXML()
{
	auto Filename = "System/zquestitem.xml";

	MXmlDocument xmlQuestItemDesc;
	if( !xmlQuestItemDesc.LoadFromFile(Filename, ZApplication::GetFileSystem()))
	{
		return false;
	}

	MXmlElement rootElement = xmlQuestItemDesc.GetDocumentElement();
	for ( int i = 0;  i < rootElement.GetChildNodeCount();  i++)
	{
		MXmlElement chrElement = rootElement.GetChildNode( i);

		char szTagName[ 256];
		chrElement.GetTagName( szTagName);

		if ( szTagName[ 0] == '#')
			continue;

		bool bFindPage = false;
		if ( !_stricmp( szTagName, "ITEM"))
		{
			char szAttrName[64];
			char szAttrValue[256];
			int nItemID = 0;
			MQuestItemSimpleDesc SimpleDesc;
			
			// Set Tag
			for ( int k = 0;  k < chrElement.GetAttributeCount();  k++)
			{
				chrElement.GetAttribute( k, szAttrName, szAttrValue);

				if ( !_stricmp( szAttrName, "id"))				// ID
					nItemID = atoi( szAttrValue);

				else if ( !_stricmp( szAttrName, "name"))		// Name
					strcpy_safe( SimpleDesc.m_szName, szAttrValue);
			}

			m_QuestItemDesc.insert( map< int, MQuestItemSimpleDesc>::value_type( nItemID, SimpleDesc));
		}
	}

	xmlQuestItemDesc.Destroy();

	return true;
}


/***********************************************************************
  ReadSimpleQuestItemDesc : protected
  
  desc : ��� ������ ����Ʈ�κ��� ������ ������ ��´�
  arg  : nItemID = ������ ID
         pIterator* = ���Ϲ��� Iterrator
  ret  : true(=success) or false(=fail)
************************************************************************/
bool ZMonsterBookInterface::ReadSimpleQuestItemDesc( int nItemID,
	map< int, MQuestItemSimpleDesc>::iterator* pIterator)
{
	map< int, MQuestItemSimpleDesc>::iterator iterator;
	iterator = m_QuestItemDesc.find( nItemID);

	if ( iterator == m_QuestItemDesc.end())
		return false;

	*pIterator = iterator;

	return true;
}


/***********************************************************************
  DrawComplete : protected
  
  desc : ��� ������ ����Ʈ�κ��� ������ ������ ��´�
  arg  : nItemID = ������ ID
         pIterator* = ���Ϲ��� Iterrator
  ret  : true(=success) or false(=fail)
************************************************************************/
void ZMonsterBookInterface::DrawComplete( void)
{
	int nMatchedItemNum = 0;
	int nTotalItemNum = 0;
	for ( int i = 0;  i < ZGetQuest()->GetNumOfPage(); i++)
	{
		// ���� �������� ���� ���� ������ ���´�
		MQuestNPCInfo* pMonsterInfo = ZGetQuest()->GetNPCPageInfo( i);
		if ( pMonsterInfo)
		{
			MQuestDropSet* pDropItem = ZGetQuest()->GetDropTable()->Find( pMonsterInfo->nDropTableID);

			if ( pDropItem)
			{
				for ( set<int>::iterator itr = pDropItem->GetQuestItems().begin();  itr != pDropItem->GetQuestItems().end();  itr++)
				{
					if ( ZGetMyInfo()->GetItemList()->GetQuestItemMap().find( *itr) != ZGetMyInfo()->GetItemList()->GetQuestItemMap().end())
						nMatchedItemNum++;

					nTotalItemNum++;
				}
			}
		}
	}

	int nPercentage = (int)( (float)nMatchedItemNum / (float)nTotalItemNum * 100.0f + 0.5);


	MLabel* pLabel = (MLabel*)ZApplication::GetGameInterface()->GetIDLResource()->FindWidget( "MonsterBook_Complete");
	if ( pLabel)
	{
		char szComplete[ 128];
		sprintf_safe( szComplete, "%s : %d%%", ZMsg(MSG_WORD_RATE), nPercentage);
		pLabel->SetText( szComplete);
	}
}
