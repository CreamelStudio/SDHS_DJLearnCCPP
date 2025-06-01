#include "pch.h"
#include "MainProc.h"

extern HINSTANCE hInst;
extern MouseMSG mouseState;
extern TCHAR strWheelValue[128];

enum MouseMSG {NONE, LBD, LBU, RBD, RBU, MBD, MBU, LDBLK, RDBLK, MDBLK};
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
    static MouseMSG mouseState = NONE;
    static TCHAR strWheelValue[128] = L"";
    switch (message)
    {
    case WM_MOUSEWHEEL:
    {
        int zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
        wsprintf(strWheelValue, L"�� ȸ���� : %03d", zDelta);
    }
    break;
    case WM_LBUTTONDBLCLK:
        mouseState = LDBLK;
        InvalidateRect(hWnd, NULL, TRUE);
        break;
    case WM_RBUTTONDBLCLK:
        mouseState = RDBLK;
        InvalidateRect(hWnd, NULL, TRUE);
        break;
    case WM_MBUTTONDBLCLK:
        mouseState = MDBLK;
        InvalidateRect(hWnd, NULL, TRUE);
        break;
    case WM_LBUTTONDOWN:
        mouseState = MouseMSG::LBD;
        InvalidateRect(hWnd, NULL, TRUE);
        break;
    case WM_LBUTTONUP:
        mouseState = MouseMSG::LBU;
        InvalidateRect(hWnd, NULL, TRUE);
        break;
    case WM_RBUTTONDOWN:
        mouseState = MouseMSG::RBD;
        InvalidateRect(hWnd, NULL, TRUE);
        break;
    case WM_RBUTTONUP:
        mouseState = MouseMSG::LBU;
        InvalidateRect(hWnd, NULL, TRUE);
        break;
    case WM_MBUTTONDOWN:
        mouseState = MouseMSG::MBD;
        InvalidateRect(hWnd, NULL, TRUE);
        break;
    case WM_MBUTTONUP:
        mouseState = MouseMSG::MBU;
        InvalidateRect(hWnd, NULL, TRUE);
        break;
    case WM_MOUSEMOVE:
    {
        TCHAR strTemp[128];
        int x = LOWORD(lParam);
        int y = HIWORD(lParam);
        wsprintf(strTemp, L"[%04d, %04d]", x, y);
        SetWindowText(hWnd, strTemp);
    }
    break;
    case WM_COMMAND:
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
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    }
}

int OnPaint(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);
    // TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...

    Ellipse(hdc, 100, 100, 300, 500);
    Rectangle(hdc, 130, 150, 180, 250);
    Rectangle(hdc, 220, 150, 270, 250);
    Ellipse(hdc, 180, 150, 220, 200);

    HBRUSH hOldBr, hMyBr;

    TextOut(hdc, 10, 30, strWheelValue, wcslen(strWheelValue));
    switch (mouseState)
    {
    case MouseMSG::LDBLK:
        TextOut(hdc, 10, 10, L"���콺 ���� ��ư ����Ŭ��", wcslen(L"���콺 ���� ��ư ����Ŭ��"));
        hMyBr = CreateSolidBrush(RGB(255, 0, 0));
        hOldBr = (HBRUSH)SelectObject(hdc, (HBRUSH)hMyBr);
        Rectangle(hdc, 130, 150, 180, 250);
        break;
    case MouseMSG::RDBLK:
        TextOut(hdc, 10, 10, L"���콺 ������ ��ư ����Ŭ��", wcslen(L"���콺 ������ ��ư ����Ŭ��"));
        break;
    case MouseMSG::MDBLK:
        TextOut(hdc, 10, 10, L"���콺 �߰� ��ư ����Ŭ��", wcslen(L"���콺 �߰� ��ư ����Ŭ��"));
        break;
    case MouseMSG::LBD:
        TextOut(hdc, 10, 10, L"���콺 ���� ��ư ������", wcslen(L"���콺 ���� ��ư ������"));
        break;
    case MouseMSG::LBU:
        TextOut(hdc, 10, 10, L"���콺 ���� ��ư ����", wcslen(L"���콺 ���� ��ư ����"));
        break;
    case MouseMSG::RBD:
        TextOut(hdc, 10, 10, L"���콺 ������ ��ư ������", wcslen(L"���콺 ������ ��ư ������"));
        break;
    case MouseMSG::RBU:
        TextOut(hdc, 10, 10, L"���콺 ���� ��ư ����", wcslen(L"���콺 ���� ��ư ����"));
        break;
    case MouseMSG::MBD:
        TextOut(hdc, 10, 10, L"���콺 �߰� ��ư ������", wcslen(L"���콺 ���� ��ư ������"));
        break;
    case MouseMSG::MBU:
        TextOut(hdc, 10, 10, L"���콺 �߰� ��ư ����", wcslen(L"���콺 �߰� ��ư ����"));
        break;
    default:
        TextOut(hdc, 10, 10, L"���콺 ��ư �������� ����", wcslen(L"���콺 ��ư �������� ����"));
        break;
    }
    EndPaint(hWnd, &ps);

    return 0;
}

int OnDestroy(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    PostQuitMessage(0);
    return 0;
}