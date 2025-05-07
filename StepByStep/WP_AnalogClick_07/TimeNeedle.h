#pragma once
typedef struct __timeneedle {
	int x, y;
	int length;
	COLORREF color;
	int thick;
}NEEDLE;

NEEDLE* StartNeedle(int x, int y, int length, int thick, COLORREF color);
void Update(NEEDLE* object);
void Release(NEEDLE* object);