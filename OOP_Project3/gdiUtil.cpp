#include "pch.h"
#include "gdiUtil.h"

//Desc : 색지정 큰 점 그리기
//Parameter : x , y 좌표, rgb색지정 RGB(r,g,b)매크로 사용
void DrawBigDot(int x, int y, COLORREF rgb)
{
    gdi->DrawDot(x + 0, y + 0, rgb);
    gdi->DrawDot(x + 0, y + 1, rgb);
    gdi->DrawDot(x + 0, y - 1, rgb);
    gdi->DrawDot(x + 1, y + 0, rgb);
    gdi->DrawDot(x - 1, y + 0, rgb);
    gdi->DrawDot(x + 1, y + 1, rgb);
    gdi->DrawDot(x - 1, y + 1, rgb);
    gdi->DrawDot(x + 1, y - 1, rgb);
    gdi->DrawDot(x - 1, y - 1, rgb);
}

void DrawBigBigDot(int x, int y, COLORREF rgb)
{
    DrawBigDot(x + 0, y + 0, rgb);
    DrawBigDot(x + 0, y + 0, rgb);
    DrawBigDot(x + 0, y + 2, rgb);
    DrawBigDot(x + 0, y - 2, rgb);
    DrawBigDot(x + 2, y + 0, rgb);
    DrawBigDot(x - 2, y + 0, rgb);
    DrawBigDot(x + 2, y + 2, rgb);
    DrawBigDot(x - 2, y + 2, rgb);
    DrawBigDot(x + 2, y - 2, rgb);
    DrawBigDot(x - 2, y - 2, rgb);
}

//Desc : 노란색 큰 점 그리기
//Parameter : x , y 좌표
void DrawYellowDot(int x, int y)
{
    gdi->DrawDot((int)(x / 2 + 0.5) + 0, (int)(y / 2 + 0.5) + 0, RGB(255, 255, 0));
    gdi->DrawDot((int)(x / 2 + 0.5) + 0, (int)(y / 2 + 0.5) + 2, RGB(255, 255, 0));
    gdi->DrawDot((int)(x / 2 + 0.5) + 0, (int)(y / 2 + 0.5) - 2, RGB(255, 255, 0));
    gdi->DrawDot((int)(x / 2 + 0.5) + 2, (int)(y / 2 + 0.5) + 0, RGB(255, 255, 0));
    gdi->DrawDot((int)(x / 2 + 0.5) - 2, (int)(y / 2 + 0.5) + 0, RGB(255, 255, 0));
    gdi->DrawDot((int)(x / 2 + 0.5) + 2, (int)(y / 2 + 0.5) + 2, RGB(255, 255, 0));
    gdi->DrawDot((int)(x / 2 + 0.5) - 2, (int)(y / 2 + 0.5) + 2, RGB(255, 255, 0));
    gdi->DrawDot((int)(x / 2 + 0.5) + 2, (int)(y / 2 + 0.5) - 2, RGB(255, 255, 0));
    gdi->DrawDot((int)(x / 2 + 0.5) - 2, (int)(y / 2 + 0.5) - 2, RGB(255, 255, 0));
}

