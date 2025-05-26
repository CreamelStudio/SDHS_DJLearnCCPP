#include "pch.h"
#include "MainProc.h"

extern HINSTANCE hInst;
extern MouseMSG mouseState;
extern TCHAR strWheelValue[128];
MOUSEOBJ* myMouse;

int OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam)
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
        return DefWindowProc(hWnd, WM_COMMAND, wParam, lParam);
    }
    return 0;
}

int OnPaint(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);
    // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
    Draw(myMouse, hdc);
    
    EndPaint(hWnd, &ps);

    return 0;
}

int OnDestroy(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    PostQuitMessage(0);
    return 0;
}

int OnCreate(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    myMouse = StartMouseObject(0, 0, 300, 600);
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
	case WM_CREATE:         return OnCreate(hWnd, wParam, lParam);
    case WM_MOUSEWHEEL:     return OnMouseWheel(hWnd, wParam, lParam);
    case WM_LBUTTONDBLCLK:  return OnMouseLBTNDBLCLK(hWnd, wParam, lParam);
    case WM_RBUTTONDBLCLK:  return OnMouseRBTNDBLCLK(hWnd, wParam, lParam);
    case WM_MBUTTONDBLCLK:  return OnMouseMBTNDBLCLK(hWnd, wParam, lParam);
    case WM_LBUTTONDOWN:    return OnMouseLBTNDN(hWnd, wParam, lParam);
    case WM_LBUTTONUP:      return OnMouseLBTNUP(hWnd, wParam, lParam);
    case WM_RBUTTONDOWN:    return OnMouseRBTNDN(hWnd, wParam, lParam);
    case WM_RBUTTONUP:      return OnMouseRBTNUP(hWnd, wParam, lParam);
    case WM_MBUTTONDOWN:    return OnMouseMBTNDN(hWnd, wParam, lParam);
    case WM_MBUTTONUP:      return OnMouseMBTNUP(hWnd, wParam, lParam);
    case WM_MOUSEMOVE:      return OnMouseMove(hWnd, wParam, lParam);
    case WM_COMMAND:        return OnCommand(hWnd, wParam, lParam);
    case WM_PAINT:          return OnPaint(hWnd, wParam, lParam);
    case WM_DESTROY:        return OnDestroy(hWnd, wParam, lParam);
    default:                return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
