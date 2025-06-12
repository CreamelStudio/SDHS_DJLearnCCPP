#include "pch.h"
#include "Dino.h"
#include "pch.h"
#include "BackGround.h"

extern HINSTANCE hInst;
extern HWND ghWnd;

DINO* StartDino(HDC hdc, int resource)
{
	DINO* Temp;
	Temp = (DINO*)malloc(sizeof(DINO));

	Temp->hImgDC = CreateCompatibleDC(hdc);
	Temp->hImgBM = LoadBitmap(hInst, MAKEINTRESOURCE(resource));
	SelectObject(Temp->hImgDC, Temp->hImgBM);

	Temp->x = 0;	Temp->y = 205;
	Temp->w = 40;	Temp->h = 50;

	Temp->sx = 0;	Temp->sy = 0;
	Temp->ex = 79; Temp->ey = 92;

	setJump(Temp, false);

	return Temp;
}

void Update(DINO* Obj)
{
	if (getJump(obj)) {
		obj->y = 170;
	}
	else {
		obj.y = 210;
	}
}

void Render(HDC hdc, DINO* Obj)
{
	//BitBlt(hdc, Obj->x, Obj->y, Obj->w, Obj->h, Obj->hImgDC, Obj->sx, Obj->sy, SRCCOPY);
	TransparentBlt(hdc, Obj->x, Obj->y, Obj->w, Obj->h, Obj->hImgDC, Obj->sx, Obj->sy, Obj->ex - Obj->sx, Obj->ey - Obj->sy, RGB(255, 255, 255));
}

void Release(DINO* Obj)	
{
	DeleteObject(Obj->hImgBM);
	ReleaseDC(ghWnd, Obj->hImgDC);
	if (Obj != NULL)	free(Obj);
}