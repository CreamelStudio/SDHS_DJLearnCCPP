#pragma once

#define MAX_LOADSTRING 100
//윈도우를 클래스화
class BaseWindow
{
private:
	HINSTANCE hInst; // 현재 인스턴스입니다.
	WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
	WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

private:
	ATOM  MyRegisterClass(HINSTANCE hInstance);
	BOOL  InitInstance(HINSTANCE, int);

public:
	BaseWindow(); //디폴트생성자
	BaseWindow(HINSTANCE hInstance); //생성자
	~BaseWindow(); //소멸자

	int Initiallize(int nCmdShow); //시스템초기화 //시스템생성

public:
	inline void SetInst(HINSTANCE hInstance) { hInst = hInstance; }
	inline HINSTANCE GetInst() { return hInst; }
};

