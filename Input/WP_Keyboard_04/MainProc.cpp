#include "pch.h"
#include "MainProc.h"

extern HINSTANCE hInst;
extern MouseMSG mouseState;
extern TCHAR strWheelValue[128];

MOUSE_OBJ* g_mouse;

MouseMSG Mouse_GetMSG(UINT message)
{
    switch (message) 
    {
    case WM_LBUTTONDOWN:   return MouseMSG::LBD;
    case WM_LBUTTONUP:     return MouseMSG::LBU;
    case WM_RBUTTONDOWN:   return MouseMSG::RBD;
    case WM_RBUTTONUP:     return MouseMSG::RBU;
    case WM_MBUTTONDOWN:   return MouseMSG::MBD;
    case WM_MBUTTONUP:     return MouseMSG::MBU;
    case WM_LBUTTONDBLCLK: return MouseMSG::LDBLK;
    case WM_RBUTTONDBLCLK: return MouseMSG::RDBLK;
    case WM_MBUTTONDBLCLK: return MouseMSG::MDBLK;
    default:               return MouseMSG::NONE;
    }
}

int OnMouseBtnClk(HWND hWnd, WPARAM wParam, LPARAM lParam)
{    
    if (g_mouse && g_mouse->state >= 0 && g_mouse->state < MouseMSG::MSG_COUNT)
    {
        return g_mouse->handlers[g_mouse->state](g_mouse, hWnd, wParam, lParam);
    }
    return 0;
}

int OnMouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    if (g_mouse)
    { 
        g_mouse->Update(g_mouse, MouseMSG::NONE, lParam); 
        InvalidateRect(hWnd, NULL, TRUE); 
    }
    return 0;
}

int OnMouseWheel(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    if (g_mouse) 
    { 
        g_mouse->SetWheel(g_mouse, wParam); 
        InvalidateRect(hWnd, NULL, TRUE); 
    }
    return 0;
}

int OnCreate(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    g_mouse = StartMouseObject(0, 0, 300, 500);
    return 0;
}

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
    g_mouse->Draw(g_mouse, hdc);
    EndPaint(hWnd, &ps);

    return 0;
}

int OnDestroy(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    if (g_mouse) {  g_mouse->Release(g_mouse);       g_mouse = NULL; }
    PostQuitMessage(0);
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
    case WM_LBUTTONDOWN:    case WM_LBUTTONUP:        case WM_RBUTTONDOWN:     
    case WM_RBUTTONUP:      case WM_MBUTTONDOWN:      case WM_MBUTTONUP:    
    case WM_LBUTTONDBLCLK:  case WM_RBUTTONDBLCLK:    case WM_MBUTTONDBLCLK:
                            g_mouse->state = Mouse_GetMSG(message);
                            return OnMouseBtnClk(hWnd, wParam, lParam);
    case WM_MOUSEMOVE:      return OnMouseMove(hWnd, wParam, lParam);
    case WM_MOUSEWHEEL:     return OnMouseWheel(hWnd, wParam, lParam);
    case WM_COMMAND:        return OnCommand(hWnd, wParam, lParam);
    case WM_PAINT:          return OnPaint(hWnd, wParam, lParam);
    case WM_DESTROY:        return OnDestroy(hWnd, wParam, lParam);
    default:                return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
