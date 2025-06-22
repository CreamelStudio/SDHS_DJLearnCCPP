#pragma once

typedef struct ___Cactus
{
	//오브젝트 좌표, 크기
	int x, y;
	int w, h;

	//이미지에 대한 좌표, 크기
	HDC hImgDC;
	HBITMAP hImgBM;
	int sx, sy;
	int ex, ey;

	int speedX;

	bool bIsJump;
}CACTUS;

CACTUS* StartCactus(HDC hdc, int resource);
void Update(CACTUS* Obj);
void Render(HDC hdc, CACTUS* Obj);
void Release(CACTUS* Obj);

inline bool getJump(CACTUS* obj) { return obj->bIsJump; };
inline void setJump(CACTUS* obj, bool bJump) { obj->bIsJump = bJump; };

inline int getSpeedX(CACTUS* obj) { return obj->speedX; };
inline void setSpeedX(CACTUS* obj, int speedX) { obj->speedX = speedX; };

inline void setX(CACTUS* obj, int x) { obj->x = x; };
inline int getX(CACTUS* obj) { return obj->x; };