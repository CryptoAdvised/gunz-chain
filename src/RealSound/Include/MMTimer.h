/*
	----------------
	Multimedia Timer
	----------------

	MMTimer.h

	"Multimedia Timer" handling class header file

	Programming by Chojoongpil
*/
#pragma once

#include "GlobalTypes.h"
#include "MUtil.h"

typedef bool (*MMTIMERCALLBACK)(uintptr_t);

// �ϳ��� Ŭ������ �Ѱ��� Ÿ�̸Ӹ� ���´�.
// �������� ������ �������� �����Ƿ� ������ ��.
class MMTimer
{
public:
    MMTimer();
    ~MMTimer();
	
	// Multimedia Timer�Ѱ��� �����Ѵ�.
    bool Create(u32 nPeriod, u32 nRes, u32 dwUser,  MMTIMERCALLBACK pfnCallback);
	void Destroy();

protected:
	static void STDCALL TimeProc(unsigned int uID, unsigned int uMsg,
		WIN_DWORD_PTR dwUser, WIN_DWORD_PTR dw1, WIN_DWORD_PTR dw2);

	// ���� Ÿ�̸Ӱ� �б��� �ݹ� �Լ�
    MMTIMERCALLBACK m_pfnCallback;

    u32 m_dwUser;
    u32 m_nPeriod;
    u32 m_nRes;
    u32 m_nIDTimer;
};
