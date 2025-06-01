#include "pch.h"
#include "gdiUtil.h"
#include <math.h>

//==========================================
// Desc : Windows GDI 선을 그리는 함수
// Parameter : HDC, 시작점(x1, y1), 끝점(x2, y2)
// Author : DJ__KIM (email : cosmosun@sdh.hs.kr)
// Date : 2025-04-14  
#define PI 3.141592f
#define RAD(x) PI/180.0f*(x)

void gdiLine(HDC hdc, int x1, int y1, int x2, int y2)
{
    MoveToEx(hdc, x1, y1, NULL);
    LineTo(hdc, x2, y2);
}

void gdiRotLineCW(HDC hdc, int CenterX, int CenterY, int NeddleLength, float theta)
{
    int NeddleX = cos(theta) * NeddleLength - sin(theta) * NeddleLength;
    int NeddleY = cos(theta) * NeddleLength + sin(theta) * NeddleLength;
    gdiLine(hdc, CenterX, CenterY, NeddleX + CenterX, NeddleY + CenterY);
}

void CBS_Needle1(HDC hdc, int cx, int cy, int length)
{
    for (int i = 0; i < 360; i += 30)
    {
        float fTheta = RAD((float)((i - 135.f)));
        int x1 = (int)((cos(fTheta) * length) - (sin(fTheta) * length));
        int y1 = (int)((sin(fTheta) * length) + (cos(fTheta) * length));
        int x2 = (int)((cos(fTheta) * (length - 10)) - (sin(fTheta) * (length - 10)));
        int y2 = (int)((sin(fTheta) * (length - 10)) + (cos(fTheta) * (length - 10)));

        gdiLine(hdc, cx + x1, cy + y1, cx + x2, cy + y2);
    }
}