#include "pch.h"
#include "MsgLoop.h"

extern HINSTANCE hInstance;
extern BOOL bIsActive;
extern BOOL bIsLoopExit;

int WndMsgLoop(HINSTANCE hInstance) {
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WPGAMELOOP01));
    
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

int GameMsgLoop(HINSTANCE hInstance) {
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WPGAMELOOP01));
    MSG msg;

    // 게임 메시지 루프입니다:
    while (bIsLoopExit)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_NOREMOVE)) {
            if (GetMessage(&msg, nullptr, 0, 0))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            else return (int)msg.wParam;
        }
        else if (bIsActive) {
            Update();
        }
        else WaitMessage();
    }
    return (int)msg.wParam;
}