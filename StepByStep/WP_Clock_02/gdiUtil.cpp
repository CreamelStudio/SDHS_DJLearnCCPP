#include "pch.h"
#include "gdiUtil.h"

//=============================================
// Desc : windois GDI 선을 그리는 함수
// Parameter : HDC, 시작점(x1,y1),끝점(x2,y2)
// Author :Hyunwoo Lee (eamill :sdh240212@sdh.hs.kr)
// Date : 2025-04-14
int GdiLine(HDC hdc, int x1,int y1,int x2,int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2 , y2);

	return 0;
}

//=============================================
// Desc : windois GDI 별을 그리는 함수
// Parameter : HDC, 좌표(mx,my),크기(scale)
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
// Desc : windois GDI 숫자 0~9를 출력하는 함수
// Parameter : HDC, 좌표(x,y),숫자(n)
// Author :Hyunwoo Lee (eamill :sdh240212@sdh.hs.kr)
// Date : 2025-04-17
void gdiPrintNumber(HDC hdc, int x, int y, int n) {
	TCHAR strNumbers[10][5][10] = {
	{L"■■■",
	 L"■ㅤ■",
	 L"■ㅤ■",
	 L"■ㅤ■",
	 L"■■■",
	},
	{L"■■ㅤ",
	 L"ㅤ■ㅤ",
	 L"ㅤ■ㅤ",
	 L"ㅤ■ㅤ",
	 L"■■■",
	},
	{L"■■■",
	 L"ㅤㅤ■",
	 L"■■■",
	 L"■ㅤㅤ",
	 L"■■■",
	},
	{L"■■■",
	 L"ㅤㅤ■",
	 L"■■■",
	 L"ㅤㅤ■",
	 L"■■■",
	},
	{L"■ㅤ■",
	 L"■ㅤ■",
	 L"■■■",
	 L"ㅤㅤ■",
	 L"ㅤㅤ■",
	},
	{L"■■■",
	 L"■ㅤㅤ",
	 L"■■■",
	 L"ㅤㅤ■",
	 L"■■■",
	},
	{L"■■■",
	 L"■ㅤㅤ",
	 L"■■■",
	 L"■ㅤ■",
	 L"■■■",
	},
	{L"■■■",
	 L"■ㅤ■",
	 L"ㅤㅤ■",
	 L"ㅤㅤ■",
	 L"ㅤㅤ■",
	},
	{L"■■■",
	 L"■ㅤ■",
	 L"■■■",
	 L"■ㅤ■",
	 L"■■■",
	},
	{L"■■■",
	 L"■ㅤ■",
	 L"■■■",
	 L"ㅤㅤ■",
	 L"■■■",
	},
	};

	if (n >= 10) return;
	for (int i = 0;i < 5;i++) {
		TextOut(hdc, x, y + i * 20, strNumbers[n][i], wcslen(strNumbers[n][i]));
	}
}

void gdiPrintNumbers(HDC hdc, int x, int y, unsigned long long int number) {
	TCHAR strBuff[128]; //숫자를 문자로 바꿔 넣을 배열
	int nSize; //숫자의 길이
	wsprintf(strBuff, L"%d", number); //숫자를 문자로 변환
	nSize = wcslen(strBuff);

	int seedNum = 1; //몇번쨰 자리수인지 계속 0씩 늘려 곱해줄 변수
	int i;
	for (int i = 0;i < nSize - 1;i++) seedNum *= 10; //10진수 자리수 만큼 곱하기
	int* num;  //각각의 숫자 자리수를 담기 위한 포인터[배열을 포인터에 배정할 예정 - 동적배열을 활용하기 위해]
	num = (int*)malloc(nSize * sizeof(int)); //메모리에 배열을 담기 위해 할당을 미리 해둠(nSize의 수 만큼 int형으로 할당 -> int형 배열 nSize만큼)

	for (int i = 0;i < nSize;i++) {
		num[i] = number / seedNum; //각 자리수의 숫자가 배열의 담김
		number %= seedNum; //첫번쨰 자리를 뺀 값을 number에 받음
		seedNum /= 10; //seed를 나누기 10을 해서 다음 번호의 숫자를 배열에 담을 수 있도록 함

		gdiPrintNumber(hdc , x += 70, y, num[i]); //출력
	}
}