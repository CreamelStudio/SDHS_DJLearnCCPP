#pragma once

void gdiLine(HDC hdc, int x1, int y1, int x2, int y2); //선그리는함수
void gdiStar(HDC hdc, int mx, int my, int scale = 1); //별그리는함수
void gdiRotLineCW(HDC hdc, int CenterX, int CenterY, int NeddleLength, float theta); // 시계만드는 함수