#include "pch.h"
#include "Clock.h"

#define PI 3.141592f
#define RAD(x) PI/180.0f*(x)

CLOCKDATA* CreateClockData(int x, int y, int width, int height, float rotationA, float rotationB, COLORREF colorA, COLORREF colorB, float thick) {
	CLOCKDATA* Temp;
	Temp = (CLOCKDATA*)malloc(sizeof(CLOCKDATA));
	if (Temp == NULL) return NULL;

	Temp->x = x;
	Temp->y = y;

	Temp->width = width;
	Temp->height = height;

	Temp->rotationA = rotationA;
	Temp->rotationB = rotationB;

	Temp->normalPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	Temp->colorA = CreatePen(PS_SOLID, thick, colorA);
	Temp->colorB = CreatePen(PS_SOLID, thick, colorB);

	return Temp;
}

void Update(CLOCKDATA* object, float rotationA, float rotationB) {
	float fThetaA = RAD((float)((rotationA - 135.f)));
	float fThetaB = RAD((float)((rotationB - 135.f)));
	object->rotationA = fThetaA;
	object->rotationB = fThetaB;
}

void Draw(CLOCKDATA* object, HDC hdc) {
	if (object == NULL) return;

	// Draw the clock hands
	HPEN oldPenNormal = (HPEN)SelectObject(object->hdc, object->normalPen);
	Ellipse(object->hdc, object->x - object->width / 2, object->y - object->height / 2, object->x + object->width / 2, object->y + object->height / 2);

	HPEN oldPenA = (HPEN)SelectObject(object->hdc, object->colorA);
	gdiRotLineCW(object->hdc, object->x, object->y, object->width / 3, object->rotationA);
	HPEN oldPenB = (HPEN)SelectObject(object->hdc, object->colorB);
	gdiRotLineCW(object->hdc, object->x, object->y, object->width / 3, object->rotationB);

	SelectObject(object->hdc, oldPenA);
	SelectObject(object->hdc, oldPenB);
}

void Relase(CLOCKDATA* object) {
	if (object == NULL) return;

	DeleteObject(object->colorA);
	DeleteObject(object->colorB);
	free(object);
	object = NULL;
}