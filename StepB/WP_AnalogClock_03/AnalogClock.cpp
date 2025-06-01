#include "pch.h"
#include "AnalogClock.h"

MYCLOCK* StartMyClock(int x, int y, int w, int h)
{
	MYCLOCK* Temp;
	Temp = (MYCLOCK*)malloc(sizeof(MYCLOCK));
	if (Temp == NULL) return NULL;

	Temp->hdc = NULL;
	Temp->iStyle = CBS_NUM1 | CBS_NUM3 | CBS_NEEDLE2;

	Temp->x = x;
	Temp->y = y;
	Temp->w = w;
	Temp->h = h;

	int cx = Temp->x + (Temp->w / 2);
	int cy = y + (h / 2);
	Temp->pHour = StartNeedle(cx, cy, 100, 10, RGB(0, 0, 0));
	Temp->pMin = StartNeedle(cx, cy, 160, 5, RGB(0, 0, 255));
	Temp->pSec = StartNeedle(cx, cy, 160, 1, RGB(255, 0, 0));

	return Temp;
}

void Update(MYCLOCK* object)
{
	switch (object->iStyle & 0xF000)
	{
	case CBS_RECT:
		Rectangle(object->hdc, object->x, object->y, object->x + object->w, object->y + object->h);
		break;
	case CBS_CIRCLE:
		Ellipse(object->hdc, object->x, object->y, object->x + object->w, object->y + object->h);
		break;
	}

	switch (object->iStyle & 0x00FF)
	{
	case CBS_NUM1:
		CBS_Num1(object->hdc, object->pMin->x, object->pMin->y, object->pMin->length);
		break;
	case CBS_NUM2:
		CBS_Num2(object->hdc, object->pMin->x, object->pMin->y, object->pMin->length);
		break;
	case CBS_NUM3:
		CBS_Num3(object->hdc, object->pMin->x, object->pMin->y, object->pMin->length);
		break;
	case CBS_NEEDLE1:
		CBS_Needle1(object->hdc, object->pMin->x, object->pMin->y, object->pMin->length);
	case CBS_NUM1 + CBS_NUM3:
		CBS_Num1(object->hdc, object->pMin->x, object->pMin->y, object->pMin->length);
		CBS_Num3(object->hdc, object->pMin->x, object->pMin->y, object->pMin->length - 20);
		break;
	case CBS_NUM2 + CBS_NEEDLE1:
		CBS_Needle1(object->hdc, object->pMin->x, object->pMin->y, object->pMin->length);
		CBS_Num2(object->hdc, object->pMin->x, object->pMin->y, object->pMin->length - 20);
		break;
	case CBS_NUM3 + CBS_NEEDLE2:
		CBS_Needle2(object->hdc, object->pMin->x, object->pMin->y, object->pMin->length);
		CBS_Num3(object->hdc, object->pMin->x, object->pMin->y, object->pMin->length + 10);
		break;
	case CBS_NUM1 + CBS_NUM3 + CBS_NEEDLE2:
		CBS_Num1(object->hdc, object->pMin->x, object->pMin->y, object->pMin->length - 20);
		CBS_Needle2(object->hdc, object->pMin->x, object->pMin->y, object->pMin->length);
		CBS_Num3(object->hdc, object->pMin->x, object->pMin->y, object->pMin->length + 10);
		break;
	}

	SetHDC(object->pHour, object->hdc);
	SetClock2PI(object->pHour, _CLOCK2PI::T12);
	SetTimeNum(object->pHour, object->st.wHour);
	Update(object->pHour);

	SetHDC(object->pMin, object->hdc);
	SetClock2PI(object->pMin, _CLOCK2PI::T60);
	SetTimeNum(object->pMin, object->st.wMinute);
	Update(object->pMin);

	SetHDC(object->pSec, object->hdc);
	SetClock2PI(object->pSec, _CLOCK2PI::T60);
	SetTimeNum(object->pSec, object->st.wSecond);
	Update(object->pSec);
}

void Release(MYCLOCK* object)
{
	Release(object->pSec);
	Release(object->pMin);
	Release(object->pHour);

	if (object == NULL) return;
	free(object);
	object = NULL;
}