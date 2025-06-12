#include "pch.h"
#include "GlobalVariable.h"


//메인윈도우 시스템 사용 전역변수
HINSTANCE hInst = NULL;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING] = _T("");                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING] = _T("");            // 기본 창 클래스 이름입니다.

//메인프로시저 전역변수
BOOL bIsLoopExit = TRUE;
BOOL bIsActive = FALSE;
int nFPS = 0;
int nCount = 0;
HDC gHDC = NULL;
HWND ghWnd = NULL;

//GameManager 전역변수
HDC ScreenDC = NULL; //화면DC //메인DC
HDC MemoryDC = NULL; //메모리에서 이미지를 모으는 DC
HBITMAP hBitmap = NULL; //해당DC의 이미지 자체

