#pragma once
class Clock
{
};

typedef struct __CLOCKDATA
{
	HDC hdc;

	int x, y;
	int width, height;
	float rotationA, rotationB;
	HPEN normalPen, colorA, colorB;
}CLOCKDATA;

CLOCKDATA* CreateClockData(int x, int y, int width, int height, float rotationA, float rotationB, COLORREF colorA, COLORREF colorB, float thick);
void Update(CLOCKDATA* object);
void Draw(CLOCKDATA* object, HDC hdc);
void Update(CLOCKDATA* object, float rotationA, float rotationB);
inline void SetHDC(CLOCKDATA* object, HDC hdc) { object->hdc = hdc; }