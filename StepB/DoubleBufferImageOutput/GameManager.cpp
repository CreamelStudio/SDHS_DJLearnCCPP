#include "pch.h"
#include "GameManager.h"

extern int nFPS;
extern int nCount;
extern HDC gHDC;

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

BYTE bitImage[][16] = {
	{
	0xE7, 0xFF,
	0xC3, 0xFF,
	0x81, 0xFF,
	0x24, 0xFF,
	0x00, 0xFF,
	0xC3, 0xFF,
	0x81, 0xFF,
	0x5A, 0xFF,
	},
	{
	0xE7, 0xFF,
	0xC3, 0xFF,
	0x81, 0xFF,
	0x12, 0xFF,
	0x00, 0xFF,
	0xC3, 0xFF,
	0x81, 0xFF,
	0xAD, 0xFF,
	}
};


extern HWND ghWnd;
extern int nAniOn;

HDC ScreenDC; //화면DC //메인DC

HDC MemoryDC; //메모리에서 이미지를 모으는 DC
HBITMAP hBitmap; //해당DC의 이미지 자체

HDC BkImageDC; //메모리DC //이미지 연결 DC
HBITMAP hBkImage; //흰 이미지 배경 깔기용

HDC ImageDC[2]; //메모리DC //실제 구현된 이미지DC
HBITMAP hImage[2]; //출력 이미지 자체


void Awake()
{
}

void Start()
{
	ScreenDC = GetDC(ghWnd); //화면DC 선언

	//이미지를 모으는 작업
	MemoryDC = CreateCompatibleDC(ScreenDC); //메모리 DC 생성
	hBitmap = CreateBitmap(640, 480, 1, 1, NULL); //1bit 흑백이미지 1면 너비 640 높이 480 생성
	SelectObject(MemoryDC, hBitmap); //DC와 비트맵 연결 //포인터와 데이터 연결

	//배경이미지 생성 
	BkImageDC = CreateCompatibleDC(ScreenDC); //흰색 배경이미지 DC 생성
	hBkImage = CreateBitmap(640, 480, 1, 1, NULL); //1bit 흑백이미지 1면 너비 640 높이 480 생성
	SelectObject(BkImageDC, hBkImage);//DC와 비트맵 연결 //포인터와 데이터 연결

	//실제이미지 생성
	ImageDC[0] = CreateCompatibleDC(ScreenDC); //이미지 DC 생성
	hImage[0] = CreateBitmap(8, 8, 1, 1, bitImage[0]); //1bit 흑백이미지 1면 너비 8 높이 8을 bitImage 데이터를 가지고 생성
	SelectObject(ImageDC[0], hImage[0]);//DC와 비트맵 연결 //포인터와 데이터 연결
	ImageDC[1] = CreateCompatibleDC(ScreenDC); //이미지 DC 생성
	hImage[1] = CreateBitmap(8, 8, 1, 1, bitImage[1]); //1bit 흑백이미지 1면 너비 8 높이 8을 bitImage 데이터를 가지고 생성
	SelectObject(ImageDC[1], hImage[1]);//DC와 비트맵 연결 //포인터와 데이터 연결
}

void Update()
{
	BitBlt(MemoryDC, 0, 0, 640, 480, BkImageDC, 0, 0, SRCCOPY | WHITENESS); //흰색 배경으로 초기화

	//===================================================================
	//FPS 및 프레임 표시
	nCount++;
	wchar_t strTemp[128] = L"";
	wsprintf(strTemp, L"FPS = %06d, frame = %06d", nFPS, nCount);
	TextOut(MemoryDC, 0, 0, strTemp, wcslen(strTemp));
	//===================================================================
	
	// 이미지 출력
	//BitBlt(MemoryDC, 100, 100, 16, 16, ImageDC, 0, 0, SRCCOPY); //원본 이미지
	StretchBlt(MemoryDC, 100, 100, 256, 256, ImageDC[nAniOn], 0, 0, 8, 8, SRCCOPY); //이미지 확대 축소
	
	BitBlt(ScreenDC, 0, 0, 640, 480, MemoryDC, 0, 0, SRCCOPY); //메모리DC 모아진 이미지를 화면에 출력
}

void Release()
{
	DeleteObject(hImage[0]); //실제 이미지 데이터 지우기
	ReleaseDC(ghWnd, ImageDC[0]); //실제 이미지 DC(포인터) 지우기
	DeleteObject(hImage[1]); //실제 이미지 데이터 지우기
	ReleaseDC(ghWnd, ImageDC[1]); //실제 이미지 DC(포인터) 지우기

	DeleteObject(hBkImage);  //배경 이미지 데이터 지우기
	ReleaseDC(ghWnd, BkImageDC); //배경 이미지 DC(포인터) 지우기

	DeleteObject(hBitmap); //모으는 DC 데이터 지우기
	ReleaseDC(ghWnd, MemoryDC); //모으는 DC(포인터) 지우기

	ReleaseDC(ghWnd, ScreenDC); //화면 DC 지우기 //메인 DC지우기
}