#pragma once

int GdiLine(HDC hdc, int x1, int y1, int x2, int y2); //�� �׸��� �Լ�
void gdiStar(HDC hdc, int mx, int my, int scale = 1); //�� �׸��� �Լ�
void gdiPrintNumber(HDC hdc, int x, int y, int n); //���� 0~9���� ����ϴ� �Լ�
void gdiPrintNumbers(HDC hdc, int x, int y, unsigned long long int number); //���� unsigned long long int ���� �ȿ��� ���