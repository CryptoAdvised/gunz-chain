#include "stdafx.h"

#include "ZApplication.h"
#include "MXML.h"
#include "MZFileSystem.h"
#include "RealSpace2.h"
#include "ZWorldItem.h"
#include "ZCharacter.h"
#include "RDummyList.h"
#include "MDebug.h"
#include "ZPost.h"
#include "ZPostLocal.h"
#include "MDataChecker.h"
#include "MUtil.h"

using namespace RealSpace2;

#define BASE_EFFECT_MODEL "baseEffect"
#define USER_WORLDITEM_FIRST		100			// 100 �����ʹ� ������ ������Ű�� ������ - �Ƿ�Ŷ ��


ZWorldItemManager ZWorldItemManager::msInstance;

//////////////////////////////////////////////////////////////////////////
//		ZWorldItem
//////////////////////////////////////////////////////////////////////////
void ZWorldItem::Initialize( int nID, short nItemID,MTD_WorldItemSubType SubType, ZWORLD_ITEM_STATE state, unsigned int nSpawnTypeFlags, const rvector& position, float fAmount )
{
	m_nID				= nID;
	m_nItemID			= nItemID;
	m_State				= state;
	m_nSpawnTypeFlags	= nSpawnTypeFlags;
	m_SubType			= SubType;
	m_Position			= position;
	m_fAmount			= fAmount;
	m_Dir				= rvector(0,1,0);
	m_Up				= rvector(0,0,1);
}

bool ZWorldItem::ApplyWorldItem( ZCharacter* pCharacter )
{
	int max,maxBullet,maxMagazine,inc,currentBullet,currentMagazine;
	if( pCharacter == NULL || (
		(m_State != WORLD_ITEM_VALIDATE ) && (m_State != WORLD_ITEM_CANDIDATE)) )
		return false;	

	ZItem* pSeletedWeapon = 0;
	switch( m_Type ) 
	{
	case WIT_QUEST:
		break;
	case WIT_HP:
		pCharacter->SetHP( min(	 pCharacter->GetHP() + m_fAmount, pCharacter->GetProperty()->fMaxHP ) );
		break;
	case WIT_AP:
		pCharacter->SetAP( min(	 pCharacter->GetAP() + m_fAmount, pCharacter->GetProperty()->fMaxAP ) );
		break;
	case WIT_HPAP:
		pCharacter->SetHP( min(	 pCharacter->GetHP() + m_fAmount, pCharacter->GetProperty()->fMaxHP ) );
		pCharacter->SetAP( min(	 pCharacter->GetAP() + m_fAmount, pCharacter->GetProperty()->fMaxAP ) );
		break;
	case WIT_BULLET:
		pSeletedWeapon = pCharacter->GetItems()->GetSelectedWeapon();
		if( pSeletedWeapon && pSeletedWeapon->GetItemType() != MMIT_RANGE )
		{
			if( !pCharacter->GetItems()->GetItem(MMCIP_PRIMARY)->IsEmpty() )
				pSeletedWeapon = pCharacter->GetItems()->GetItem(MMCIP_PRIMARY);
			else if( !pCharacter->GetItems()->GetItem(MMCIP_PRIMARY)->IsEmpty() )
				pSeletedWeapon = pCharacter->GetItems()->GetItem(MMCIP_SECONDARY);
			else
				pSeletedWeapon = 0;
		}

		if( pSeletedWeapon )
		{
			currentBullet	= pSeletedWeapon->GetBulletAMagazine();		// ���� ������ źâ���� �Ѿ˼�
			currentMagazine	= pSeletedWeapon->GetBullet();				// ���� �������� ���� źâ���� �Ѿ˼�
			
			inc = pSeletedWeapon->GetDesc()->m_nMagazine;		// �Ѿ� ������
			max = pSeletedWeapon->GetDesc()->m_nMaxBullet;		// ��ü ä������ �ִ� �Ѿ��� ����

			maxBullet = min((max - currentMagazine),inc);
			maxMagazine = max - maxBullet;

			int nBullet = (int)m_fAmount;
			if( currentBullet < inc ) 
			{
				pSeletedWeapon->SetBulletAMagazine( maxBullet );				// ���� źâ�� �Ѿ˼� ä���			
				--nBullet;
			}

			if( nBullet > 0 )
				pSeletedWeapon->SetBullet( min( ( nBullet*inc + currentMagazine ), maxMagazine));

			//// MEMORYHACK ���������� �˷��ش�.
			if (pCharacter->GetUID() == ZGetMyUID()) {
				MDataChecker* pChecker = ZApplication::GetGame()->GetDataChecker();
				pChecker->RenewCheck((BYTE*)pSeletedWeapon->GetBulletPointer(), sizeof(int));
				pChecker->RenewCheck((BYTE*)pSeletedWeapon->GetAMagazinePointer(), sizeof(int));
			}
		}
		break;
	
	default:
		mlog("���� ���� ���� ������ Ÿ���Դϴ�\n");
		return false;
	}

	if( pCharacter == g_pGame->m_pMyCharacter )
	{
		ZGetSoundEngine()->PlaySound("fx_itemget");
	}

	return true;

}

