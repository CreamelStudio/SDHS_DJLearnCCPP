#include "LineAlgebra.h"
#include <Windows.h>
#include <stdio.h>

#include <cmath>   // round, abs ���� ���� �Լ�
#include <algorithm> // std::swap

//Pointer�� Ȱ���� swap
void pSwap(int* a, int* b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

//Reference Pointer�� Ȱ���� swap
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
		pos.X = x;   // �� (����)
		pos.Y = y;   // �� (����)
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	}

	void Dot(int x, int y)
	{
		//���� ����
		gotoxy(x, y);
		printf("*");
	}

	//���� �Լ�
	void HLine(int x1, int x2, int y)
	{
		if (x1 > x2) pSwap(&x1, &x2);
		for (int x = x1; x <= x2; x++)
		{
			Dot(x, y);
		}
	}

	//������ �Լ�
	void VLine(int x, int y1, int y2)
	{
		if (y1 > y2) rSwap(y1, y2);
		for (int y = y1; y <= y2; y++)
		{
			Dot(x, y);
		}
	}

	//���� �� �簢�� �׸��� �Լ�
	void Rect(int x1, int y1, int x2, int y2)
	{
		LineAlgebra::HLine(x1, x2, y1);
		LineAlgebra::VLine(x1, y1, y2);
		LineAlgebra::HLine(x1, x2, y2);
		LineAlgebra::VLine(x2, y1, y2);
	}

    // �� ���� �� �� ���� �׸���
    void TwoPointLine(int x1, int y1, int x2, int y2)
    {
        float m; // ���� ����
        int x = x1, y = y1; // �� ��ǥ

        // ������ ���� ó��
        if (x1 == x2)
        {
            LineAlgebra::VLine(x1, y1, y2);
            return;
        }
        // ���� ���� ó��
        if (y1 == y2)
        {
            LineAlgebra::HLine(x1, x2, y1);
            return;
        }

        int tempX = x1;
        int tempY = y1;

        m = (float)(y2 - y1) / (x2 - x1); // ���� ���ϴ� ����
        if ((-1.0f < m) && (m < 1.0f)) // -1 < m < 1 (x�� ����)
        {
            if (x1 > x2) std::swap(x1, x2);

            for (x = x1; x <= x2; x++)
            {
                y = (int)round(m * (x - tempX) + tempY); // ���� ����
                Dot(x, y);
            }
        }
        else // |m| >= 1 (y�� ����)
        {
            if (y1 > y2) std::swap(y1, y2);

            for (y = y1; y <= y2; y++)
            {
                x = (int)round((1.0f / m) * (y - tempY) + tempX); // ���� ����
                Dot(x, y);
            }
        }
    }


    // ������ ���� �׸��� (DDA �˰���)
    void GradualLine(int x1, int y1, int x2, int y2)
    {
        int x = x1, y = y1;

        // ������ ���� ó��
        if (x1 == x2)
        {
            LineAlgebra::VLine(x1, y1, y2);
            return;
        }
        // ���� ���� ó��
        if (y1 == y2)
        {
            LineAlgebra::HLine(x1, x2, y1);
            return;
        }

        float m = (float)(y2 - y1) / (x2 - x1); // ���� ���ϴ� ����

        if ((-1.0f < m) && (m < 1.0f)) // -1 < m < 1 �� x�� ����
        {
            if (x1 > x2) std::swap(x1, x2);

            float yf = (float)y1; // y�� float���� ���� ��
            Dot(x1, y1); // ������ ���

            for (x = x1 + 1; x <= x2; x++)
            {
                yf += m;
                Dot(x, (int)round(yf));
            }
        }
        else // |m| >= 1 �� y�� ����
        {
            if (y1 > y2) std::swap(y1, y2);

            float xf = (float)x1;
            float n = 1.0f / m;
            Dot(x1, y1); // ������ ���

            for (y = y1 + 1; y <= y2; y++)
            {
                xf += n;
                Dot((int)round(xf), y);
            }
        }
    }


}