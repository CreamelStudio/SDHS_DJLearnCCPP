#include "pch.h"
#include "gdiUtil.h"

//==========================================
// Desc : Windows GDI 선을 그리는 함수
// Parameter : HDC, 시작점(x1, y1), 끝점(x2, y2)
// Author : DJ__KIM (email : cosmosun@sdh.hs.kr)
// Date : 2025-04-14  
void gdiLine(HDC hdc, int x1, int y1, int x2, int y2)
{
    MoveToEx(hdc, x1, y1, NULL);
    LineTo(hdc, x2, y2);
}

//==========================================
// Desc : Windows GDI 별을 그리는 함수
// Parameter : HDC, 좌표(mx, my), 크기(scale)
// Author : DJ__KIM (email : cosmosun@sdh.hs.kr)
// Date : 2025-04-14     
void gdiStar(HDC hdc, int mx, int my, int scale)
{
    MoveToEx(hdc,   mx + 0 * scale,     my + -10 * scale, NULL);
    LineTo(hdc,     mx + 6 * scale,     my + 8 * scale);
    LineTo(hdc,     mx + -10 * scale,   my + -3 * scale);
    LineTo(hdc,     mx + 10 * scale,    my + -3 * scale);
    LineTo(hdc,     mx + -6 * scale,    my + 8 * scale);
    LineTo(hdc,     mx + 0 * scale,     my + -10 * scale);
}

//==========================================
// Desc : Windows GDI 숫자 0~9을 출력하는 함수
// Parameter : HDC, 좌표(x, y), 숫자(0~9)(n)
// Author : DJ__KIM (email : cosmosun@sdh.hs.kr)
// Date : 2025-04-17 
void gdiPrintNumber(HDC hdc, int x, int y, int n)
{
	TCHAR strNumber[10][5][7] = {
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
	for (int i = 0; i < 5; i++)
	{
		TextOut(hdc, x, y + i * 25, strNumber[n][i], wcslen(strNumber[n][i]));
	}
}

void gdiPrintNumbers(HDC hdc, int x, int y, unsigned int number)
{
	if (number > INT_MAX) //숫자 크기 제한
	{
		//printf("%d 이상의 숫자는 출력하지 않습니다.", INT_MAX);
		return;
	}

	TCHAR strBuff[128]; //숫자 출력 문자열
	int  nSize; //숫자 크기
	wsprintf(strBuff, L"%d", number); //숫자를 문자열로 저장
	nSize = wcslen(strBuff); //숫자가 변환된 문자열의 크기 구하기

	int seedNum = 1; //시작이 1의 자리
	int i;
	for (i = 0; i < nSize - 1; i++) seedNum *= 10; //10진수 자리수 만큼 곱하기 
	int* num;
	num = (int*)malloc(nSize * sizeof(int)); //메모리 확보를 해줘(nSize의 수 만큼 int형 ==> int형 배열 nSize만큼)

	//문자화된 숫자를 다시 한 숫자씩 포인터num(num 배열)에 하나씩 저장
	for (i = 0; i < nSize; i++)
	{
		num[i] = number / seedNum; //포인터 배열 num에 하나씩 숫자 저장
		number %= seedNum; //큰 수를 줄인 수를 돌려주기
		seedNum /= 10; //자리수 줄이기 

		gdiPrintNumber(hdc, x += 120, y, num[i]); //숫자 출력
	}
}