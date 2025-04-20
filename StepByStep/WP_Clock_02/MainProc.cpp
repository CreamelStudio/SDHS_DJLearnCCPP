#include "pch.h"
#include "MainProc.h"

extern HINSTANCE hInst;

SYSTEMTIME gST;
HFONT ghFont;

//WM_CREATE ���� �Լ� //�����찡 ������� �� �� ���� ȣ��
int OnCreate(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    ghFont = CreateFontW(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"�ü�ü");
    SetTimer(hWnd, 0, 1000, NULL); //�ð� ���� ID(0��), 1000(1��)
    //���� ���ϴ� �޽����� �����쿡�� ��Ź�ϴ� ���
    SendMessage(hWnd, WM_TIMER, NULL, NULL);
    //OnTimer(hWnd, NULL, NULL); //�� ���� ���
    return 0;
}

//WM_TIMER ���� �Լ� //������ ���� ������ ������ �ð����� �ݺ� ȣ�� 
int OnTimer(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    GetLocalTime(&gST);//SYSTEMTIME����ü ���� �� �����ϱ�

    TCHAR strTime[128]; //���ڿ� //�ð�
    wsprintf(strTime, L"%d�� %d�� %d��", //���ڿ��� �ð� ����
        gST.wHour, gST.wMinute, gST.wSecond);
    SetWindowText(hWnd, strTime);
    InvalidateRect(hWnd, NULL, TRUE); //��ȿȭ�����Ͽ� WM_PAINTȣ��
    return 0;
}

int OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam)
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
        return DefWindowProc(hWnd, WM_COMMAND, wParam, lParam);
    }
    return 0;
}

int OnPaint(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);
    // TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...
    SelectObject(hdc, ghFont);
    gdiPrintNumbers(hdc, 0, 0, gST.wHour);
    gdiPrintNumbers(hdc, 300, 0, gST.wMinute);
    gdiPrintNumbers(hdc, 600, 0, gST.wSecond);

    EndPaint(hWnd, &ps);
    return 0;
}

int OnDestroy(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    KillTimer(hWnd, 0);
    PostQuitMessage(0);
    return 0;
}

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
    case WM_CREATE:     return OnCreate(hWnd, wParam, lParam);
    case WM_TIMER:      return OnTimer(hWnd, wParam, lParam);
    case WM_COMMAND:    return OnCommand(hWnd, wParam, lParam);
    case WM_PAINT:      return OnPaint(hWnd, wParam, lParam);
    case WM_DESTROY:    return OnDestroy(hWnd, wParam, lParam);
    default:            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
