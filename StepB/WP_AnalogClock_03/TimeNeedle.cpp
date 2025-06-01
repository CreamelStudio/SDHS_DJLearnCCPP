#include "pch.h"
#include "TimeNeedle.h"

NEEDLE* StartNeedle(int x, int y, int length, int thick, COLORREF rgb)
{
	NEEDLE* Temp;
	Temp = (NEEDLE*)malloc(sizeof(NEEDLE));
	if (Temp == NULL) return NULL;

	Temp->hdc = NULL;
	Temp->c2pi = _CLOCK2PI::T12;

	Temp->x = x;
	Temp->y = y;
	Temp->length = length;
	Temp->color = CreatePen(PS_SOLID, thick, rgb);

	return Temp;
}

void Update(NEEDLE* object)
{
	float fTheta = 0.f;

	switch (object->c2pi)
	{
	case _CLOCK2PI::T12:
		fTheta = RAD((float)((object->timeNum - 4.5) * 30.0f));
		break;
	case _CLOCK2PI::T60:
		fTheta = RAD((float)((object->timeNum - 22.5) * 6.0f));
		break;
	}

	HPEN oldPen = (HPEN)SelectObject(object->hdc, object->color);
	gdiRotLineCW(object->hdc, object->x, object->y, object->length, fTheta);
	SelectObject(object->hdc, oldPen);
}

void Release(NEEDLE* object)
{
	DeleteObject(object->color);
	if (object == NULL) return;
	free(object);
	object = NULL;
}