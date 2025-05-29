#include "pch.h"
#include "GameManager.h"

extern int nFPS;
extern int nCount;
extern HDC ghdc;

void Awake() {

}

void Start() {

}

void Update() {
	nCount++;
	
	wchar_t strTemp[128] = L"";
	wsprintf(strTemp, L"FPS = %5d, frame = %5d", nFPS, nCount);
	TextOut(ghdc, 0, 0, strTemp, wcslen(strTemp));
}

void Release() {

}