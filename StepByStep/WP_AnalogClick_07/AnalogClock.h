#pragma once
//Typedef struct -> class



typedef struct __analogclock
{
	int x, y; //�ð� ��ǥ
	int w, h; //�ð� ũ��

	NEEDLE* pHour; //��ħ
	NEEDLE* pMin; //��ħ
	NEEDLE* pSec; //��ħ

	SYSTEMTIME st;
}MYCLOCK;

MYCLOCK* StartMyClick();
void Update(MYCLOCK* object);
void Release(MYCLOCK* object);

inline void Set(MYCLOCK* object, SYSTEMTIME st) { object->st = st; };