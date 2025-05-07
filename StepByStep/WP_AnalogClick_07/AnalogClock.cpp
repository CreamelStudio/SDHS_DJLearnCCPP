#include "pch.h"
#include "AnalogClock.h"

MYCLOCK* StartMyClick(int x, int y, int w, int h) {
	MYCLOCK* Temp;
	Temp = (MYCLOCK*)malloc(sizeof(MYCLOCK));
	if (Temp == NULL) return NULL;

	Temp->x = x;
	Temp->y = y;
	Temp->w = w;
	Temp->h = h;

	int cx = (Temp->w - Temp->x) / 2;
	int cy = (h - y) / 2;

	Temp->pHour = StartNeedle(cx, cy, 100, 5, RGB(255,0,0));
	Temp->pHour = StartNeedle(cx, cy, 100, 5, RGB(0, 255, 0));
	Temp->pHour = StartNeedle(cx, cy, 100, 5, RGB(0, 0, 255));

	return Temp;
}
void Update(MYCLOCK* object) {

}
void Release(MYCLOCK* object) {
	if (object == NULL) return;
	free(object);
	object = NULL;
}