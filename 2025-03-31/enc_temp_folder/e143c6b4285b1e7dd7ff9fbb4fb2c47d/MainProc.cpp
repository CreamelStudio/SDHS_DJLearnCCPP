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

	for (int i = 0;i < 10;i++)
	{
		//gdiStar(hdc, rand() % 800, rand() % 600,rand()%10 + 1);
		GdiLine(hdc, rand() % 800, rand() % 600, rand() % 800, rand() % 600);
	}

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






