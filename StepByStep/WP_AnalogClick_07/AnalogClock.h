#pragma once
//Typedef struct -> class



typedef struct __analogclock
{
	int x, y; //시계 좌표
	int w, h; //시계 크기

	NEEDLE* pHour; //시침
	NEEDLE* pMin; //분침
	NEEDLE* pSec; //초침

	SYSTEMTIME st;
}MYCLOCK;

MYCLOCK* StartMyClick();
void Update(MYCLOCK* object);
void Release(MYCLOCK* object);

inline void Set(MYCLOCK* object, SYSTEMTIME st) { object->st = st; };