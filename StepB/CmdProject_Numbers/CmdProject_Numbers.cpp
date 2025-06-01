// CmdProject_Numbers.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"

void gotoxy(int x, int y)
{
	COORD CursorPosition = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}

void prtNumber(int x,int y, int n)
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
		gotoxy(x, y+i);
		printf("%s\n", strNumber[n][i]);
	}
}
void DrawNumber(int x,int y, unsigned long long int number)
{
	if (number > INT_MAX)
	{
		printf("%d 이상의 숫자는 출력하지 않습니다.", INT_MAX);
		return;
	}

	char strBuff[128]; //숫자 출력 문자열
	int nSize; //숫자 크기
	sprintf(strBuff, "%d", number); //숫자를 문자열로 저장
	nSize = strlen(strBuff); //숫자 변화된 문자열의 크기 구하기

	int seedNum = 1; //시작이 1의 자리
	int i;
	for (i = 0;i < nSize - 1;i++) seedNum *= 10; //10진수 자리수 만큼 곱하기  (자리수만큼 변해서 할수 있음)
	int* num;
	num = (int*)malloc(nSize * sizeof(int)); //메모리 확보를 해줘(nSize의 수만큼 int형 ==> int형 배열 nSize만큼)

	//문자화된 숫자를 다시 한 숫자씩 포인터 num(num 배열)에 저장
	for (i = 0;i < nSize;i++)
	{
		num[i] = number / seedNum; //포인터 배열 num에 하나씩 숫자 저장
		number %= seedNum; //큰 수를 줄인 수를 돌려주기
		seedNum /= 10; //자리수 줄이기
	
		prtNumber(x += 8, y, num[i]); //숫자 출력
	}
}
int main()
{
	DrawNumber(10,5,123456789);
}
