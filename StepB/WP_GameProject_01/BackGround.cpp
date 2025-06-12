#include "pch.h"
#include "BackGround.h"

extern HINSTANCE hInst;
extern HWND ghWnd;

BACKGROUND* StartBackground(HDC hdc, int resource)
{ 
	BACKGROUND* Temp;
	Temp = (BACKGROUND*)malloc(sizeof(BACKGROUND));

	Temp->hImgDC = CreateCompatibleDC(hdc);
	Temp->hImgBM = LoadBitmap(hInst, MAKEINTRESOURCE(resource));
	SelectObject(Temp->hImgDC, Temp->hImgBM);

	Temp->x = 0;	Temp->y = 200;
	Temp->w = 640;	Temp->h = 100;

	Temp->sx = 0;	Temp->sy = 0;
	Temp->ex = 640; Temp->ey = 100;

	Temp->speedX += 1;
	setSpeedX(Temp, 1);
	Temp->speedY += 0;
	setSpeedY(Temp, 0);

	return Temp;
}

void Update(BACKGROUND* Obj)
{
	Obj->sx += Obj->speedX;
	if (Obj->sx >= 1200 - Obj->w)	Obj->sx = 0;
}

void Render(HDC hdc, BACKGROUND* Obj)
{
	BitBlt(hdc, Obj->x, Obj->y, Obj->w, Obj->h, 
		   Obj->hImgDC, Obj->sx, Obj->sy, SRCCOPY);
}

void Release(BACKGROUND* Obj)
{
	DeleteObject(Obj->hImgBM);
	ReleaseDC(ghWnd, Obj->hImgDC);
	if(Obj != NULL)	free(Obj);
}