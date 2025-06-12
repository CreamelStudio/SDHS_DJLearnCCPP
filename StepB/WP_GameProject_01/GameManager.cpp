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

BACKGROUND* BackGround = NULL;
DINO* Dino = NULL;

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

	BackGround = StartBackground(ScreenDC, IDB_GROUND1);
	Dino = StartDino(ScreenDC, IDB_DINO1);
}

void Update()
{ 
	Update(BackGround);
	Update(Dino);

	Render(MemoryDC, BackGround);
	Render(MemoryDC, Dino);

	Sleep(1);

#ifdef _DEBUG
	//===================================================================
	//FPS 및 프레임 표시
	nCount++;
	wchar_t strTemp[128] = L"";
	wsprintf(strTemp, L"FPS = %06d, frame = %06d", nFPS, nCount);
	TextOut(MemoryDC, 0, 0, strTemp, wcslen(strTemp));
	//===================================================================
#endif
	
	BitBlt(ScreenDC, 0, 0, 640, 480, MemoryDC, 0, 0, SRCCOPY); //메모리DC 모아진 이미지를 화면에 출력
}

void Release()
{
	Release(BackGround);

	DeleteObject(hBitmap); //모으는 DC 데이터 지우기
	ReleaseDC(ghWnd, MemoryDC); //모으는 DC(포인터) 지우기

	ReleaseDC(ghWnd, ScreenDC); //화면 DC 지우기 //메인 DC지우기
}