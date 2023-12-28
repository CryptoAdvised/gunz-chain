#include "StdAfx.h"

bool IsAddressHooked(unsigned long address)
{
    BYTE* offsetValue = (BYTE*)address;
    return (*offsetValue == 0xE8 || *offsetValue == 0xE9 || *offsetValue == 0x7E || *offsetValue == 0x74 || *offsetValue == 0xFF);
}

void AntiClocking()
{
    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_LOWEST);
    SetThreadPriority(GetCurrentThread(), THREAD_MODE_BACKGROUND_BEGIN);
    DWORD getTickCount = (DWORD)GetProcAddress(GetModuleHandleA("kernel32.dll"), "GetTickCount");
    DWORD queryPerformanceCounter = (DWORD)GetProcAddress(GetModuleHandleA("kernel32.dll"), "QueryPerformanceCounter");

    while(true)
    {
        if (IsAddressHooked(getTickCount) || IsAddressHooked(queryPerformanceCounter) || GetModuleHandleA ("SpeedHack.dll") != NULL || GetModuleHandleA ("MyHookDll.dll") != NULL)
        {
            MessageBox(g_hWnd,"Clocking modifier detected!",  NULL, MB_OK);
            exit(0); 
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    }
}