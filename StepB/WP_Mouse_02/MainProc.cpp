#include "pch.h"
#include "MainProc.h"

extern HINSTANCE hInst;
extern MouseMSG mouseState;
extern TCHAR strWheelValue[128];

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
    case WM_MOUSEWHEEL:     return OnMouseWheel(hWnd, wParam, lParam);
    case WM_LBUTTONDBLCLK:  return OnMouseLBUTTONDBLCLK(hWnd, wParam, lParam);
    case WM_RBUTTONDBLCLK:  return OnMouseRBUTTONDBLCLK(hWnd, wParam, lParam);
    case WM_MBUTTONDBLCLK:  return OnMouseMBUTTONDBLCLK(hWnd, wParam, lParam);
    case WM_LBUTTONDOWN:    return OnMouseLBUTTONDOWN(hWnd, wParam, lParam);
    case WM_LBUTTONUP:      return OnMouseLBUTTONUP(hWnd, wParam, lParam);
    case WM_RBUTTONDOWN:    return OnMouseRBUTTONDOWN(hWnd, wParam, lParam);
    case WM_RBUTTONUP:      return OnMouseRBUTTONUP(hWnd, wParam, lParam);
    case WM_MBUTTONDOWN:    return OnMouseMBUTTONDOWN(hWnd, wParam, lParam);
    case WM_MBUTTONUP:      return OnMouseMBUTTONUP(hWnd, wParam, lParam);
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
    TextOut(hdc, 10, 30, strWheelValue, wcslen(strWheelValue));
    switch (mouseState)
    {
    case MouseMSG::LDBLK:
        TextOut(hdc, 10, 10, L"���콺 ���� ��ư ����Ŭ��", wcslen(L"���콺 ���� ��ư ����Ŭ��"));
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
