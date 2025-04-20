#include "pch.h"

extern HINSTANCE hInst;
int OnPaint(HWND hWnd, WPARAM wParam, LPARAM lParam);

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

	// 숫자 0
	GdiLine(hdc, 50, 50, 70, 50);
	GdiLine(hdc, 70, 50, 70, 90);
	GdiLine(hdc, 70, 90, 50, 90);
	GdiLine(hdc, 50, 90, 50, 50);

	// 숫자 1
	GdiLine(hdc, 90, 50, 90, 90);

	// 숫자 2
	GdiLine(hdc, 110, 50, 130, 50);
	GdiLine(hdc, 130, 50, 130, 70);
	GdiLine(hdc, 130, 70, 110, 90);
	GdiLine(hdc, 110, 90, 130, 90);

	// 숫자 3
	GdiLine(hdc, 150, 50, 170, 50);
	GdiLine(hdc, 170, 50, 170, 70);
	GdiLine(hdc, 170, 70, 150, 70);
	GdiLine(hdc, 170, 70, 170, 90);
	GdiLine(hdc, 170, 90, 150, 90);

	// 숫자 4
	GdiLine(hdc, 190, 50, 190, 70);
	GdiLine(hdc, 190, 70, 210, 70);
	GdiLine(hdc, 210, 50, 210, 90);

	// 숫자 5
	GdiLine(hdc, 230, 50, 250, 50);
	GdiLine(hdc, 230, 50, 230, 70);
	GdiLine(hdc, 230, 70, 250, 70);
	GdiLine(hdc, 250, 70, 250, 90);
	GdiLine(hdc, 250, 90, 230, 90);

	// 숫자 6
	GdiLine(hdc, 270, 50, 270, 90);
	GdiLine(hdc, 270, 90, 290, 90);
	GdiLine(hdc, 290, 90, 290, 70);
	GdiLine(hdc, 290, 70, 270, 70);

	// 숫자 7
	GdiLine(hdc, 310, 50, 330, 50);
	GdiLine(hdc, 330, 50, 330, 90);

	// 숫자 8
	GdiLine(hdc, 350, 50, 370, 50);
	GdiLine(hdc, 370, 50, 370, 90);
	GdiLine(hdc, 370, 90, 350, 90);
	GdiLine(hdc, 350, 90, 350, 50);
	GdiLine(hdc, 350, 70, 370, 70);

	// 숫자 9
	GdiLine(hdc, 410, 90, 410, 70);
	GdiLine(hdc, 390, 70, 410, 70);
	GdiLine(hdc, 410, 70, 410, 50);
	GdiLine(hdc, 410, 50, 390, 50);
	GdiLine(hdc, 390, 50, 390, 70);

	
	//선그리는 함수를 MoveToEx(),LineTo() 이용해서 만드세요
	//GdiLine(hdc,100,300,200,500);

	EndPaint(hWnd, &ps);
	return 0;
}

int OnDestroy(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	PostQuitMessage(0);
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND: return OnCommand(hWnd, wParam, lParam);

	case WM_PAINT:   return OnPaint(hWnd, wParam, lParam);
	case WM_DESTROY: return OnDestroy(hWnd, wParam, lParam);

	default:         return DefWindowProc(hWnd, message, wParam, lParam);

	}
	return 0;
}






