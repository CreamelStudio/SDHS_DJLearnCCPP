#include "pch.h"
#include "MainProc.h"

extern HINSTANCE hInst;
static int length = 0;
TCHAR strBuffer[128];
POINT ptPos;

int OnCreate(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    return 0;
}

int OnChar(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    strBuffer[length] = (TCHAR)wParam;
    strBuffer[length + 1] = NULL;
    length++;
    InvalidateRect(hWnd, NULL, TRUE);
    return 0;
}   

int OnKeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    switch (wParam)
    {
    case 'w':   case 'W':   case VK_UP:     ptPos.y -= 5;   break;
    case 's':   case 'S':   case VK_DOWN:   ptPos.y += 5;   break;
    case 'a':   case 'A':   case VK_LEFT:   ptPos.x -= 5;   break;
    case 'd':   case 'D':   case VK_RIGHT:  ptPos.x += 5;   break;
    }
    InvalidateRect(hWnd, NULL, TRUE);
    return 0;
}

int OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
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

int OnPaint(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);
    // TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...
    TextOut(hdc, 100 + ptPos.x, 100 + ptPos.y, strBuffer, wcslen(strBuffer));
    EndPaint(hWnd, &ps);
    return 0;
}

int OnDestroy(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    PostQuitMessage(0);
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
    case WM_CREATE:     return OnCreate(hWnd, wParam, lParam);
    case WM_CHAR:       return OnChar(hWnd, wParam, lParam);
    case WM_KEYDOWN:    return OnKeyDown(hWnd, wParam, lParam);
    case WM_COMMAND:    return OnCommand(hWnd, wParam, lParam);
    case WM_PAINT:      return OnPaint(hWnd, wParam, lParam);
    case WM_DESTROY:    return OnDestroy(hWnd, wParam, lParam);
    default:            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}