#include "pch.h"
#include "GameManager.h"

extern int nFPS;
extern int nCount;
extern HDC gHDC;
extern BOOL bIsLoopExit;

BYTE SpriteData[256] = {
	0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,
	0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,
	0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,
	0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,0,
	0,0,0,0,0,0,0,1,1,0,0,0,0,1,0,0,
	0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,
	0,0,0,0,1,0,1,1,1,1,0,0,0,0,0,0,
	0,0,0,1,0,0,1,1,1,1,0,0,0,0,0,0,
	0,0,1,0,0,0,0,1,1,0,0,0,0,0,0,0,
	0,0,1,0,0,0,1,1,1,1,0,0,0,0,0,0,
	0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,
	0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,
	0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,
	0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,
	0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,
	0,0,0,0,1,1,1,0,0,1,1,1,0,0,0,0
};

//이미지 자체인데, 1bit이미지 //흑백
//BYTE bitImage[] = {
//	0xC3, 0xFF, 
//	0xBD, 0xFF,
//	0x66, 0xFF,
//	0x5A, 0xFF,
//	0x5A, 0xFF,
//	0x66, 0xFF,
//	0xBD, 0xFF,
//	0xC3, 0xFF,
//};

//BYTE bitImage[][16] = {
//	{
//	0xE7, 0xFF,
//	0xC3, 0xFF,
//	0x81, 0xFF,
//	0x24, 0xFF,
//	0x00, 0xFF,
//	0xC3, 0xFF,
//	0x81, 0xFF,
//	0x5A, 0xFF,
//	},
//	{
//	0xE7, 0xFF,
//	0xC3, 0xFF,
//	0x81, 0xFF,
//	0x12, 0xFF,
//	0x00, 0xFF,
//	0xC3, 0xFF,
//	0x81, 0xFF,
//	0xAD, 0xFF,
//	}
//};


extern HWND ghWnd;

HDC ScreenDC; //화면DC //메인DC

HDC MemoryDC; //메모리에서 이미지를 모으는 DC
HBITMAP hBitmap; //해당DC의 이미지 자체


void Awake()
{
	bIsLoopExit = true;
}

void Start()
{
	ScreenDC = GetDC(ghWnd); //화면DC 선언

	//이미지를 모으는 작업
	MemoryDC = CreateCompatibleDC(ScreenDC); //메모리 DC 생성
	hBitmap = CreateBitmap(640, 480, 1, 1, NULL); //1bit 흑백이미지 1면 너비 640 높이 480 생성
	SelectObject(MemoryDC, hBitmap); //DC와 비트맵 연결 //포인터와 데이터 연결
}

VOID DrawPoint(HDC hdc, int x, int y, int dx, int dy, COLORREF color, int nSize) {
	for (int i = 0; i < nSize; i++) {
		for (int j = 0; j < nSize; j++) {
			SetPixel(hdc, x * nSize + dx + i, y * nSize + dy + j, color);
		}
	}
}

void Update()
{
	int offset = 0;
	for (int y = 0; y < 16; y++) {
		for (int x = 0; x < 16; x++) {
			if (SpriteData[offset++]) {
				DrawPoint(MemoryDC, x, y, 10, 10, RGB(255, 255, 255), 10);
			}
		}
	}

	//===================================================================
	//FPS 및 프레임 표시
	nCount++;
	wchar_t strTemp[128] = L"";
	wsprintf(strTemp, L"FPS = %06d, frame = %06d", nFPS, nCount);
	TextOut(MemoryDC, 0, 0, strTemp, wcslen(strTemp));
	//===================================================================
	BitBlt(ScreenDC, 0, 0, 640, 480, MemoryDC, 0, 0, SRCCOPY); //메모리DC 모아진 이미지를 화면에 출력
}



void Release()
{
	DeleteObject(hBitmap); //모으는 DC 데이터 지우기
	ReleaseDC(ghWnd, MemoryDC); //모으는 DC(포인터) 지우기

	ReleaseDC(ghWnd, ScreenDC); //화면 DC 지우기 //메인 DC지우기
}