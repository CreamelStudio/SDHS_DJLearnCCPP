#pragma once

typedef struct ___Dino
{
	//오브젝트 좌표, 크기
	int x, y;
	int w, h;

	//이미지에 대한 좌표, 크기
	HDC hImgDC;
	HBITMAP hImgBM;
	int sx, sy;
	int ex, ey;

	bool bIsJump;
}DINO;

DINO* StartDino(HDC hdc, int resource);
void Update(DINO* Obj);
void Render(HDC hdc, DINO* Obj);
void Release(DINO* Obj);

inline bool getJump(DINO* obj) { return obj->bIsJump; };
inline void setJump(DINO* obj, bool bJump) { obj->bIsJump = bJump; };