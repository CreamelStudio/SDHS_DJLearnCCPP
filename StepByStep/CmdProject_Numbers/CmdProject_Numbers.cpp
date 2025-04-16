// CmdProject_Numbers.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"



void gotoXY(int x, int y) {
	COORD CursorPosition = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}

void prtNumber(int x, int y, int n) {
	char strNumbers[10][5][10] = {
	{"■■■",
	 "■ ■",
	 "■ ■",
	 "■ ■",
	 "■■■",
	},
	{"■■ ",
	 " ■",
	 " ■",
	 " ■",
	 "■■■",
	},
	{"■■■",
	 "  ■",
	 "■■■",
	 "■  ",
	 "■■■",
	},
	{"■■■",
	 "  ■",
	 "■■■",
	 "  ■",
	 "■■■",
	},
	{"■ ■",
	 "■ ■",
	 "■■■",
	 "  ■",
	 "  ■",
	},
	{"■■■",
	 "■  ",
	 "■■■",
	 "  ■",
	 "■■■",
	},
	{"■■■",
	 "■  ",
	 "■■■",
	 "■ ■",
	 "■■■",
	},
	{"■■■",
	 "■ ■",
	 "  ■",
	 "  ■",
	 "  ■",
	},
	{"■■■",
	 "■ ■",
	 "■■■",
	 "■ ■",
	 "■■■",
	},
	{"■■■",
	 "■ ■",
	 "■■■",
	 "  ■",
	 "■■■",
	},
	};

	if (n >= 10) return;
	for (int i = 0;i < 5;i++) {
		gotoXY(x, y + i);
		printf("%s\n", strNumbers[n][i]);
	}
}

void DrawNumbers(int x, int y, unsigned long long int number) {
	char strBuff[128]; //숫자를 문자로 바꿔 넣을 배열
	int nSize; //숫자의 길이
	sprintf(strBuff, "%d", number); //숫자를 문자로 변환
	nSize = strlen(strBuff);

	int seedNum = 1; //몇번쨰 자리수인지 계속 0씩 늘려 곱해줄 변수
	int i;
	for (int i = 0;i < nSize - 1;i++) seedNum *= 10; //10진수 자리수 만큼 곱하기
	int* num;  //각각의 숫자 자리수를 담기 위한 포인터[배열을 포인터에 배정할 예정 - 동적배열을 활용하기 위해]
	num = (int*)malloc(nSize * sizeof(int)); //메모리에 배열을 담기 위해 할당을 미리 해둠(nSize의 수 만큼 int형으로 할당 -> int형 배열 nSize만큼)

	for (int i = 0;i < nSize;i++) {
		num[i] = number / seedNum; //각 자리수의 숫자가 배열의 담김
		number %= seedNum; //첫번쨰 자리를 뺀 값을 number에 받음
		seedNum /= 10; //seed를 나누기 10을 해서 다음 번호의 숫자를 배열에 담을 수 있도록 함

		prtNumber(4 * i + x, y, num[i]); //출력
	}
}

int main()
{
	DrawNumbers(0, 10, 9876543210);
}
