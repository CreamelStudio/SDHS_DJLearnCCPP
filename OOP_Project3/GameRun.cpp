#include "pch.h"
#include "GameRun.h"

extern BaseWindow* System;
extern bool bIsGameActive;
extern HDC ScreenDC;  //주버퍼
extern HDC MemoryDC;  //보조버퍼
extern HBITMAP MemoryBM;
extern RECT rtScreen;

Square2D* pTetra;

void Initialize() {
    pTetra = new Square2D;
    pTetra->Init();
}

void Process() {
	pTetra->Process();
}

void PreRender() {
    BitBlt(MemoryDC,
        rtScreen.left, rtScreen.top,
        rtScreen.right, rtScreen.bottom,
        NULL, 0, 0, BLACKNESS);
    gdi->StartDraw(MemoryDC);
}

void Render() {
    gdi->GrayPen();
    gdi->Line((int)(rtScreen.right / 2 + 0.5) + 0, 0, (int)(rtScreen.right / 2 + 0.5), (int)(rtScreen.bottom + 0.5));
    gdi->Line(0, (int)(rtScreen.bottom / 2 + 0.5), (int)(rtScreen.right + 0.5), (int)(rtScreen.bottom / 2 + 0.5));

	pTetra->Render();
}

void PostRender() {
    gdi->StopDraw(MemoryDC);
    BitBlt(ScreenDC,
        rtScreen.left, rtScreen.top,
        rtScreen.right, rtScreen.bottom,
        MemoryDC, 0, 0, SRCCOPY);
}

void Release() {
    pTetra->Release();
	delete pTetra;
}