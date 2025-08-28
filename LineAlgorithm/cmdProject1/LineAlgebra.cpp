#include "LineAlgebra.h"
#include <Windows.h>
#include <stdio.h>

#include <cmath>   // round, abs 같은 수학 함수
#include <algorithm> // std::swap

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

    // 두 점을 알 때 직선 그리기
    void TwoPointLine(int x1, int y1, int x2, int y2)
    {
        float m; // 기울기 변수
        int x = x1, y = y1; // 점 좌표

        // 수직선 예외 처리
        if (x1 == x2)
        {
            LineAlgebra::VLine(x1, y1, y2);
            return;
        }
        // 수평선 예외 처리
        if (y1 == y2)
        {
            LineAlgebra::HLine(x1, x2, y1);
            return;
        }

        int tempX = x1;
        int tempY = y1;

        m = (float)(y2 - y1) / (x2 - x1); // 기울기 구하는 공식
        if ((-1.0f < m) && (m < 1.0f)) // -1 < m < 1 (x축 기준)
        {
            if (x1 > x2) std::swap(x1, x2);

            for (x = x1; x <= x2; x++)
            {
                y = (int)round(m * (x - tempX) + tempY); // 정수 보정
                Dot(x, y);
            }
        }
        else // |m| >= 1 (y축 기준)
        {
            if (y1 > y2) std::swap(y1, y2);

            for (y = y1; y <= y2; y++)
            {
                x = (int)round((1.0f / m) * (y - tempY) + tempX); // 정수 보정
                Dot(x, y);
            }
        }
    }


    // 점진적 직선 그리기 (DDA 알고리즘)
    void GradualLine(int x1, int y1, int x2, int y2)
    {
        int x = x1, y = y1;

        // 수직선 예외 처리
        if (x1 == x2)
        {
            LineAlgebra::VLine(x1, y1, y2);
            return;
        }
        // 수평선 예외 처리
        if (y1 == y2)
        {
            LineAlgebra::HLine(x1, x2, y1);
            return;
        }

        float m = (float)(y2 - y1) / (x2 - x1); // 기울기 구하는 공식

        if ((-1.0f < m) && (m < 1.0f)) // -1 < m < 1 → x축 독립
        {
            if (x1 > x2) std::swap(x1, x2);

            float yf = (float)y1; // y를 float으로 따로 둠
            Dot(x1, y1); // 시작점 찍기

            for (x = x1 + 1; x <= x2; x++)
            {
                yf += m;
                Dot(x, (int)round(yf));
            }
        }
        else // |m| >= 1 → y축 독립
        {
            if (y1 > y2) std::swap(y1, y2);

            float xf = (float)x1;
            float n = 1.0f / m;
            Dot(x1, y1); // 시작점 찍기

            for (y = y1 + 1; y <= y2; y++)
            {
                xf += n;
                Dot((int)round(xf), y);
            }
        }
    }


}