ZWorldItem::ZWorldItem()
{
	m_nID					= 0;
	m_Type				= WIT_HP;
	m_State				= WORLD_ITEM_INVALIDATE;
	m_Position			= rvector( 0.f, 0.f, 0.f );
	m_nSpawnTypeFlags	= WORLD_ITEM_TIME_ONCE;
	m_pVMesh			= NULL;

	m_dwStartTime		 = 0.f;
	m_dwToggleBackupTime = 0.f;

	m_bToggle			= true;
	m_bisDraw			= true;
}

ZWorldItem::~ZWorldItem() 
{
	if(m_pVMesh) {
		delete m_pVMesh;
		m_pVMesh = NULL;
	}
}

void ZWorldItem::CreateVisualMesh()
{
	RMesh* pMesh	= ZGetMeshMgr()->Get( m_modelName );
	m_pVMesh = new RVisualMesh;
	m_pVMesh->Create( pMesh );
	m_pVMesh->SetAnimation("play");
	m_pVMesh->SetCheckViewFrustum(true);
}

//////////////////////////////////////////////////////////////////////////
//		ZWorldItemMananger
//////////////////////////////////////////////////////////////////////////
ZWorldItemManager::ZWorldItemManager()
{
	m_nStandAloneIDGen = 10000000;		// worlditem�� õ���� �̻��� ������ �ʴ´�.

}

int ZWorldItemManager::GenStandAlondID()
{
	return (++m_nStandAloneIDGen);
}

bool ZWorldItemManager::ApplyWorldItem( int nID, ZCharacter* pCharacter )
{
	WIL_Iterator iter = mItemList.find( nID );
	if( iter == mItemList.end() )	return false;

	return ApplyWorldItem( iter, pCharacter );
}

bool ZWorldItemManager::ApplyWorldItem( WIL_Iterator& iter, ZCharacter* pCharacter )
{
	ZWorldItem* pWorldItem = iter->second;
	if( !pWorldItem->ApplyWorldItem( pCharacter ) )	
	{
		mlog("ApplyItem Function�� ���ڿ� ��Ȯ���� �ʽ��ϴ�.(�������� state�� ������ �ִ°� �����ϴ�)\n" );
		return false;	
	}

	// ����Ʈ���� �ٸ� ���� ��ٸ��� ��� ������ ���..

	if( ZGetQuest() && ZGetQuest()->GetQuestState() == MQUEST_COMBAT_PREPARE )
		if( g_pGame->m_pMyCharacter->IsObserverTarget() )// �������������� �Ѿ�� ��ٸ��� ���
			return true;

	switch(pWorldItem->GetType())
	{
		case WIT_HP :
		case WIT_HPAP : 
			ZGetEffectManager()->AddHealEffect( pCharacter->GetPosition(), pCharacter );
			break;
		case WIT_QUEST :
			ZGetEffectManager()->AddEatBoxEffect( pCharacter->GetPosition(), pCharacter );
			break;
		case WIT_AP :
			ZGetEffectManager()->AddRepireEffect( pCharacter->GetPosition(), pCharacter );
			break;
		case WIT_BULLET :
			ZGetEffectManager()->AddExpanseAmmoEffect(pCharacter->GetPosition(), pCharacter );
	}

	if( CheckBitSet(pWorldItem->GetSpawnTypeFlags(), WORLD_ITEM_TIME_ONCE) )
		DeleteWorldItem( iter, false );
	else
		pWorldItem->SetState( WORLD_ITEM_WAITING );

	return true;
}

