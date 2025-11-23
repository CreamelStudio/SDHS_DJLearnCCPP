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
            
            VERTEX v1 = { 0, 0, 1 };
            VERTEX sv1;  //최종화면 출력좌표
            Matrix2D mat;
            mat.Identity();
            mat.Move(rtScreen.right / 2, rtScreen.bottom / 2);
            
            sv1 = Multiple(v1, mat);
            DrawBigBigDot(sv1.x, sv1.y, RGB(200, 200, 0));

            gdi->GrayPen();
            gdi->Line((int)(rtScreen.right / 2 + 0.5) + 0, 0, (int)(rtScreen.right / 2 + 0.5), (int)(rtScreen.bottom + 0.5));
            gdi->Line(0, (int)(rtScreen.bottom / 2 + 0.5),(int)(rtScreen.right + 0.5), (int)(rtScreen.bottom / 2 + 0.5));

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