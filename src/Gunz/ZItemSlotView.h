#ifndef ZITEMSLOTVIEW_H
#define ZITEMSLOTVIEW_H

#include "ZPrerequisites.h"
#include "MWidget.h"
#include "RMesh.h"
#include "RVisualMeshMgr.h"
#include "ZMeshView.h"
#include "MButton.h"
#include "MMatchItem.h"

using namespace RealSpace2;


class ZItemSlotView : public MButton{
protected:
	MBitmap*				m_pBackBitmap;
	MMatchCharItemParts		m_nParts;

	bool					m_bSelectBox;			// ����Ʈ �ڽ� ��� ����
	bool					m_bDragAndDrop;			// �巡�� �� ��� ���� ����
	bool					m_bKindable;

	virtual void OnDraw(MDrawContext* pDC);
	virtual bool IsDropable(MWidget* pSender);
	virtual bool OnDrop(MWidget* pSender, MBitmap* pBitmap, const char* szString, const char* szItemString);

	void SetDefaultText(MMatchCharItemParts nParts);
	virtual bool OnEvent(MEvent* pEvent, MListener* pListener);
	bool IsEquipableItem(u32 nItemID, int nPlayerLevel, MMatchSex nPlayerSex);
public:
	char					m_szItemSlotPlace[128];

	ZItemSlotView(const char* szName=NULL, MWidget* pParent=NULL, MListener* pListener=NULL);
	virtual ~ZItemSlotView(void);
	MMatchCharItemParts GetParts() { return m_nParts; }
	void SetParts(MMatchCharItemParts nParts);

	void SetBackBitmap(MBitmap* pBitmap);
	void SetIConBitmap(MBitmap* pBitmap);

	void EnableDragAndDrop( bool bEnable);

	void SetKindable( bool bKindable);


#define MINT_ITEMSLOTVIEW	"ItemSlotView"
	virtual const char* GetClassName(void){ return MINT_ITEMSLOTVIEW; }

};



#endif