#pragma once

void gdiLine(HDC hdc, int x1, int y1, int x2, int y2); //선그리는함수
void gdiStar(HDC hdc, int mx, int my, int scale = 1); //별그리는함수
void gdiPrintNumber(HDC hdc, int x, int y, int n);//숫자0~9 출력하는 함수
void gdiPrintNumbers(HDC hdc, int x, int y, unsigned int number);//숫자INT_MAX범위안에서 출력