#include "pch.h"
#include "TimeNeedle.h"

NEEDLE* StartNeedle(int x, int y, int length, int thick,COLORREF color) {
	NEEDLE* Temp;
	Temp = (NEEDLE*)malloc(sizeof(NEEDLE));

	Temp->x = x;
	Temp->y = x;
	Temp->length = length;
	Temp->thick = thick;
	Temp->color = color;

	return Temp;
}
void Update(NEEDLE* object, HDC hdc ) {
	float Sectheta = RAD((float)((gST.wSecond - 22.5) * 6.0f));
	gdiRotLineCW(hdc, object->pSec->x, object->pSec->x, object->pSec->x, Sectheta);
	float Sectheta = RAD((float)((gST.wMinute - 22.5) * 6.0f));
	gdiRotLineCW(hdc, object->pMin->x, object->pMin->x, object->pMin->x, Sectheta);
	float Sectheta = RAD((float)((gST.wHour - 4.5) * 6.0f));
	gdiRotLineCW(hdc, object->pHour->x, object->pHour->x, object->pHour->x, Sectheta);
}
void Release(NEEDLE* object) {
	if (object == NULL) return;
	free(object);
	object = NULL;
}