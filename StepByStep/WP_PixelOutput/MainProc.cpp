#include "pch.h"
#include "MainProc.h"

extern INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
extern HINSTANCE hInst;
void MyPixel(HDC hdc, int x, int y, int width, int height, COLORREF rgb);
void HLine(HDC hdc, int x1, int x2, int y, COLORREF rgb);
void VLine(HDC hdc, int x1, int x2, int y, COLORREF rgb);
void NeMo(HDC hdc, int x1, int x2, int y1, int y2, COLORREF rgb);

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
    for (int i = 0;i < 100;i++) {
        MyPixel(hdc, 100 + i * 5, 100, 5, 5, RGB(255, 0, 0));
        MyPixel(hdc, 100 + i * 5, 105, 5, 5, RGB(0, 255, 0));
        MyPixel(hdc, 100 + i * 5, 110, 5, 5, RGB(0, 0, 255));
    }
    
    MyPixel(hdc, 100, 150 + 50, 50, 5, RGB(0,0,0));
    MyPixel(hdc, 150, 100 + 50, 5, 50, RGB(0, 0, 0));
    MyPixel(hdc, 100, 100 + 50, 5, 50, RGB(0, 0, 0));
    MyPixel(hdc, 100, 100 + 50, 50, 5, RGB(0, 0, 0));

    NeMo(hdc, 200, 200, 250, 250, RGB(50,50,50));

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

void MyPixel(HDC hdc, int x, int y, int width, int height, COLORREF rgb) {
    for (int i = 0;i < height;i++) {
        for (int j = 0;j < width;j++) {
            SetPixel(hdc, j + x, i + y, rgb);
        }
    }
}

void HLine(HDC hdc, int x1, int x2, int y, COLORREF rgb) {
    MyPixel(hdc, x1, y, x2 - x1, 5, RGB(0,0,0));
}

void VLine(HDC hdc, int x, int y1, int y2, COLORREF rgb) {
    MyPixel(hdc, x, y1, 5, y2 - y1, RGB(0, 0, 0));
}

void NeMo(HDC hdc, int x1, int x2, int y1, int y2, COLORREF rgb) {
    HLine(hdc, x1, x2, y1, rgb);
    HLine(hdc, x1, x2, y2, rgb);

    VLine(hdc, x1, x2, y1, rgb);
    VLine(hdc, x1, x2, y2, rgb);

}