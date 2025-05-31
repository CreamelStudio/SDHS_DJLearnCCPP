#pragma once
enum _CLOCK2PI{T12, T24, T60}; //12 = 360, 24 = 360, 60 = 360

typedef struct __timeneedle {
	HDC hdc;
	_CLOCK2PI c2pi;
	int timeNum;

	int x, y;
	int length;

	HPEN color;
}NEEDLE;

NEEDLE* StartNeedle(int x, int y, int length, int thick, COLORREF color);
void Update(NEEDLE* object);
void Release(NEEDLE* object);

inline void SetTimeNum(NEEDLE* object, int num) { object->timeNum = num; }
inline void SetClock2PI(NEEDLE* object, _CLOCK2PI c2pi) { object->c2pi = c2pi; }
inline void SetGDC(NEEDLE* object, HDC hdc) { object->hdc = hdc; }