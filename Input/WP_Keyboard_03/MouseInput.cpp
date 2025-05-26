#include "pch.h"
#include "MouseInput.h"

extern HINSTANCE hInst;
extern MouseMSG mouseState;
extern TCHAR strWheelValue[128];

MOUSEOBJ* StartMouseObject(int x, int y, int w, int h) {
    MOUSEOBJ* Temp;
	Temp = (MOUSEOBJ*)malloc(sizeof(MOUSEOBJ));

    Temp->x = x;
    Temp->y = y;
    Temp->w = w;
    Temp->h = h;

    Temp->rtMouse = { x, y, w, h };
    Temp->rtLeftBtn = { (x + 100) - 40, (y + 100) - 40, (x + 100) + 40, (y + 100) + 40 };
    Temp->rtRightBtn = { (Temp->rtMouse.right - 100) - 40, (Temp->rtMouse.right - 100) - 40, (Temp->rtMouse.right - 100) + 40, (Temp->rtMouse.right - 100) + 40 };
    Temp->rtMiddleBtn = { x + (w / 2) - 20, x + (w / 2) - 20, x + (w / 2) + 20, x + (w / 2) + 20 };

	Temp->State = MouseMSG::NONE;

    Temp->crBtnState[0][0] = RGB(255, 255, 255);
    Temp->crBtnState[1][0] = RGB(255, 255, 255);
    Temp->crBtnState[2][0] = RGB(255, 255, 255);

    Temp->crBtnState[0][1] = RGB(255, 0, 0);
    Temp->crBtnState[1][1] = RGB(0, 0, 255);
    Temp->crBtnState[2][1] = RGB(0, 255, 0);

    return Temp;
}

void Update(MOUSEOBJ* mouse) {
    mouse->State = mouseState;
}

void Draw(MOUSEOBJ* mouse, HDC hdc)
{
    int l = mouse->rtMouse.left;
    int r = mouse->rtMouse.right;
    int t = mouse->rtMouse.top;
    int b = mouse->rtMouse.bottom;
    Ellipse(hdc, l, t, r, b);

    int lbl = mouse->rtLeftBtn.left;
    int lbr = mouse->rtLeftBtn.right;
    int lbt = mouse->rtLeftBtn.top;
    int lbb = mouse->rtLeftBtn.bottom;
    Rectangle(hdc, lbl, lbt, lbr, lbb);

    int rbl = mouse->rtRightBtn.left;
    int rbr = mouse->rtRightBtn.right;
    int rbt = mouse->rtRightBtn.top;
    int rbb = mouse->rtRightBtn.bottom;
    Rectangle(hdc, rbl, rbt, rbr, rbb);

    int mbl = mouse->rtMiddleBtn.left;
    int mbr = mouse->rtMiddleBtn.right;
    int mbt = mouse->rtMiddleBtn.top;
    int mbb = mouse->rtMiddleBtn.bottom;
    Ellipse(hdc, mbl, mbt, mbr, mbb);

    HBRUSH hOldBr, hMyBr;

    TextOut(hdc, 10, 30, strWheelValue, wcslen(strWheelValue)); //휠
    switch (mouseState)
    {
    case MouseMSG::LDBLK:
        TextOut(hdc, 10, 10, L"마우스 왼쪽 버튼 더블클릭", wcslen(L"마우스 왼쪽 버튼 더블클릭"));
        hMyBr = CreateSolidBrush(RGB(255, 255, 0));
        hOldBr = (HBRUSH)SelectObject(hdc, (HBRUSH)hMyBr);
        Rectangle(hdc, lbl, lbt, lbr, lbb);
        SelectObject(hdc, hOldBr);
        break;
    case MouseMSG::RDBLK:
        TextOut(hdc, 10, 10, L"마우스 오른쪽 버튼 더블클릭", wcslen(L"마우스 오른쪽 버튼 더블클릭"));
        hMyBr = CreateSolidBrush(RGB(0, 255, 255));
        hOldBr = (HBRUSH)SelectObject(hdc, (HBRUSH)hMyBr);
        Rectangle(hdc, rbl, rbt, rbr, rbb);
        SelectObject(hdc, hOldBr);
        break;
    case MouseMSG::MDBLK:
        TextOut(hdc, 10, 10, L"마우스 중간 버튼 더블클릭", wcslen(L"마우스 중간 버튼 더블클릭"));
        hMyBr = CreateSolidBrush(RGB(255, 0, 255));
        hOldBr = (HBRUSH)SelectObject(hdc, (HBRUSH)hMyBr);
        Ellipse(hdc, mbl, mbt, mbr, mbb);
        SelectObject(hdc, hOldBr);
        break;
    case MouseMSG::LBD:
        TextOut(hdc, 10, 10, L"마우스 왼쪽 버튼 눌러짐", wcslen(L"마우스 왼쪽 버튼 눌러짐"));
        hMyBr = CreateSolidBrush(mouse->crBtnState[0][1]);
        hOldBr = (HBRUSH)SelectObject(hdc, (HBRUSH)hMyBr);
        Rectangle(hdc, lbl, lbt, lbr, lbb);
        SelectObject(hdc, hOldBr);
        break;
    case MouseMSG::LBU:
        TextOut(hdc, 10, 10, L"마우스 왼쪽 버튼 떼짐", wcslen(L"마우스 왼쪽 버튼 떼짐"));
        Rectangle(hdc, lbl, lbt, lbr, lbb);
        break;
    case MouseMSG::RBD:
        TextOut(hdc, 10, 10, L"마우스 오른쪽 버튼 눌러짐", wcslen(L"마우스 오른쪽 버튼 눌러짐"));
        hMyBr = CreateSolidBrush(mouse->crBtnState[1][1]);
        hOldBr = (HBRUSH)SelectObject(hdc, (HBRUSH)hMyBr);
        Rectangle(hdc, rbl, rbt, rbr, rbb);
        SelectObject(hdc, hOldBr);
        break;
    case MouseMSG::RBU:
        TextOut(hdc, 10, 10, L"마우스 오른쪽 버튼 떼짐", wcslen(L"마우스 오른쪽 버튼 떼짐"));
        Rectangle(hdc, rbl, rbt, rbr, rbb);
        break;
    case MouseMSG::MBD:
        TextOut(hdc, 10, 10, L"마우스 중간 버튼 눌러짐", wcslen(L"마우스 중간 버튼 눌러짐"));
        hMyBr = CreateSolidBrush(mouse->crBtnState[2][1]);
        hOldBr = (HBRUSH)SelectObject(hdc, (HBRUSH)hMyBr);
        Ellipse(hdc, mbl, mbt, mbr, mbb);
        SelectObject(hdc, hOldBr);
        break;
    case MouseMSG::MBU:
        TextOut(hdc, 10, 10, L"마우스 중간 버튼 떼짐", wcslen(L"마우스 중간 버튼 떼짐"));
        Ellipse(hdc, mbl, mbt, mbr, mbb);
        break;
    default:
        TextOut(hdc, 10, 10, L"마우스 버튼 눌러지지 않음", wcslen(L"마우스 버튼 눌러지지 않음"));
    }

}

void Release(MOUSEOBJ* mouse) {
    if (mouse == NULL) return;
	free(mouse);
}

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