#include "pch.h"
#include "MainProc.h"

extern HINSTANCE hInst;

SYSTEMTIME gST;

int OnCreate(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    SetTimer(hWnd, 0, 1000, NULL);
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
    HDC hdc = BeginPaint(hWnd, &ps);
    // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
    int SecNeddleLength = 160;
    int SecNeddleX = 0; //초바늘 끝점
    int SecNeddleY = 0; //초바늘 끝점
    int SecCenterX = 500; //초바늘 시작점
    int SecCenterY = 250; //초바늘 시작점

    Ellipse(hdc, -230 + SecCenterX, -230 + SecCenterY, 230 + SecCenterX, 230 + SecCenterY);

    float theta = RAD((float)((gST.wSecond - 22.5) * 6.0f));
    // 원 둘레의 좌표를 추출하는 공식
    // //원래공식
    //  x =  cos() * len + sin() * len
    //  y = -sin() * len + cos() * len
    // //변경 시계방향 CW
    //  x = cos() * len - sin() * len
    //  y = cos() * len + sin() * len
    SecNeddleX = cos(theta) * SecNeddleLength - sin(theta) * SecNeddleLength;
    SecNeddleY = cos(theta) * SecNeddleLength + sin(theta) * SecNeddleLength;
    gdiLine(hdc, SecCenterX, SecCenterY, SecNeddleX + SecCenterX, SecNeddleY + SecCenterY);
    gdiStar(hdc, SecNeddleX + SecCenterX, SecNeddleY + SecCenterY);

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
