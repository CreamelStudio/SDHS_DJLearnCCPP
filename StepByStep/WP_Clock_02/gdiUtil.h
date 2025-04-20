#pragma once

int GdiLine(HDC hdc, int x1, int y1, int x2, int y2); //선 그리는 함수
void gdiStar(HDC hdc, int mx, int my, int scale = 1); //별 그리는 함수
void gdiPrintNumber(HDC hdc, int x, int y, int n); //숫자 0~9까지 출력하는 함수
void gdiPrintNumbers(HDC hdc, int x, int y, unsigned long long int number); //숫자 unsigned long long int 범위 안에서 출력