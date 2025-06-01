#include "pch.h"

extern HINSTANCE hInst;
int OnPaint(HWND hWnd, WPARAM wParam, LPARAM lParam);

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

	DrawNumber(hdc, 100, 100, 1234567890);

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

void prtNumber(int x, int y, int n)
{
	char strNumber[10][5][7] = {
		{" OOO ",
		 "O   O",
		 "O   O",
		 "O   O",
		 " OOO",
		},

		{" 1111 ",
		 "  11  ",
		 "  11  ",
		 "  11  ",
		 "111111",
		},

		{"22222",
		 "   22",
		 "22222",
		 "22  ",
		 "22222",
		},

		{"33333",
		 "   33",
		 "33333",
		 "   33",
		 "33333",
		},

		{"44   ",
		 "444  ",
		 "444444",
		 "   44",
		 "   44",
		},

		{"55555",
		 "55   ",
		 "55555",
		 "   55",
		 "55555",
		},

		{" 666",
		 "6   ",
		 "6666 ",
		 "6   6",
		 " 666 ",
		 },

		 {"77777",
		 "   77 ",
		 "   77 ",
		 "  77  ",
		 " 77   ",
		 },

		{" 888 ",
		 "8   8",
		 " 888 ",
		 "8   8",
		 " 888 ",
		 },
		 {"99999",
		 "9   99",
		 "999999",
		 "   999",
		 "999999",
		 },

	};

	if (n >= 10) return;
	for (int i = 0;i < 5;i++)
	{
		gotoxy(x, y + i);
		printf("%s\n", strNumber[n][i]);
	}
}

void gotoxy(int x, int y)
{
	COORD CursorPosition = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}

void DrawNumber(HDC hdc, int x, int y, unsigned long long int number)
{
	if (number > INT_MAX)
	{
		printf("%d �̻��� ���ڴ� ������� �ʽ��ϴ�.", INT_MAX);
		return;
	}

	char strBuff[128]; //���� ��� ���ڿ�
	int nSize; //���� ũ��
	sprintf(strBuff, "%d", number); //���ڸ� ���ڿ��� ����
	nSize = strlen(strBuff); //���� ��ȭ�� ���ڿ��� ũ�� ���ϱ�

	int seedNum = 1; //������ 1�� �ڸ�
	int i;
	for (i = 0;i < nSize - 1;i++) seedNum *= 10; //10���� �ڸ��� ��ŭ ���ϱ�  (�ڸ�����ŭ ���ؼ� �Ҽ� ����)
	int* num;
	num = (int*)malloc(nSize * sizeof(int)); //�޸� Ȯ���� ����(nSize�� ����ŭ int�� ==> int�� �迭 nSize��ŭ)

	//����ȭ�� ���ڸ� �ٽ� �� ���ھ� ������ num(num �迭)�� ����
	for (i = 0;i < nSize;i++)
	{
		num[i] = number / seedNum; //������ �迭 num�� �ϳ��� ���� ����
		number %= seedNum; //ū ���� ���� ���� �����ֱ�
		seedNum /= 10; //�ڸ��� ���̱�

		prtNumber(x += 8, y, num[i]); //���� ���
	}
}






