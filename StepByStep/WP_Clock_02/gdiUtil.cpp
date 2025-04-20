#include "pch.h"
#include "gdiUtil.h"

//=============================================
// Desc : windois GDI ���� �׸��� �Լ�
// Parameter : HDC, ������(x1,y1),����(x2,y2)
// Author :Hyunwoo Lee (eamill :sdh240212@sdh.hs.kr)
// Date : 2025-04-14
int GdiLine(HDC hdc, int x1,int y1,int x2,int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2 , y2);

	return 0;
}

//=============================================
// Desc : windois GDI ���� �׸��� �Լ�
// Parameter : HDC, ��ǥ(mx,my),ũ��(scale)
// Author :Hyunwoo Lee (eamill :sdh240212@sdh.hs.kr)
// Date : 2025-04-14

void gdiStar(HDC hdc, int mx, int my,int scale)
{
	MoveToEx(hdc, mx + 0   * scale,    my + -10 * scale, NULL);
	LineTo(hdc,   mx + 6   * scale,    my + 8	* scale);
	LineTo(hdc,   mx + -10 * scale,	   my + -3  * scale);
	LineTo(hdc,   mx + 10  * scale,    my + -3  * scale);
	LineTo(hdc,   mx + -6  * scale,    my + 8	* scale);
	LineTo(hdc,   mx + 0   * scale,    my + -10 * scale);
}


//=============================================
// Desc : windois GDI ���� 0~9�� ����ϴ� �Լ�
// Parameter : HDC, ��ǥ(x,y),����(n)
// Author :Hyunwoo Lee (eamill :sdh240212@sdh.hs.kr)
// Date : 2025-04-17
void gdiPrintNumber(HDC hdc, int x, int y, int n) {
	TCHAR strNumbers[10][5][10] = {
	{L"����",
	 L"��ԡ�",
	 L"��ԡ�",
	 L"��ԡ�",
	 L"����",
	},
	{L"����",
	 L"�ԡ��",
	 L"�ԡ��",
	 L"�ԡ��",
	 L"����",
	},
	{L"����",
	 L"�Ԥԡ�",
	 L"����",
	 L"��Ԥ�",
	 L"����",
	},
	{L"����",
	 L"�Ԥԡ�",
	 L"����",
	 L"�Ԥԡ�",
	 L"����",
	},
	{L"��ԡ�",
	 L"��ԡ�",
	 L"����",
	 L"�Ԥԡ�",
	 L"�Ԥԡ�",
	},
	{L"����",
	 L"��Ԥ�",
	 L"����",
	 L"�Ԥԡ�",
	 L"����",
	},
	{L"����",
	 L"��Ԥ�",
	 L"����",
	 L"��ԡ�",
	 L"����",
	},
	{L"����",
	 L"��ԡ�",
	 L"�Ԥԡ�",
	 L"�Ԥԡ�",
	 L"�Ԥԡ�",
	},
	{L"����",
	 L"��ԡ�",
	 L"����",
	 L"��ԡ�",
	 L"����",
	},
	{L"����",
	 L"��ԡ�",
	 L"����",
	 L"�Ԥԡ�",
	 L"����",
	},
	};

	if (n >= 10) return;
	for (int i = 0;i < 5;i++) {
		TextOut(hdc, x, y + i * 20, strNumbers[n][i], wcslen(strNumbers[n][i]));
	}
}

void gdiPrintNumbers(HDC hdc, int x, int y, unsigned long long int number) {
	TCHAR strBuff[128]; //���ڸ� ���ڷ� �ٲ� ���� �迭
	int nSize; //������ ����
	wsprintf(strBuff, L"%d", number); //���ڸ� ���ڷ� ��ȯ
	nSize = wcslen(strBuff);

	int seedNum = 1; //����� �ڸ������� ��� 0�� �÷� ������ ����
	int i;
	for (int i = 0;i < nSize - 1;i++) seedNum *= 10; //10���� �ڸ��� ��ŭ ���ϱ�
	int* num;  //������ ���� �ڸ����� ��� ���� ������[�迭�� �����Ϳ� ������ ���� - �����迭�� Ȱ���ϱ� ����]
	num = (int*)malloc(nSize * sizeof(int)); //�޸𸮿� �迭�� ��� ���� �Ҵ��� �̸� �ص�(nSize�� �� ��ŭ int������ �Ҵ� -> int�� �迭 nSize��ŭ)

	for (int i = 0;i < nSize;i++) {
		num[i] = number / seedNum; //�� �ڸ����� ���ڰ� �迭�� ���
		number %= seedNum; //ù���� �ڸ��� �� ���� number�� ����
		seedNum /= 10; //seed�� ������ 10�� �ؼ� ���� ��ȣ�� ���ڸ� �迭�� ���� �� �ֵ��� ��

		gdiPrintNumber(hdc , x += 70, y, num[i]); //���
	}
}