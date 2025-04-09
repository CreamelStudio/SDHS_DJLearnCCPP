#include "pch.h"
#include "MainProc.h"

extern INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
extern HINSTANCE hInst;

int OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam) {
    int wmId = LOWORD(wParam);
    // Parse the menu selections:
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

int OnPaint(HWND hWnd, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);

    //Draw the text
	TextOut(hdc, 100, 20, L"가나다라마바사", 8);
    TextOut(hdc, 100, 30, L"아자차카타파하", 8);
    TextOut(hdc, 100, 40, L"ABCDEFGHIJKMNOPQRSTUVWXYZ", 25);
    EndPaint(hWnd, &ps);

    return 0;
}

int OnDestroy(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	PostQuitMessage(0);
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
        case WM_COMMAND: return OnCommand(hWnd, wParam, lParam);
        break;
        case WM_PAINT: return OnPaint(hWnd, wParam, lParam);
        break;
        case WM_DESTROY: return OnDestroy(hWnd, wParam, lParam);
        default: return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}