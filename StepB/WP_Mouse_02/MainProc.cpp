#include "pch.h"
#include "MainProc.h"

extern HINSTANCE hInst;
extern MouseMSG mouseState;
extern TCHAR strWheelValue[128];

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
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    }
}
int OnPaint(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);
    // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

    Ellipse(hdc, 100, 100, 300, 500);
    Rectangle(hdc, 130, 150, 180, 250);
    Rectangle(hdc, 220, 150, 270, 250);
    Ellipse(hdc, 180, 150, 220, 200);
    TextOut(hdc, 10, 30, strWheelValue, wcslen(strWheelValue));
    switch (mouseState)
    {
    case MouseMSG::LDBLK:
        TextOut(hdc, 10, 10, L"마우스 왼쪽 버튼 더블클릭", wcslen(L"마우스 왼쪽 버튼 더블클릭"));
        break;
    case MouseMSG::RDBLK:
        TextOut(hdc, 10, 10, L"마우스 오른쪽 버튼 더블클릭", wcslen(L"마우스 오른쪽 버튼 더블클릭"));
        break;
    case MouseMSG::MDBLK:
        TextOut(hdc, 10, 10, L"마우스 중간 버튼 더블클릭", wcslen(L"마우스 중간 버튼 더블클릭"));
        break;
    case MouseMSG::LBD:
        TextOut(hdc, 10, 10, L"마우스 왼쪽 버튼 눌러짐", wcslen(L"마우스 왼쪽 버튼 눌러짐"));
        break;
    case MouseMSG::LBU:
        TextOut(hdc, 10, 10, L"마우스 왼쪽 버튼 떼짐", wcslen(L"마우스 왼쪽 버튼 떼짐"));
        break;
    case MouseMSG::RBD:
        TextOut(hdc, 10, 10, L"마우스 오른쪽 버튼 눌러짐", wcslen(L"마우스 오른쪽 버튼 눌러짐"));
        break;
    case MouseMSG::RBU:
        TextOut(hdc, 10, 10, L"마우스 왼쪽 버튼 떼짐", wcslen(L"마우스 왼쪽 버튼 떼짐"));
        break;
    case MouseMSG::MBD:
        TextOut(hdc, 10, 10, L"마우스 중간 버튼 눌러짐", wcslen(L"마우스 왼쪽 버튼 눌러짐"));
        break;
    case MouseMSG::MBU:
        TextOut(hdc, 10, 10, L"마우스 중간 버튼 떼짐", wcslen(L"마우스 중간 버튼 떼짐"));
        break;
    default:
        TextOut(hdc, 10, 10, L"마우스 버튼 눌러지지 않음", wcslen(L"마우스 버튼 눌러지지 않음"));
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
