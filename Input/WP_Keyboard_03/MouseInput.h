#pragma once

enum MouseMSG { NONE, LBD, LBU, RBD, RBU, MBD, MBU, LDBLK, RDBLK, MDBLK };

typedef struct __MOUSEOBJECT {
	int x, y;
	int w, h; 

	RECT rtMouse;
	RECT rtLeftBtn;
	RECT rtRightBtn;
	RECT rtMiddleBtn;

	MouseMSG State; // Current mouse state
	COLORREF crBtnState[3][2]; // {Left : Right : Middle} {Normal, On}
} MOUSEOBJ;

MOUSEOBJ* StartMouseObject(int x, int y, int w, int h);
void Update(MOUSEOBJ* mouse);
void Draw(MOUSEOBJ* mouse, HDC hdc);
void Release(MOUSEOBJ* mouse);

int OnMouseWheel(HWND hWnd, WPARAM wParam, LPARAM lParam);
int OnMouseLBTNDBLCLK(HWND hWnd, WPARAM wParam, LPARAM lParam);
int OnMouseRBTNDBLCLK(HWND hWnd, WPARAM wParam, LPARAM lParam);
int OnMouseMBTNDBLCLK(HWND hWnd, WPARAM wParam, LPARAM lParam);
int OnMouseLBTNDN(HWND hWnd, WPARAM wParam, LPARAM lParam);
int OnMouseLBTNUP(HWND hWnd, WPARAM wParam, LPARAM lParam);
int OnMouseRBTNDN(HWND hWnd, WPARAM wParam, LPARAM lParam);
int OnMouseRBTNUP(HWND hWnd, WPARAM wParam, LPARAM lParam);
int OnMouseMBTNDN(HWND hWnd, WPARAM wParam, LPARAM lParam);
int OnMouseMBTNUP(HWND hWnd, WPARAM wParam, LPARAM lParam);
int OnMouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam);