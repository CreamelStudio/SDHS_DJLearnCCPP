#include "pch.h"
#include "GameManager.h"

extern int nFPS;
extern int nCount;
extern HDC gHDC;

void Awake()
{

}

void Start()
{

}

void Update()
{
	nCount++;

	wchar_t strTemp[128] = L"";
	wsprintf(strTemp, L"FPS = %06d, frame = %06d", nFPS, nCount);
	TextOut(gHDC, 0, 0, strTemp, wcslen(strTemp));
}

void Release()
{

}