ZWorldItem *ZWorldItemManager::AddWorldItem( int nID, short nItemID,MTD_WorldItemSubType nItemSubType, const rvector& pos )
{
	ZWorldItem* pWorldItem = NULL;

	WIL_Iterator iterItem = mItemList.find( nID );
	if( iterItem == mItemList.end() )
	{
		map<short, MMatchWorldItemDesc*>::iterator iter = MGetMatchWorldItemDescMgr()->find( nItemID );
		if( iter == MGetMatchWorldItemDescMgr()->end() ) 
		{
			mlog("�߰��Ϸ��� ����������� ���� ���� ���� �̸��Դϴ�\n" );
			return NULL;
		}
		MMatchWorldItemDesc* pDesc = iter->second;

		u32 nSpawnTypeFlags = WORLD_ITEM_TIME_ONCE;
		if (pDesc->m_nItemType == WIT_CLIENT) 
			SetBitSet(nSpawnTypeFlags, WORLD_ITEM_STAND_ALINE);

		pWorldItem = new ZWorldItem();
		pWorldItem->Initialize( nID, nItemID, nItemSubType,WORLD_ITEM_INVALIDATE, nSpawnTypeFlags, pos, pDesc->m_fAmount );
		pWorldItem->SetName( pDesc->m_szDescName );
		pWorldItem->SetModelName( pDesc->m_szModelName );
		pWorldItem->SetType(pDesc->m_nItemType );
		pWorldItem->m_dwStartTime = GetGlobalTimeMS();

		if(pDesc->m_nItemType==WIT_QUEST) {
			pWorldItem->CreateVisualMesh();
		}

		mItemList.insert( WorldItemList::value_type( nID, pWorldItem ));
		iterItem = mItemList.find( nID );
	}
	SpawnWorldItem( iterItem );
	
	return pWorldItem;
}

#define  WORLD_ITEM_RADIUS		100.f
void ZWorldItemManager::update()
{
	ZCharacter* pCharacter = g_pGame->m_pMyCharacter;
	
	if( pCharacter==NULL||pCharacter->IsDead() ) return; 
	
	for(auto* pItem : MakePairValueAdapter(mItemList))
	{
		if( pItem->GetState() == WORLD_ITEM_VALIDATE )
		{
			char szName[64];
			strcpy_safe(szName,pItem->GetName());
			rvector charPos = pCharacter->m_Position;
			rvector itemPos = pItem->GetPosition();
			auto vec = charPos - itemPos;
			if (Magnitude(vec) <= WORLD_ITEM_RADIUS)
			{
				OnOptainWorldItem(pItem);
			}			
		}
	}
}

void ZWorldItemManager::OnOptainWorldItem(ZWorldItem* pItem)
{
	if( !CheckBitSet(pItem->GetSpawnTypeFlags(), WORLD_ITEM_STAND_ALINE) )
	{
		if (ZGetGameClient()->GetMatchStageSetting()->GetNetcode() != NetcodeType::ServerBased)
			ZPostRequestObtainWorldItem( ZGetGameClient()->GetPlayerUID(), pItem->GetID() );
	}
	else
	{
		ZPostLocalEventOptainSpecialWorldItem(int(pItem->GetItemID()));
	}

	pItem->SetState( WORLD_ITEM_CANDIDATE );
}

void ZWorldItemManager::Clear()
{
	for( WIL_Iterator iter = mItemList.begin(); iter != mItemList.end(); )
	{
		SAFE_DELETE( iter->second );
		iter = mItemList.erase( iter );
	}
	mDrawer.Clear();
}

bool ZWorldItemManager::DeleteWorldItem( int nID , bool bDrawRemoveEffect)
{
	WIL_Iterator iter = mItemList.find( nID );
	if( iter == mItemList.end() )	return false;

	DeleteWorldItem( iter, bDrawRemoveEffect);
	return true;
}

void ZWorldItemManager::DeleteWorldItem( WIL_Iterator& iter , bool bDrawRemoveEffect)
{
	if (bDrawRemoveEffect)
	{
		ZWorldItem* pItem = iter->second;
		mDrawer.DrawEffect(WORLD_ITEM_EFFECT_REMOVE, pItem->GetPosition());
	}

	SAFE_DELETE( iter->second );
	mItemList.erase( iter );
}

