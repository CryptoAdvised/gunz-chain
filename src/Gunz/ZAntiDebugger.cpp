#include "StdAfx.h"

bool IsDebuggerPresentTiming() {
    auto start = std::chrono::high_resolution_clock::now();
    Sleep(100); // Sleep for a short time
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> elapsed = end - start;
    return elapsed.count() > 500; // If time is significantly longer, debugger might be present
}

bool HasHardwareBreakpoints() {
    CONTEXT ctx = {0};
    ctx.ContextFlags = CONTEXT_DEBUG_REGISTERS;

    if (GetThreadContext(GetCurrentThread(), &ctx)) {
        if (ctx.Dr0 || ctx.Dr1 || ctx.Dr2 || ctx.Dr3) {
            return true;
        }
    }
    return false;
}

void AntiDebugger()
{

    while (true) {
        if (IsDebuggerPresentTiming() || HasHardwareBreakpoints()) {
            MessageBox(g_hWnd,"Debugger detected!",  NULL, MB_OK);
            exit(0); 
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    return;
}
