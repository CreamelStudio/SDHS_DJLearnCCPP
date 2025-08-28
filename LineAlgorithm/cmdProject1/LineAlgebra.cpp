#include "LineAlgebra.h"
#include <Windows.h>
#include <stdio.h>
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

	//������ �� �� �����׸���
	void TwoPointLine(int x1, int y1, int x2, int y2)
	{
		float m; //���� ����
		int x = x1, y = y1; //�� ��ǥ

		//������ ���� ó��
		if (x1 == x2) //(��, x1 != x2)
		{
			LineAlgebra::VLine(x, y1, y2);
			return;
		}
		//���� ���� ó��
		if (y1 == y2) //(��, y1 != y2)
		{
			LineAlgebra::HLine(x1, x2, y);
			return;
		}

		int tempX = x1;
		int tempY = y1;

		m = (float)(y2 - y1) / (x2 - x1); //���� ���ϴ� ����
		//if((m < 1.0f) && (m > -1.0f)) //x���� ���������� �� ��
		if ((-1.0 < m) && (m < 1.0f)) //-1 < m < 1
		{
			if (x1 > x2)
			{
				for (x = x1; x > x2; x--)
				{
					y = m * (x - tempX) + tempY; //������ ������
					Dot(x, y);
				}
			}
			else //x1 < x2
			{
				for (x = x1; x <= x2; x++)
				{
					y = m * (x - tempX) + tempY; //������ ������
					Dot(x, y);
				}
			}
		}
		else //y���� ���������� �� �� //m < -1 , m > 1
		{
			if (y1 > y2)
			{
				for (y = y1; y > y2; y--)
				{
					x = (1 / m) * (y - tempY) + tempX; //������ ������
					Dot(x, y);
				}
			}
			else //y1 < y2
			{
				for (y = y1; y <= y2; y++)
				{
					x = (1 / m) * (y - tempY) + tempX; //������ ������
					Dot(x, y);
				}
			}
		}
	}

	//������ �����׸���
	void GradualLine(int x1, int y1, int x2, int y2)
	{
		int x = x1, y = y1; //�� ��ǥ
		//������ ���� ó��
		if (x1 == x2) //(��, x1 != x2)
		{
			LineAlgebra::VLine(x, y1, y2);
			return;
		}
		//���� ���� ó��
		if (y1 == y2) //(��, y1 != y2)
		{
			LineAlgebra::HLine(x1, x2, y);
			return;
		}

		float m = (float)(y2 - y1) / (x2 - x1); //���� ���ϴ� ����
		if ((-1.0 < m) && (m < 1.0f)) //-1 < m < 1
		{
			y = y1;
			if (x1 > x2) pSwap(&x1, &x2);
			for (x = x1; x <= x2; x++) //������ x
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
			for (y = y1; y <= y2; y++) //������ y
			{
				x = x + n;
				Dot(x, y);
			}
		}

	}

}