void ZWorldItemManager::Draw(int mode,float height,bool bWaterMap)//�ӽ�..
{
	ZWorldItem* pWorldItem	= 0;

	RSetWBuffer( TRUE );
	RGetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	float _h = 0.f;

	for( WIL_Iterator iter = mItemList.begin(); iter != mItemList.end(); ++iter )
	{
		pWorldItem	= iter->second;
		if( pWorldItem->GetState() == WORLD_ITEM_VALIDATE )
		{
			_h = pWorldItem->GetPosition().z;

			bool bDraw = false;

			if(mode==0) {			// �����׸���

				if( bWaterMap ) {
					if( _h <= height)	// ����
						bDraw = true;
				}
				else {
					bDraw = false;
				}

				if( pWorldItem->GetType()==WIT_QUEST ) 
					bDraw = true;
				
			} else if(mode==1) {	// ���߱׸���

				if( bWaterMap )  {
					if(bWaterMap && _h > height)	// ����
						bDraw = true;
				}
				else {
					bDraw = true;
				}

				if( pWorldItem->GetType()==WIT_QUEST )
					bDraw = false;
			}

			if(bDraw)
				mDrawer.DrawWorldItem( pWorldItem );
		}
	}
}

void ZWorldItemManager::Draw()
{
	ZWorldItem* pWorldItem	= 0;

	RSetWBuffer( TRUE );
	RGetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	for( WIL_Iterator iter = mItemList.begin(); iter != mItemList.end(); ++iter )
	{
		pWorldItem	= iter->second;
		if( pWorldItem->GetState() == WORLD_ITEM_VALIDATE )
			mDrawer.DrawWorldItem( pWorldItem );
	}
}

bool ZWorldItemManager::SpawnWorldItem( WIL_Iterator& iter )
{
	ZWorldItem* pItem = iter->second;
	pItem->SetState( WORLD_ITEM_VALIDATE );

	if (pItem->GetItemID() < USER_WORLDITEM_FIRST)
		mDrawer.DrawEffect(WORLD_ITEM_EFFECT_CREATE, pItem->GetPosition());

	return true;
}

void ZWorldItemManager::Reset(bool bDrawRemoveEffect)
{
	for( WIL_Iterator iter = mItemList.begin(); iter != mItemList.end(); ++iter)
	{
		ZWorldItem* pItem = iter->second;

		if (bDrawRemoveEffect)
		{
			if ((pItem->GetType() != WIT_CLIENT) && (pItem->GetState() == WORLD_ITEM_VALIDATE))
				mDrawer.DrawEffect(WORLD_ITEM_EFFECT_REMOVE, pItem->GetPosition());
		}

		SAFE_DELETE( pItem );
	}

	mItemList.clear();
}

void ZWorldItemManager::AddQuestPortal(rvector& pos)
{
	int id = GenStandAlondID();
	AddWorldItem(id, WORLDITEM_PORTAL_ID,MTD_Static, pos);

	ZGetSoundEngine()->PlaySound("fx_openportal",pos);
}

//////////////////////////////////////////////////////////////////////////
//		ZWorldItemDrawer
//////////////////////////////////////////////////////////////////////////
RVisualMesh* ZWorldItemDrawer::AddMesh( const char* pName )
{
	_ASSERT( pName );
	RMesh* pMesh	= ZGetMeshMgr()->Get( (char*)pName );
	RVisualMesh* pVMesh = new RVisualMesh;
	pVMesh->Create( pMesh );
 	pVMesh->SetAnimation("play");
	pVMesh->SetCheckViewFrustum(true);
	mVMeshList.insert( WorldItemVMeshMap::value_type( string(pName), pVMesh ));
	return pVMesh;
}

