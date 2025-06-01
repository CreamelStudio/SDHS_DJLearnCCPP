#pragma once

#define CBS_RECT 0x1000
#define CBS_CIRCLE 0x2000
#define CBS_NUM1 0x0001
#define CBS_NUM2 0x0002
#define CBS_NUM3 0x0004
#define CBS_NEEDLE1 0x0010
#define CBS_NEEDLE2 0x0020

typedef struct __analogclock
{
	HDC hdc;
	SYSTEMTIME st;

	int iStyle;
	
	int x, y;
	int w, h;
	NEEDLE* pHour;
	NEEDLE* pMin;
	NEEDLE* pSec;
}MYCLOCK;

MYCLOCK* StartMyClock(int x, int y, int w, int h);
void Update(MYCLOCK* object);
void Release(MYCLOCK* object);

inline void SetTime(MYCLOCK* object, SYSTEMTIME st) { object->st = st; }
inline void SetHDC(MYCLOCK* object, HDC hdc) { object->hdc = hdc; }
inline void SetBK(MYCLOCK* object, int istyle) { object->iStyle = istyle; }