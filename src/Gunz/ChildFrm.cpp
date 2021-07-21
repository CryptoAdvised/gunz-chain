// ChildFrm.cpp : CChildFrame Ŭ������ ����
//
#include "stdafx.h"
#ifdef MFC
#include "MatchServer.h"

#include "ChildFrm.h"
#include "OutputView.h"
#include "MatchServerView.h"
#include ".\childfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
END_MESSAGE_MAP()


// CChildFrame ����/�Ҹ�

CChildFrame::CChildFrame()
{
	// TODO: ���⿡ ��� �ʱ�ȭ �ڵ带 �߰��մϴ�.
}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡�� Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.
	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}


// CChildFrame ����

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG


// CChildFrame �޽��� ó����

void CChildFrame::OnUpdateFrameTitle(BOOL bAddToTitle)
{
	//CMDIChildWnd::OnUpdateFrameTitle(TRUE);
	CMDIChildWnd::OnUpdateFrameTitle(bAddToTitle);
	//CMDIChildWnd::OnUpdateFrameTitle(FALSE);
	CView* pView = GetActiveView();
	if(pView!=NULL){
		if(pView->IsKindOf(RUNTIME_CLASS(COutputView))) SetWindowText("Output");
		else if(pView->IsKindOf(RUNTIME_CLASS(CMatchServerView))) SetWindowText("MatchServerView");
	}

}
#endif