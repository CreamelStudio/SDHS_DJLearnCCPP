#pragma once

#define PI 3.141592f
#define RAD(x) PI/180.0f*(x)

void gdiLine(HDC hdc, int x1, int y1, int x2, int y2); //선그리는함수
void gdiStar(HDC hdc, int mx, int my, int scale = 1); //별그리는함수
void CBS_Num1(HDC hdc, int cx, int cy, int length);
void CBS_Num2(HDC hdc, int cx, int cy, int length);
void CBS_Num3(HDC hdc, int cx, int cy, int length);
void CBS_Needle1(HDC hdc, int cx, int cy, int length);
void CBS_Needle2(HDC hdc, int cx, int cy, int length);