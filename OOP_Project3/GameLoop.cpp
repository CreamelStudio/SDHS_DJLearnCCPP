#include "pch.h"
#include "GameLoop.h"

extern BaseWindow* System;
extern bool bIsGameActive;
extern HDC ScreenDC;  //주버퍼
extern HDC MemoryDC;  //보조버퍼
extern HBITMAP MemoryBM;
extern RECT rtScreen;

int BaseLoop()
{
    HACCEL hAccelTable = LoadAccelerators(System->GetInst(), MAKEINTRESOURCE(IDC_OOPPROJECT3));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}

int GameLoop()
{
    HACCEL hAccelTable = LoadAccelerators(System->GetInst(), MAKEINTRESOURCE(IDC_OOPPROJECT3));

    MSG msg;

    Initialize();
    while (1)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_NOREMOVE))
        {
            if (GetMessage(&msg, nullptr, 0, 0))
            {
                if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
                {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }
            }
            else
            {
                return (int)msg.wParam;
            }
        }
        else if (bIsGameActive)
        {
            
            Process();
            PreRender();
            Render();
            PostRender();
            
        }
        else WaitMessage();
    }
    Release();
    return (int)msg.wParam;
}