#include "pch.h"
#include "MainProc.h"

extern HINSTANCE hInst;

SYSTEMTIME gST;
HFONT ghFont;

//WM_CREATE 실행 함수 //윈도우가 만들어질 때 한 번만 호출
int OnCreate(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    ghFont = CreateFontW(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"궁서체");
    SetTimer(hWnd, 0, 1000, NULL); //시간 설정 ID(0번), 1000(1초)
    //내가 원하는 메시지를 윈도우에게 부탁하는 방식
    SendMessage(hWnd, WM_TIMER, NULL, NULL);
    //OnTimer(hWnd, NULL, NULL); //안 좋은 방식
    return 0;
}

//WM_TIMER 실행 함수 //윈도우 종료 전까지 정해진 시간마다 반복 호출 
int OnTimer(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    GetLocalTime(&gST);//SYSTEMTIME구조체 변수 값 저장하기

    TCHAR strTime[128]; //문자열 //시간
    wsprintf(strTime, L"%d시 %d분 %d초", //문자열에 시간 저장
        gST.wHour, gST.wMinute, gST.wSecond);
    SetWindowText(hWnd, strTime);
    InvalidateRect(hWnd, NULL, TRUE); //무효화선언하여 WM_PAINT호출
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
    SelectObject(hdc, ghFont);
    gdiPrintNumbers(hdc, 0, 0, gST.wHour);
    gdiPrintNumbers(hdc, 300, 0, gST.wMinute);
    gdiPrintNumbers(hdc, 600, 0, gST.wSecond);

    EndPaint(hWnd, &ps);
    return 0;
}

int OnDestroy(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    KillTimer(hWnd, 0);
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
