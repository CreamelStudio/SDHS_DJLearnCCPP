#include "pch.h"
#include "gdiUtil.h"

#define PI 3.141592f
#define RAD(x) PI/180.0f*(x)

//==========================================
// Desc : Windows GDI 선을 그리는 함수
// Parameter : HDC, 시작점(x1, y1), 끝점(x2, y2)
// Author : DJ__KIM (email : cosmosun@sdh.hs.kr)
// Date : 2025-04-14  
void gdiLine(HDC hdc, int x1, int y1, int x2, int y2)
{
    MoveToEx(hdc, x1, y1, NULL);
    LineTo(hdc, x2, y2);
}

//==========================================
// Desc : Windows GDI 별을 그리는 함수
// Parameter : HDC, 좌표(mx, my), 크기(scale)
// Author : DJ__KIM (email : cosmosun@sdh.hs.kr)
// Date : 2025-04-14     
void gdiStar(HDC hdc, int mx, int my, int scale)
{
    MoveToEx(hdc,   mx + 0 * scale,     my + -10 * scale, NULL);
    LineTo(hdc,     mx + 6 * scale,     my + 8 * scale);
    LineTo(hdc,     mx + -10 * scale,   my + -3 * scale);
    LineTo(hdc,     mx + 10 * scale,    my + -3 * scale);
    LineTo(hdc,     mx + -6 * scale,    my + 8 * scale);
    LineTo(hdc,     mx + 0 * scale,     my + -10 * scale);
}

void CBS_Num1(HDC hdc, int cx, int cy, int length) {
	for (int i = 0, j = 0; i < 360; i += 30, j++) {
        float fTheta = RAD((float)((i - 135.f)));
		int x = (int)(cos(fTheta) * length) - (sin(fTheta) * length);
		int y = (int)(sin(fTheta) * length) + (cos(fTheta) * length);
        TCHAR strTemp[3] = L"";
        wsprintf(strTemp, L"%2d", j == 0 ? 12 : j);
		TextOut(hdc, cx + x - 10, cy + y - 10, strTemp, lstrlen(strTemp));
	}
}

void CBS_Num2(HDC hdc, int cx, int cy, int length) {
    for (int i = 0, j = 0; j < 360; i += 90, j += 3) {
		float fTheta = RAD((float)((i - 135.f)));
		int x = (int)(cos(fTheta) * length) - (sin(fTheta) * length);
		int y = (int)(sin(fTheta) * length) + (cos(fTheta) * length);
		TCHAR strTemp[3] = L"";
		wsprintf(strTemp, L"%2d", j == 0 ? 12 : j);
		TextOut(hdc, cx + x - 10, cy + y - 10, strTemp, lstrlen(strTemp));
    }
}

void CBS_Num3(HDC hdc, int cx, int cy, int length) {
	for (int i = 0, j = 0; j < 360; i += 6, j++) {
		float fTheta = RAD((float)((i - 135.f)));
		int x = (int)(cos(fTheta) * length) - (sin(fTheta) * length);
		int y = (int)(sin(fTheta) * length) + (cos(fTheta) * length);
		TCHAR strTemp[3] = L"";
		wsprintf(strTemp, L"%2d", j);
		TextOut(hdc, cx + x - 10, cy + y - 10, strTemp, lstrlen(strTemp));
	}
}

void CBS_Needle1(HDC hdc, int cx, int cy, int length) {
	for (int i = 0;i < 360;i += 30) {
		float fTheta = RAD((float)((i - 135.f)));

		int x1 = (int)((cos(fTheta) * length) - (sin(fTheta) * length));
		int y1 = (int)(sin(fTheta) * length) + (cos(fTheta) * length);
		int x2 = (int)((cos(fTheta) * (length - 10)) - (sin(fTheta) * (length - 10)));
		int y2 = (int)((sin(fTheta) * (length - 10)) + (cos(fTheta) * (length - 10)));

		gdiLine(hdc, cx + x1, cy + y1, cx + x2, cy + y2);
	}
}

void CBS_Needle2(HDC hdc, int cx, int cy, int length) {
	for (int i = 0;i < 360;i += 6) {
		float fTheta = RAD((float)((i - 135.f)));
		int x1 = (int)((cos(fTheta) * length) - (sin(fTheta) * length));
		int y1 = (int)(sin(fTheta) * length) + (cos(fTheta) * length);
		int x2 = (int)((cos(fTheta) * (length - 10)) - (sin(fTheta) * (length - 10)));
		int y2 = (int)((sin(fTheta) * (length - 10)) + (cos(fTheta) * (length - 10)));
		gdiLine(hdc, cx + x1, cy + y1, cx + x2, cy + y2);
	}
}