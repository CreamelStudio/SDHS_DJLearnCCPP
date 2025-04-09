#include "pch.h"
#include "MainProc.h"

extern HINSTANCE hInst;
extern INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int OnCommand(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    int wmId = LOWORD(wParam);
    // Parse the menu selections:
    switch (wmId)
    {
    case IDM_ABOUT:
        DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
        break;
    case IDM_EXIT:

        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

int OnPaint(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);

    TextOut(hdc, 100, 30, L"서울디지텍고등학교", 9);
    TextOut(hdc, 100, 50, L"게임 프로그래밍 전공", 11);
    TextOut(hdc, 100, 70, L"2학년 0반 김 대 진", 12);

    EndPaint(hWnd, &ps);

    return 0;
}

int OnDestroy(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    DestroyWindow(hWnd);

    return 0;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        return OnCommand(hWnd, message, wParam, lParam);
    }
    break;
    case WM_PAINT:
    {
        return OnPaint(hWnd, message, wParam, lParam);
    }
    break;
    case WM_DESTROY:
        return OnDestroy(hWnd, message, wParam, lParam);
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}