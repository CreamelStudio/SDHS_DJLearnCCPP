#include "pch.h"
#include "MainProc.h"

extern BaseWindow* System;
extern bool bIsGameActive;
extern HDC ScreenDC;  //주버퍼
extern HDC MemoryDC;  //보조버퍼
extern HBITMAP MemoryBM;
extern RECT rtScreen;

int OnCreate(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    bIsGameActive = true; //게임루프 활성화

    GetClientRect(hWnd, &rtScreen);
    ScreenDC = GetDC(hWnd);
    MemoryDC = CreateCompatibleDC(ScreenDC);
    MemoryBM = CreateCompatibleBitmap(ScreenDC, rtScreen.right, rtScreen.bottom);
    SelectObject(MemoryDC, MemoryBM);
    
    return 0;
}

int OnReSize(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    GetClientRect(hWnd, &rtScreen);
    InvalidateRect(hWnd, NULL, TRUE);
    ScreenDC = GetDC(hWnd);
    MemoryDC = CreateCompatibleDC(ScreenDC);
    MemoryBM = CreateCompatibleBitmap(ScreenDC, rtScreen.right, rtScreen.bottom);
    SelectObject(MemoryDC, MemoryBM);
    return 0;
}

int OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    int wmId = LOWORD(wParam);
    // 메뉴 선택을 구문 분석합니다:
    switch (wmId)
    {
    case IDM_ABOUT:
        DialogBox(System->GetInst(), MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
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
    case WM_COMMAND:    return OnCommand(hWnd, wParam, lParam);
    case WM_SIZE:       return OnReSize(hWnd, wParam, lParam);
    case WM_PAINT:      return OnPaint(hWnd, wParam, lParam);
    case WM_DESTROY:    return OnDestroy(hWnd, wParam, lParam);
    default:            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}