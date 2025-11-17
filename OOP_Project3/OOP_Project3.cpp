// OOP_Project3.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "OOP_Project3.h"

BaseWindow* System;
bool bIsGameActive = false;
HDC hdc;
HDC ScreenDC;  //주버퍼
HDC MemoryDC;  //보조버퍼
HBITMAP MemoryBM;
RECT rtScreen; //화면크기

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    System = new BaseWindow(hInstance);

    return System->Initiallize(SW_SHOW);
}

