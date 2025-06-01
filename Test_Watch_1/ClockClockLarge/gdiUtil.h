#pragma once

void gdiLine(HDC hdc, int x1, int y1, int x2, int y2); //선그리는함수
void gdiRotLineCW(HDC hdc, int CenterX, int CenterY, int NeddleLength, float theta); //시계침 그리는 함수
void CBS_Needle1(HDC hdc, int cx, int cy, int length);
void CBS_Needle2(HDC hdc, int cx, int cy, int length);