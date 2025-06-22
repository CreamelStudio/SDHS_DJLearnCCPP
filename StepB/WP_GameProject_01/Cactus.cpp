#include "pch.h"
#include "Cactus.h"
#include "BackGround.h"

extern HINSTANCE hInst;
extern HWND ghWnd;


CACTUS* StartCactus(HDC hdc, int resource)
{
	CACTUS* Temp;
	Temp = (CACTUS*)malloc(sizeof(CACTUS));

	Temp->hImgDC = CreateCompatibleDC(hdc);
	Temp->hImgBM = LoadBitmap(hInst, MAKEINTRESOURCE(resource));
	SelectObject(Temp->hImgDC, Temp->hImgBM);

	Temp->x = 40;	Temp->y = 205;
	Temp->w = 39;	Temp->h = 76;

	Temp->sx = 0;	Temp->sy = 0;
	Temp->ex = 79; Temp->ey = 92;

	setSpeedX(Temp, -2);

	setJump(Temp, false);

	return Temp;
}

void Update(CACTUS* obj)
{
	setX(obj, getX(obj) + getSpeedX(obj));

	if (obj->x < 0 - obj->w) {
		setX(obj, rand() % 5 * 100 + 640);
	}
}

void Render(HDC hdc, CACTUS* Obj)
{
	//BitBlt(hdc, Obj->x, Obj->y, Obj->w, Obj->h, Obj->hImgDC, Obj->sx, Obj->sy, SRCCOPY);
	TransparentBlt(hdc, Obj->x, Obj->y, Obj->w, Obj->h, Obj->hImgDC, Obj->sx, Obj->sy, Obj->ex - Obj->sx, Obj->ey - Obj->sy, RGB(255, 255, 255));
}

void Release(CACTUS* Obj)
{
	DeleteObject(Obj->hImgBM);
	ReleaseDC(ghWnd, Obj->hImgDC);
	if (Obj != NULL)	free(Obj);
}