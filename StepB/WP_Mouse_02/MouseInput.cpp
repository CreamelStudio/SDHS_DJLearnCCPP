#include "pch.h"
#include "MouseInput.h"

extern MouseMSG mouseState;
extern TCHAR strWheelValue[128];

int OnMouseWheel(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    int zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
    wsprintf(strWheelValue, L"ÈÙ È¸Àü°ª : %03d", zDelta);
    InvalidateRect(hWnd, NULL, TRUE);
    return 0;
}

int OnMouseLBUTTONDBLCLK(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    mouseState = LDBLK;
    InvalidateRect(hWnd, NULL, TRUE);
    return 0;
}

int OnMouseRBUTTONDBLCLK(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    mouseState = RDBLK;
    InvalidateRect(hWnd, NULL, TRUE);
    return 0;
}

int OnMouseMBUTTONDBLCLK(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    mouseState = MDBLK;
    InvalidateRect(hWnd, NULL, TRUE);
    return 0;
}

int OnMouseLBUTTONDOWN(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    mouseState = LBD;
    InvalidateRect(hWnd, NULL, TRUE);
    return 0;
}

int OnMouseLBUTTONUP(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    mouseState = MouseMSG::LBU;
    InvalidateRect(hWnd, NULL, TRUE);
    return 0;
}

int OnMouseRBUTTONDOWN(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    mouseState = MouseMSG::RBD;
    InvalidateRect(hWnd, NULL, TRUE);
    return 0;
}

int OnMouseRBUTTONUP(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    mouseState = MouseMSG::RBU;
    InvalidateRect(hWnd, NULL, TRUE);
    return 0;
}

int OnMouseMBUTTONDOWN(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    mouseState = MouseMSG::MBD;
    InvalidateRect(hWnd, NULL, TRUE);
    return 0;
}

int OnMouseMBUTTONUP(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    mouseState = MouseMSG::MBU;
    InvalidateRect(hWnd, NULL, TRUE);
    return 0;
}