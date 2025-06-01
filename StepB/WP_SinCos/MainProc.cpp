#include "pch.h"
#include "MainProc.h"

extern HINSTANCE hInst;


RECT       grtWndClient;
SYSTEMTIME gST;

HPEN hOldPen;
HPEN hRedPen;
HPEN hGreenPen;
HPEN hBluePen;
HPEN hYellowPen;
HPEN hBlackPen;
HPEN hWhitePen;

HBRUSH hOldBrush;
HBRUSH hRedBrush;
HBRUSH hGreenBrush;
HBRUSH hBlueBrush;
HBRUSH hYellowBrush;
HBRUSH hBlackBrush;
HBRUSH hWhiteBrush;

int OnCreate(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    GetClientRect(hWnd, &grtWndClient);
    SetTimer(hWnd, 0, 1000/33, NULL);
    hRedPen =   CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
    hGreenPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
    hBluePen =  CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
    hYellowPen =CreatePen(PS_SOLID, 1, RGB(255, 255, 0));
    hBlackPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    hWhitePen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));

    hRedBrush       = CreateSolidBrush(RGB(255, 0, 0));
    hGreenBrush     = CreateSolidBrush(RGB(0, 255, 0));
    hBlueBrush      = CreateSolidBrush(RGB(0, 0, 255));
    hYellowBrush    = CreateSolidBrush(RGB(255, 255, 0));
    hBlackBrush     = CreateSolidBrush(RGB(0, 0, 0));
    hWhiteBrush     = CreateSolidBrush(RGB(255, 255, 255));
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

#define PI 3.141592f
#define RAD(x) PI/180.0f*(x)

int OnPaint(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    static int degRun = 0;

    HDC hdc = BeginPaint(hWnd, &ps);
    // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
    //int sysSX = grtWndClient.left + 1;
    //int sysSY = grtWndClient.top + 1;
    //int sysEX = grtWndClient.right - 1;
    //int sysEY = grtWndClient.bottom -1;
    //int sysCW = (sysEX - sysSX) / 2;
    //int sysCH = (sysEY - sysSY) / 2;

    //int startX = 500;

    //Rectangle(hdc, sysSX, sysSY, sysEX, sysEY);
    //gdiLine(hdc, startX, sysSY, startX, sysEY); //x좌표가 같음 (수직선)
    //gdiLine(hdc, sysSX, sysCH, sysEX, sysCH); //y좌표가 같음(수평선)
    //
    //gdiLine(hdc, startX / 2, sysSY, startX / 2, sysEY);
    //gdiLine(hdc, sysSX, sysCH - 250, sysEX, sysCH - 250);
    //gdiLine(hdc, sysSX, sysCH + 250, sysEX, sysCH + 250);

    //int x, y;

    //for (int i = 0; i < 360; i++)
    //{
    //    x = i * 2.0f;
    //    y = -sin((float)RAD(i)) * 250;
    //    SetPixel(hdc, x + startX, y + sysCH, RGB(255, 0, 0));
    //}
    //for (int i = 0; i < 360; i++)
    //{
    //    x = i * 2.0f;
    //    y = -cos((float)RAD(i)) * 250;
    //    SetPixel(hdc, x + startX, y + sysCH, RGB(0, 0, 255));
    //}

    //for (int i = 0; i < 360; i++)
    //{
    //    x = i * 2.0f;
    //    y = -tan((float)RAD(i)) * 250;
    //    if(abs(y) < 250) SetPixel(hdc, x + startX, y + sysCH, RGB(0, 0, 0));
    //}

    //for (int i = 0; i < 360; i++)
    //{
    //    x = cos((float)RAD(i)) * 250;
    //    y = -sin((float)RAD(i)) * 250;
    //    SetPixel(hdc, x + startX / 2, y + sysCH, RGB(0, 0, 0));
    //}

    //(degRun>=360) ? degRun = 0 : degRun++;
    //x = cos((float)RAD(degRun)) * 250;
    //y = -sin((float)RAD(degRun)) * 250;
    //gdiStar(hdc, x + startX / 2, y + sysCH);
    //x = degRun * 2.0f;
    //y = -sin((float)RAD(degRun)) * 250;
    //gdiStar(hdc, x + startX, y + sysCH);
    //x = degRun * 2.0f;
    //y = -cos((float)RAD(degRun)) * 250;
    //gdiStar(hdc, x + startX, y + sysCH);
    //x = degRun * 2.0f;
    //y = -tan((float)RAD(degRun)) * 250;
    //if (abs(y) < 250) gdiStar(hdc, x + startX, y + sysCH);

    hOldPen = (HPEN)SelectObject(hdc, hRedPen);
    hOldBrush = (HBRUSH)SelectObject(hdc, hGreenBrush);
    Rectangle(hdc, 100, 100, 400, 400);
    SelectObject(hdc, hYellowBrush);
    SelectObject(hdc, hBlackPen);
    Ellipse(hdc, 100, 100, 400, 400);
    gdiLine(hdc, 100, 100, 400, 400);
    SelectObject(hdc, hBluePen);
    gdiLine(hdc, 100, 400, 400, 100);

    SelectObject(hdc, hOldBrush);
    SelectObject(hdc, hOldPen);
    EndPaint(hWnd, &ps);
    return 0;
}

int OnDestroy(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    DeleteObject(hWhiteBrush);
    DeleteObject(hBlackBrush);
    DeleteObject(hYellowBrush);
    DeleteObject(hBlueBrush);
    DeleteObject(hGreenBrush);
    DeleteObject(hRedBrush);

    DeleteObject(hWhitePen);
    DeleteObject(hBlackPen);
    DeleteObject(hYellowPen);
    DeleteObject(hBluePen);
    DeleteObject(hGreenPen);
    DeleteObject(hRedPen);

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
