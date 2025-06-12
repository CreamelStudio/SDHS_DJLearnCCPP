#pragma once

typedef struct ___Background
{
	//오브젝트 좌표, 크기
	int x, y;
	int w, h;
	int speedX, speedY; //배경 객체 움직이는 속도

	//이미지에 대한 좌표, 크기
	HDC hImgDC;
	HBITMAP hImgBM;
	int sx, sy;
	int ex, ey;
}BACKGROUND;

BACKGROUND* StartBackground(HDC hdc, int resource);
void Update(BACKGROUND* Obj);
void Render(HDC hdc, BACKGROUND* Obj);
void Release(BACKGROUND* Obj);

inline int getSpeedX(BACKGROUND* Obj) { return Obj->speedX; }
inline int getSpeedY(BACKGROUND* Obj) { return Obj->speedY; }
inline void setSpeedX(BACKGROUND* Obj, int speed) { Obj->speedX = speed; }
inline void setSpeedY(BACKGROUND* Obj, int speed) { Obj->speedY = speed; }

