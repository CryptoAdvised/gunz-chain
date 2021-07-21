/*
	MMTimer.cpp
	-----------
	
	"Multimedia Timer" handling class implementation file
	
	Programming by Chojoongpil
	MAIET entertainment software
*/
#include "stdafx.h"
#include "MMTimer.h"

#ifdef WIN32

#include "MWindows.h"
#include <mmsystem.h>

////////////////////////////////////////
// Constructor & Destructor

MMTimer::MMTimer()
{	
    m_nIDTimer = NULL;
}

MMTimer::~MMTimer()
{
	Destroy();	// ������ Ÿ�̸Ӱ� �ִٸ� ���� �Ѵ�.
}

////////////////////////////////////////
// Member Function Implementation

void MMTimer::Destroy()
{
    if (m_nIDTimer){
        timeKillEvent (m_nIDTimer);
    }
}

// �ݹ��Լ��� ���� �����͸� �ξ���.
bool MMTimer::Create (u32 nPeriod, u32 nRes, u32 dwUser, MMTIMERCALLBACK pfnCallback)
{
    bool bRtn = true;
    
    _ASSERT(pfnCallback);
    _ASSERT(nPeriod > 10);
    _ASSERT(nPeriod >= nRes);

    m_nPeriod = nPeriod;
    m_nRes = nRes;
    m_dwUser = dwUser;
    m_pfnCallback = pfnCallback;

    if ((m_nIDTimer = timeSetEvent (m_nPeriod, m_nRes, TimeProc, (u32) this, TIME_PERIODIC)) == NULL){
        bRtn = FALSE;
    }

    return (bRtn);
}

// Multimedia Ÿ�̸� �޽����� ȣ��ɶ����� �� �ݹ� �Լ��� �Ҹ����.
void STDCALL MMTimer::TimeProc(unsigned int uID, unsigned int uMsg,
	WIN_DWORD_PTR dwUser, WIN_DWORD_PTR dw1, WIN_DWORD_PTR dw2)
{	    
	// �ݹ��Լ��� ���� �����͸� �ξ���.
	// Callback�Լ��� static�̹Ƿ� ���� ������Ʈ�� pointer�� ��� ������� ó���ȴ�.
    MMTimer * ptimer = (MMTimer *) dwUser;
	
	// ��¥ Callback�Լ��� ȣ��ȴ�.
	// �Լ��� MMTIMERCALLBACK�� ���� ������.
    (ptimer->m_pfnCallback) (ptimer->m_dwUser);
}

#endif