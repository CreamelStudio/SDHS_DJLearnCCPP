#include <Windows.h>

#define WIDTH 640
#define HEIGHT 480

LRESULT CALLBACK WndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam) {
	switch (umsg) {
		case WM_CLOSE:
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}

	return DefWindowProc(hwnd, umsg, wparam, lparam);
}

int APIENTRY WinMain(HINSTANCE hinst, HINSTANCE hprevinst, LPSTR lpCmdLine, int nshowcmd) {
	HWND hwnd;
	WNDCLASSEX wcex;
	HINSTANCE hinstance = GetModuleHandle(NULL);

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hinstance;
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcex.hCursor = LoadCursor(0, IDC_ARROW);
	wcex.hIcon = LoadIcon(hinstance, (LPCTSTR)IDI_APPLICATION);
	wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_APPLICATION);
	wcex.lpfnWndProc = WndProc;
	wcex.lpszClassName = L"MyWindowClass";
	wcex.lpszMenuName = NULL;
	wcex.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&wcex);

	hwnd = CreateWindow(L"MyWindowClass", L"MyWindow", WS_OVERLAPPEDWINDOW, 0, 0, WIDTH, HEIGHT, NULL, NULL, hinstance, NULL);


	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	MSG msg;

	while (GetMessage(&msg, 0, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}