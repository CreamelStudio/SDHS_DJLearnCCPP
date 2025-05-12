#pragma once
//Typedef struct -> class



typedef struct __analogclock
{
	HDC hdc;
	SYSTEMTIME st;

	int iStyle;

	int x, y; //�ð� ��ǥ
	int w, h; //�ð� ũ��

	NEEDLE* pHour; //��ħ
	NEEDLE* pMin; //��ħ
	NEEDLE* pSec; //��ħ
}MYCLOCK;

MYCLOCK* StartMyClock(int x, int y, int w, int h);
void Update(MYCLOCK* object);
void Release(MYCLOCK* object);

inline void Set(MYCLOCK* object, SYSTEMTIME st) { object->st = st; };
inline void SetTime(MYCLOCK* object, SYSTEMTIME st) { object->st = st; };
inline void SetHDC(MYCLOCK* object, HDC hdc) { object->hdc = hdc; };
inline void SetHDC(NEEDLE* object, HDC hdc) { object->hdc = hdc; };
inline void SetBK(MYCLOCK* object, int istyle) {object->iStyle = istyle}