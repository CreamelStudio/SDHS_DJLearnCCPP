#include "pch.h"
#include "gdiUtil.h"

//=============================================
// Desc : windois GDI 선을 그리는 함수
// Parameter : HDC, 시작점(x1,y1),끝점(x2,y2)
// Author :JungHwan_Kim (eamill :sdh240204@sdh.hs.kr)
// Date : 2025-04-14
int GdiLine(HDC hdc, int x1,int y1,int x2,int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2 , y2);

	return 0;
}

//=============================================
// Desc : windois GDI 별을 그리는 함수
// Parameter : HDC, 좌표(mx,my),크기(scale)
// Author :JungHwan_Kim (eamill :sdh240204@sdh.hs.kr)
// Date : 2025-04-14

void gdiStar(HDC hdc, int mx, int my,int scale)
{
	MoveToEx(hdc, mx + 0   * scale,    my + -10 * scale, NULL);
	LineTo(hdc,   mx + 6   * scale,    my + 8	* scale);
	LineTo(hdc,   mx + -10 * scale,	   my + -3  * scale);
	LineTo(hdc,   mx + 10  * scale,    my + -3  * scale);
	LineTo(hdc,   mx + -6  * scale,    my + 8	* scale);
	LineTo(hdc,   mx + 0   * scale,    my + -10 * scale);
}

