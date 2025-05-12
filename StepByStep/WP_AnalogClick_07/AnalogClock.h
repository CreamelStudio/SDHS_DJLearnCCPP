#pragma once
//Typedef struct -> class



typedef struct __analogclock
{
	HDC hdc;
	SYSTEMTIME st;

	int iStyle;

	int x, y; //시계 좌표
	int w, h; //시계 크기

	NEEDLE* pHour; //시침
	NEEDLE* pMin; //분침
	NEEDLE* pSec; //초침
}MYCLOCK;

MYCLOCK* StartMyClock(int x, int y, int w, int h);
void Update(MYCLOCK* object);
void Release(MYCLOCK* object);

inline void Set(MYCLOCK* object, SYSTEMTIME st) { object->st = st; };
inline void SetTime(MYCLOCK* object, SYSTEMTIME st) { object->st = st; };
inline void SetHDC(MYCLOCK* object, HDC hdc) { object->hdc = hdc; };
inline void SetHDC(NEEDLE* object, HDC hdc) { object->hdc = hdc; };
inline void SetBK(MYCLOCK* object, int istyle) {object->iStyle = istyle}