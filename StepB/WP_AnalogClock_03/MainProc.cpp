#include "pch.h"
#include "MainProc.h"

extern HINSTANCE hInst;

SYSTEMTIME gST;
MYCLOCK* g_pClock;

int OnCreate(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    SetTimer(hWnd, 0, 1000, NULL);
    g_pClock = StartMyClock(100, 100, 500, 500);
    return 0;
}

int OnTimer(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    GetLocalTime(&gST);
    InvalidateRect(hWnd, NULL, true);
    
    return 0;
}

int OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    int wmId = LOWORD(wParam);
    // 메뉴 선택을 구문 분석합니다:
    //SetBK(g_pClock, CBS_RECT | CBS_NUM1);
    static int clockStyle = NULL;
    static int hourPenThick = 5;

    static COLORREF myColor = RGB(0, 0, 0);

    CHOOSECOLOR cc;
    static COLORREF crTemp[16];
    ZeroMemory(&cc, sizeof(CHOOSECOLOR));
    cc.lStructSize = sizeof(CHOOSECOLOR);
    cc.hwndOwner == hWnd;
    cc.lpCustColors = crTemp;
    cc.Flags = CC_RGBINIT;

    switch (wmId)
    {
    case IDM_RECT:
        clockStyle += CBS_RECT;
        break;
    case IDM_CIRCLE:
        clockStyle += CBS_CIRCLE;
        break;
    case IDM_NUM1:
        clockStyle += CBS_NUM1;
        break;
    case IDM_NUM2:
        clockStyle += CBS_NUM2;
        break;
    case IDM_NUM3:
        clockStyle += CBS_NUM3;
        break;
    case IDM_HOURTHICK:
        if ((hourPenThick += 2) >= 30) hourPenThick = 5;
        g_pClock->pHour->color = (HPEN)CreatePen(PS_SOLID, hourPenThick, myColor);
        break;
    case IDM_HOURCOLOR:
        ChooseColor(&cc);
        myColor = cc.rgbResult;
        g_pClock->pHour->color = (HPEN)CreatePen(PS_SOLID, hourPenThick, myColor);
        break;
    case IDM_ABOUT:
        DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
        break;
    case IDM_EXIT:
        DestroyWindow(hWnd);
        break;
    default:
        return DefWindowProc(hWnd, WM_COMMAND, wParam, lParam);
    }
    SetBK(g_pClock, CBS_RECT | clockStyle);
    return 0;
}

#define PI 3.141592f
#define RAD(x) PI/180.0f*(x)

int OnPaint(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);
    // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
    SetHDC(g_pClock, hdc);
    
    Update(g_pClock);

    EndPaint(hWnd, &ps);
    return 0;
}

int OnDestroy(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    PostQuitMessage(0);
    return 0;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:     return OnCreate(hWnd, wParam, lParam);
    case WM_TIMER:      return OnTimer(hWnd, wParam, lParam);
    case WM_COMMAND:    return OnCommand(hWnd, wParam, lParam);
    case WM_PAINT:      return OnPaint(hWnd, wParam, lParam);
    case WM_DESTROY:    return OnDestroy(hWnd, wParam, lParam);
    default:            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
