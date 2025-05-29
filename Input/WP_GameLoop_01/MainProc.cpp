#include "pch.h"
#include "MainProc.h"

extern HINSTANCE hInst;
extern INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
extern BOOL bIsActive;
extern HDC ghdc;

extern BOOL bIsLoopExit;

extern int nFPS;
extern int nCount;

int OnCreate(HWND hWnd, WPARAM wParam, LPARAM lParam) {
    Start();
    bIsLoopExit = TRUE;
    SetTimer(hWnd, 0, 1000, NULL);
    ghdc = GetDC(hWnd);
    bIsActive = TRUE;
    return 0;
}
int OnDestroy(HWND hWnd, WPARAM wParam, LPARAM lParam) {
    bIsLoopExit = FALSE;
    ReleaseDC(hWnd, ghdc);
    KillTimer(hWnd, 0);
    PostQuitMessage(0);

    return 0;
}
/*int OnPaint(HWND hWnd, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);
    // TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...
    EndPaint(hWnd, &ps);

    return 0;
}*/

int OnTimer() {
    nFPS = nCount;
    nCount = 0;
    return 0;
}

int OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam) {
    int wmId = LOWORD(wParam);
        // �޴� ������ ���� �м��մϴ�:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, WM_COMMAND, wParam, lParam);
        }

    return 0;
}


//
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  �뵵: �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���ø����̼� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_CREATE: return OnCreate(hWnd, wParam, lParam);
        case WM_COMMAND: return OnCommand(hWnd, wParam, lParam);
        case WM_TIMER: return OnTimer();
        //case WM_PAINT: return OnPaint(hWnd, wParam, lParam);
        case WM_DESTROY: return OnDestroy(hWnd, wParam, lParam);
        default: return DefWindowProc(hWnd, message, wParam, lParam);
                                  
    }
    return 0;
}
