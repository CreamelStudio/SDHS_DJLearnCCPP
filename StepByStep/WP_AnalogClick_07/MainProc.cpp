#include "pch.h"
#include "MainProc.h"

extern HINSTANCE hInst;
void gdiRotLineCW(HDC hdc, float x, float y, float lineLength, float theta);
SYSTEMTIME gST;

HPEN hOldPen;
HPEN hRedPen;
HPEN hGreenPen;
HPEN hBluePen;
HPEN hYellowPen;
HPEN hBlackPen;
HPEN hWhitePen;

HBRUSH    hOldBrush;
HBRUSH    hRedBrush;
HBRUSH  hGreenBrush;
HBRUSH   hBlueBrush;
HBRUSH hYellowBrush;
HBRUSH  hBlackBrush;
HBRUSH  hWhiteBrush;

int OnCreate(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    hRedPen =    CreatePen(PS_DOT, 1, RGB(255, 0, 0));
    hGreenPen =  CreatePen(PS_DOT, 1, RGB(0, 255, 0));
    hBluePen =   CreatePen(PS_DOT, 1, RGB(0, 0, 255));
    hYellowPen = CreatePen(PS_DOT, 1, RGB(255, 255, 0));
    hBlackPen =  CreatePen(PS_DOT, 1, RGB(0, 0, 0));
    hWhitePen =  CreatePen(PS_DOT, 1, RGB(255, 255, 255));

    hRedBrush =    CreateSolidBrush(RGB(255, 0, 0));
    hGreenBrush =  CreateSolidBrush(RGB(0, 255, 0));
    hBlueBrush =   CreateSolidBrush(RGB(0, 0, 255));
    hYellowBrush = CreateSolidBrush(RGB(255, 255, 0));
    hBlackBrush =  CreateSolidBrush(RGB(0, 0, 0));
    hWhiteBrush =  CreateSolidBrush(RGB(255, 255, 255));

    SetTimer(hWnd, 0, 1000, NULL);
    return 0;
}

int OnTimer(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    GetLocalTime(&gST);

    TCHAR strTime[128];
    wsprintf(strTime, L"%02d : %02d : %02d", gST.wHour, gST.wMinute, gST.wSecond);
    SetWindowTextW(hWnd, strTime);
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



int OnPaint(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);

    // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
    int SecNeddleLength = 140;
    int MinuteNeddleLength = 140;
    int HourNeddleLength = 70;

    int SecNeddleX = 0; //초바늘 끝점
    int SecNeddleY = 0; //초바늘 끝점
    int SecCenterX = 500; //초바늘 시작점
    int SecCenterY = 300; //초바늘 시작점

    Ellipse(hdc, -260 + SecCenterX, -260 + SecCenterY, 260 + SecCenterX, 260 + SecCenterY);
    Ellipse(hdc, -240 + SecCenterX, -240 + SecCenterY, 240 + SecCenterX, 240 + SecCenterY);
    

    float Sectheta = RAD((float)((gST.wSecond - 22.5) * 6.0f));
    gdiRotLineCW(hdc, 500, 300, 160, Sectheta);
    float Mintheta = RAD((float)((gST.wMinute - 22.5) * 6.0f));
    gdiRotLineCW(hdc, 500, 300, 160, Mintheta);
    float Hourtheta = RAD((float)((gST.wHour - 4.5) * 30.0f));
    gdiRotLineCW(hdc, 500, 300, 70, Hourtheta);


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

void gdiRotLineCW(HDC hdc, float x, float y, float lineLength, float theta) {
    float tempNeddleX = cos(theta) * lineLength - sin(theta) * lineLength;
    float tempNeddleY = cos(theta) * lineLength + sin(theta) * lineLength;
    gdiLine(hdc, x, y, tempNeddleX + x, tempNeddleY + y);
}

int OnDestroy(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
      DeleteObject(hBlackPen);
      DeleteObject(hWhitePen);
      DeleteObject(hYellowPen);
      DeleteObject(hBluePen);
      DeleteObject(hGreenPen);
      DeleteObject(hRedPen);

      DeleteObject(hBlackBrush);
      DeleteObject(hWhiteBrush);
      DeleteObject(hYellowBrush);
      DeleteObject(hBlueBrush);
      DeleteObject(hGreenBrush);
      DeleteObject(hRedBrush);

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
