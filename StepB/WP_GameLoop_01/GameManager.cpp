#include "pch.h"
#include "GameManager.h"

extern int nFPS;
extern int nCount;
extern HDC gHDC;

BYTE bitImage[] = {
	0xC3, 0xFF,
	0xDB, 0xFF,
	0x66, 0xFF,
	0x5A, 0xFF,
	0x5A, 0xFF,
	0x66, 0xFF,
	0xDB, 0xFF,
	0xC3, 0xFF,
};

HDC ScreenDC, MemoryDC, ImageDC, BkImageDC;
HBITMAP hBitmap, hImage, hBkImage;
extern HWND ghWnd;

void Awake()
{
	
}

void Start()
{
	ScreenDC = GetDC(ghWnd); // Get the screen device context

	MemoryDC = CreateCompatibleDC(ScreenDC);
	hBitmap = CreateBitmap(640, 480, 1, 1, NULL); 
	SelectObject(MemoryDC, hBitmap);

	BkImageDC = CreateCompatibleDC(ScreenDC);
	hBkImage = CreateBitmap(640, 480, 1, 1, NULL);
	SelectObject(BkImageDC, hBkImage);

	ImageDC = CreateCompatibleDC(ScreenDC);
	hImage = CreateBitmap(8, 8, 1, 1, bitImage);
	SelectObject(ImageDC, hImage);
}

void Update()
{
	BitBlt(MemoryDC, 0, 0, 640, 480, BkImageDC, 0, 0, SRCCOPY);

	nCount++;
	wchar_t strTemp[128] = L"";
	wsprintf(strTemp, L"FPS = %06d, frame = %06d", nFPS, nCount);
	TextOut(gHDC, 0, 0, strTemp, wcslen(strTemp));

	//BitBlt(ScreenDC, 100, 100, 640, 480, MemoryDC, 0, 0, SRCCOPY);
	//StretchBlt(ScreenDC, 0, 0, 256, 256, ImageDC, 0, 0, 8, 8, SRCCOPY);
	StretchBlt(MemoryDC, 100, 100, 256, 256, ImageDC, 0, 0, 8, 8, SRCCOPY);
	BitBlt(ScreenDC, 0, 0, 640, 480, MemoryDC, 0, 0, SRCCOPY);
}

void Release()
{
	DeleteObject(hImage);
	ReleaseDC(ghWnd, ImageDC);
	DeleteObject(hBkImage);
	ReleaseDC(ghWnd, BkImageDC);
	DeleteObject(hBitmap);
	ReleaseDC(ghWnd, MemoryDC);
	ReleaseDC(ghWnd, ScreenDC);
}