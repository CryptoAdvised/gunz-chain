#include "StdAfx.h"



void AntiDebugger()
{

    while (true) {
        if (IsDebuggerPresent()) {
            MessageBox(g_hWnd,"Debugger detected!",  NULL, MB_OK);
            exit(0); 
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    return;
}
