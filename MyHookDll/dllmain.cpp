// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

HMODULE g_hModule = nullptr;
HHOOK g_hhk = nullptr;

LRESULT CALLBACK CallWndProc(
    _In_ int    nCode,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam
)
{
    auto lpcwp = (LPCWPSTRUCT)lParam;
    if (nCode == HC_ACTION && lpcwp->message == WM_COMMAND) {
        TCHAR szBuf[MAXBYTE]{};
        wsprintf(szBuf, TEXT("[hook] WM_COMMAND "));
        OutputDebugString(szBuf);
    }
    return ::CallNextHookEx(g_hhk, nCode, wParam, lParam);
}


void InstallHook(DWORD tid)
{
    g_hhk = ::SetWindowsHookEx(WH_CALLWNDPROC, CallWndProc, g_hModule, tid);
    return;
}

void UninstallHook(void)
{
    ::UnhookWindowsHookEx(g_hhk);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        g_hModule = hModule;
        MessageBox(NULL, NULL, NULL, NULL);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

