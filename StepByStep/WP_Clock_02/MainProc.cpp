#include "pch.h"

extern HINSTANCE hInst;

SYSTEMTIME gSt;

//WM_CREATE 실행 함수 //윈도우가 만들어질 때 헌 번만 호출
int OnCreate(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	SetTimer(hWnd, 0, 1000, NULL); //시간 설정 ID(0번), 1000(1초)
	SendMessage(hWnd, WM_TIMER, NULL, NULL); //내가 윈하는 메시지를 윈도우에게 부탁하는 형식
	//OnTimer(hWand,NLII,NULL); //안 좋은 방식
	return 0;
}

//WM_TIMER 실행 함수 //정해진 시간마다 반복 호출  //윈도우 종료 전까지
int OnTimer(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	GetLocalTime(&gSt); //SYSTEMIME구조체 변수 값 저장하기
	TCHAR strTime[128];
	wsprintf(strTime, L"%d시 %d분 %d초", gSt.wHour, gSt.wMinute, gSt.wSecond);
	SetWindowText(hWnd, strTime);
	InvalidateRect(hWnd, NULL, NULL); // 무효화선선언하여  wm_paint호출
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
	TCHAR strTime[128]; //문자열 //시간
	
	gdiPrintNumbers(hdc, 0, 0, gSt.wHour);
	gdiPrintNumbers(hdc, 200, 0, gSt.wMinute);
	gdiPrintNumbers(hdc, 400, 0, gSt.wSecond);

	EndPaint(hWnd, &ps);
	return 0;
}

int OnDestroy(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	KillTimer(hWnd, 0);
	PostQuitMessage(0);
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE: return OnCreate(hWnd, wParam, lParam);
		break;
	case WM_TIMER: return OnTimer(hWnd, wParam, lParam);
		break;
	case WM_COMMAND: return OnCommand(hWnd, wParam, lParam);

	case WM_PAINT:   return OnPaint(hWnd, wParam, lParam);
	case WM_DESTROY: return OnDestroy(hWnd, wParam, lParam);

	default:         return DefWindowProc(hWnd, message, wParam, lParam);

	}
	return 0;
}





