#include "pch.h"
#include "MouseInput.h"

extern MouseMSG mouseState;
extern TCHAR strWheelValue[128];

int OnMouseWheel(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    int zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
    wsprintf(strWheelValue, L"휠 회전값 : %3d", zDelta / WHEEL_DELTA);
    InvalidateRect(hWnd, NULL, TRUE);
    return 0;
}

int OnMouseLBTNDBLCLK(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    mouseState = LDBLK;
    InvalidateRect(hWnd, NULL, TRUE);
    return 0;
}

int OnMouseRBTNDBLCLK(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    mouseState = RDBLK;
    InvalidateRect(hWnd, NULL, TRUE);
    return 0;
}

int OnMouseMBTNDBLCLK(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    mouseState = MDBLK;
    InvalidateRect(hWnd, NULL, TRUE);
    return 0;
}

int OnMouseLBTNDN(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    mouseState = MouseMSG::LBD;
    InvalidateRect(hWnd, NULL, TRUE);
    return 0;
}

int OnMouseLBTNUP(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    mouseState = MouseMSG::LBU;
    InvalidateRect(hWnd, NULL, TRUE);
    return 0;
}

int OnMouseRBTNDN(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    mouseState = MouseMSG::RBD;
    InvalidateRect(hWnd, NULL, TRUE);
    return 0;
}

int OnMouseRBTNUP(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    mouseState = MouseMSG::RBU;
    InvalidateRect(hWnd, NULL, TRUE);
    return 0;
}

int OnMouseMBTNDN(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    mouseState = MouseMSG::MBD;
    InvalidateRect(hWnd, NULL, TRUE);
    return 0;
}

int OnMouseMBTNUP(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    mouseState = MouseMSG::MBU;
    InvalidateRect(hWnd, NULL, TRUE);
    return 0;
}

int OnMouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    TCHAR strTemp[128];
    int x = LOWORD(lParam);
    int y = HIWORD(lParam);
    wsprintf(strTemp, L"마우스 좌표[%04d,%04d]", x, y);
    SetWindowText(hWnd, strTemp);
    return 0;
}