void ZWorldItemDrawer::DrawWorldItem( ZWorldItem* pWorldItem, bool Rotate )
{
	_ASSERT( pWorldItem != 0 );

	if( pWorldItem->m_bisDraw==false )
		return; //weapon ���� �׷��ִ� ���� ���..

	WIVMM_iterator iter = mVMeshList.find( string( pWorldItem->GetModelName()) );
	RVisualMesh* pVMesh = 0;

	if(pWorldItem->m_pVMesh) {// �ڽŸ��� visual mesh �� ����Ѵٸ�~
		pVMesh = pWorldItem->m_pVMesh;

		if(pWorldItem->GetType()==WIT_QUEST)
			if( pVMesh->isOncePlayDone() )
				pVMesh->SetAnimation("playloop");
	}
	else {

		if( iter == mVMeshList.end() ) 
			pVMesh = AddMesh( pWorldItem->GetModelName() );
		else
			pVMesh = iter->second;
	}
	
	rmatrix world;
	rvector pos = pWorldItem->GetPosition();
	rvector dir = pWorldItem->GetDir();
	rvector up  = pWorldItem->GetUp();

//	MakeWorldMatrix( &world, pos, rvector(0,1,0), rvector(0,0,1) );
	MakeWorldMatrix( &world, pos, dir , up );

	float fVis = 1.f;

	DWORD thistime = GetGlobalTimeMS();

	if( (pWorldItem->GetType()!=WIT_CLIENT)
		&& (pWorldItem->GetSubType() != MTD_Static) )
	{
		if( thistime > pWorldItem->m_dwStartTime + 6000) // 6�� ����
		{
			if(pWorldItem->m_dwToggleBackupTime < thistime  ) {
				pWorldItem->m_bToggle = !pWorldItem->m_bToggle;
				pWorldItem->m_dwToggleBackupTime = thistime + 100;
			} 
			
			float fAspect = ( pWorldItem->m_dwToggleBackupTime - thistime ) / 100.f;

			fAspect = max(min(fAspect,1.f),0.5f); // 0.3f ~ 1.f

			if(pWorldItem->m_bToggle) {
				fVis = fAspect;
			}
			else {
				fVis = 1.5f - fAspect;
			}
		}
	}

	pVMesh->SetVisibility(fVis);

	pVMesh->SetWorldMatrix( world );
	pVMesh->Frame();
	pVMesh->Render();

	if(pVMesh->m_bIsRender==false)
		return;

	if (pWorldItem->GetItemID() < USER_WORLDITEM_FIRST) 
		if(pWorldItem->GetType()!=WIT_QUEST)
			DrawEffect( WORLD_ITEM_EFFECT_IDLE, pos );
}

void ZWorldItemDrawer::DrawEffect( ZWORLD_ITEM_EFFECT effect, const rvector& pos )
{
	RVisualMesh* pVMesh = 0;
	switch( effect ) 
	{
	case WORLD_ITEM_EFFECT_CREATE:
		ZGetEffectManager()->AddWorldItemEatenEffect( pos );
		break;
	case WORLD_ITEM_EFFECT_REMOVE:
		ZGetEffectManager()->AddWorldItemEatenEffect( pos );
		break;
	case WORLD_ITEM_EFFECT_IDLE:
		{
		WIVMM_iterator iter = mVMeshList.find( string(BASE_EFFECT_MODEL) );
		if( iter == mVMeshList.end() )
			pVMesh = AddMesh( BASE_EFFECT_MODEL );
		else
			pVMesh = iter->second;
		if( pVMesh != 0 )
		{
			rmatrix world;
			MakeWorldMatrix( &world, pos, rvector(0,1,0), rvector(0,0,1) );

			pVMesh->SetWorldMatrix( world );
			pVMesh->Frame();
			pVMesh->Render();
		}			
		}
		break;

	}
}

ZWorldItemDrawer::~ZWorldItemDrawer()
{
	Clear();
}

void ZWorldItemDrawer::Clear()
{
	for( WIVMM_iterator iter = mVMeshList.begin(); iter != mVMeshList.end(); )
	{
		RVisualMesh* pVMesh = iter->second;
		SAFE_DELETE( pVMesh );
		iter	= mVMeshList.erase( iter );
	}
}



//////////////////////////////////////////////////////////////////////////
//		Global Method
//////////////////////////////////////////////////////////////////////////
ZWorldItemManager* ZGetWorldItemManager()
{
	return ZWorldItemManager::GetInstance();
}


int ZWorldItemManager::GetLinkedWorldItemID(MMatchItemDesc* pItemDesc)
{
	for (map<short, MMatchWorldItemDesc*>::iterator itor = MGetMatchWorldItemDescMgr()->begin();
		itor != MGetMatchWorldItemDescMgr()->end(); ++itor)
	{
		MMatchWorldItemDesc* pWorldItemDesc = itor->second;

		// worlditem.xml�� ���̸��� zitem.xml�� �޽��̸��� ���ƾ߸� �ȴ�.
		if(strcmp(pItemDesc->m_szMeshName, pWorldItemDesc->m_szModelName)==0)
		{
			return pWorldItemDesc->m_nID;
		}
	}

	_ASSERT(0);	// �´� ����������� ����.
	return 0;

}