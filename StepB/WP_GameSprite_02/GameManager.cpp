#include "pch.h"
#include "GameManager.h"

extern HINSTANCE hInst;
extern int nFPS;
extern int nCount;
extern HDC gHDC;
extern HWND ghWnd;
extern BOOL bIsLoopExit;

extern HDC ScreenDC; //화면DC //메인DC
extern HDC MemoryDC; //메모리에서 이미지를 모으는 DC
extern HBITMAP hBitmap; //해당DC의 이미지 자체

BYTE SpriteData[256] = {
	0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0,
	0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0,
	0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
	0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
	0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0,
};

HDC hBkImgDC = NULL;
HBITMAP hBkImgBM = NULL;

HDC hBkImgDC2 = NULL;
HBITMAP hBkImgBM2 = NULL;

void Awake()
{
	bIsLoopExit = TRUE;
}

void Start()
{
	ScreenDC = GetDC(ghWnd); //화면DC 선언 //프라임 버퍼

	//이미지를 모으는 작업  //세컨 버퍼
	MemoryDC = CreateCompatibleDC(ScreenDC); //메모리 DC 생성
	hBitmap = CreateCompatibleBitmap(ScreenDC, 640, 480); //너비 640 높이 480 화면과 동일한 표면생성
	SelectObject(MemoryDC, hBitmap); //DC와 비트맵 연결 //포인터와 데이터 연결

	//이미지를 리소스로 부터 읽어오기
	hBkImgDC = CreateCompatibleDC(ScreenDC);
	hBkImgBM = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
	SelectObject(hBkImgDC, hBkImgBM);

	//이미지를 파일로 부터 읽어오기
	hBkImgDC2 = CreateCompatibleDC(ScreenDC);
	hBkImgBM2 = (HBITMAP)LoadImage(hInst, L"./Image/wave.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	SelectObject(hBkImgDC2, hBkImgBM2);
}

void DrawPoint(HDC hdc, int x, int y, int dx, int dy, COLORREF color, int nSize)
{
	for (int i = 0; i < nSize; i++)
	{
		for (int j = 0; j < nSize; j++)
		{
			SetPixel(hdc, x * nSize + dx + i, y * nSize + dy + j, color);
		}
	}
}

void Update()
{
	BitBlt(MemoryDC, 0, 0, 640, 480, hBkImgDC2, 0, 0, SRCCOPY);

	int offset = 0;
	for (int y = 0; y < 16; y++) //height
	{
		for (int x = 0; x < 16; x++) //width
		{
			if (SpriteData[offset++])
			{
				//SetPixel(MemoryDC, x + 100, y + 100, RGB(255, 255, 255));
				DrawPoint(MemoryDC, x, y, 20, 20, RGB(255, 200, 0), 20);
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