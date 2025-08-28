#include "LineAlgebra.h"
#include <Windows.h>
#include <stdio.h>
//Pointer를 활용한 swap
void pSwap(int* a, int* b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

//Reference Pointer를 활용한 swap
void rSwap(int& a, int& b)
{
	int temp;
	temp = a;
	a = b;
	b = temp;
}

namespace LineAlgebra
{
	void gotoxy(int x, int y) {
		COORD pos;
		pos.X = x;   // 열 (가로)
		pos.Y = y;   // 행 (세로)
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	}

	void Dot(int x, int y)
	{
		//점을 찎음
		gotoxy(x, y);
		printf("*");
	}

	//수평선 함수
	void HLine(int x1, int x2, int y)
	{
		if (x1 > x2) pSwap(&x1, &x2);
		for (int x = x1; x <= x2; x++)
		{
			Dot(x, y);
		}
	}

	//수직선 함수
	void VLine(int x, int y1, int y2)
	{
		if (y1 > y2) rSwap(y1, y2);
		for (int y = y1; y <= y2; y++)
		{
			Dot(x, y);
		}
	}

	//속이 빈 사각형 그리기 함수
	void Rect(int x1, int y1, int x2, int y2)
	{
		LineAlgebra::HLine(x1, x2, y1);
		LineAlgebra::VLine(x1, y1, y2);
		LineAlgebra::HLine(x1, x2, y2);
		LineAlgebra::VLine(x2, y1, y2);
	}

	//두점을 알 때 직선그리기
	void TwoPointLine(int x1, int y1, int x2, int y2)
	{
		float m; //기울기 변수
		int x = x1, y = y1; //점 좌표

		//수직선 예외 처리
		if (x1 == x2) //(단, x1 != x2)
		{
			LineAlgebra::VLine(x, y1, y2);
			return;
		}
		//수평선 예외 처리
		if (y1 == y2) //(단, y1 != y2)
		{
			LineAlgebra::HLine(x1, x2, y);
			return;
		}

		int tempX = x1;
		int tempY = y1;

		m = (float)(y2 - y1) / (x2 - x1); //기울기 구하는 공식
		//if((m < 1.0f) && (m > -1.0f)) //x축을 독립축으로 둘 때
		if ((-1.0 < m) && (m < 1.0f)) //-1 < m < 1
		{
			if (x1 > x2)
			{
				for (x = x1; x > x2; x--)
				{
					y = m * (x - tempX) + tempY; //직선의 방정식
					Dot(x, y);
				}
			}
			else //x1 < x2
			{
				for (x = x1; x <= x2; x++)
				{
					y = m * (x - tempX) + tempY; //직선의 방정식
					Dot(x, y);
				}
			}
		}
		else //y축을 독립축으로 둘 때 //m < -1 , m > 1
		{
			if (y1 > y2)
			{
				for (y = y1; y > y2; y--)
				{
					x = (1 / m) * (y - tempY) + tempX; //직선의 방정식
					Dot(x, y);
				}
			}
			else //y1 < y2
			{
				for (y = y1; y <= y2; y++)
				{
					x = (1 / m) * (y - tempY) + tempX; //직선의 방정식
					Dot(x, y);
				}
			}
		}
	}

	//점진적 직선그리기
	void GradualLine(int x1, int y1, int x2, int y2)
	{
		int x = x1, y = y1; //점 좌표
		//수직선 예외 처리
		if (x1 == x2) //(단, x1 != x2)
		{
			LineAlgebra::VLine(x, y1, y2);
			return;
		}
		//수평선 예외 처리
		if (y1 == y2) //(단, y1 != y2)
		{
			LineAlgebra::HLine(x1, x2, y);
			return;
		}

		float m = (float)(y2 - y1) / (x2 - x1); //기울기 구하는 공식
		if ((-1.0 < m) && (m < 1.0f)) //-1 < m < 1
		{
			y = y1;
			if (x1 > x2) pSwap(&x1, &x2);
			for (x = x1; x <= x2; x++) //독립축 x
			{
				y = y + m;
				Dot(x, y);
			}
		}
		else
		{
			x = x2;
			if (y1 > y2) rSwap(y1, y2);
			float n = (1 / m);
			for (y = y1; y <= y2; y++) //독립축 y
			{
				x = x + n;
				Dot(x, y);
			}
		}

	}

}