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
            BitBlt(MemoryDC, 
                rtScreen.left, rtScreen.top, 
                rtScreen.right, rtScreen.bottom,
                NULL, 0, 0, BLACKNESS);
            gdi->StartDraw(MemoryDC);


            gdi->DkGreenPen();

            for (int i = ((rtScreen.right / 50) / -2) - 1; i < ((rtScreen.right / 50) / 2) + 1; i++) {
				gdi->LineFloat(rtScreen.right / 2 + i * 50, rtScreen.top, rtScreen.right / 2 + i * 50, rtScreen.bottom);
            }

            for (int i = ((rtScreen.bottom / 50) / -2) - 1; i < ((rtScreen.bottom / 50) / 2) + 1; i++) {
				gdi->LineFloat(rtScreen.left, rtScreen.bottom / 2 + i * 50, rtScreen.right, rtScreen.bottom / 2 + i * 50);
            }

            gdi->YellowPen();
            gdi->LineFloat(rtScreen.right / 2, rtScreen.top, rtScreen.right / 2, rtScreen.bottom);
            gdi->LineFloat(rtScreen.left, rtScreen.bottom / 2, rtScreen.right, rtScreen.bottom / 2);

            
            gdi->StopDraw(MemoryDC);
            BitBlt(ScreenDC,
                rtScreen.left, rtScreen.top,
                rtScreen.right, rtScreen.bottom,
                MemoryDC, 0, 0, SRCCOPY);
        }
        else WaitMessage();
    }

    return (int)msg.wParam;
}