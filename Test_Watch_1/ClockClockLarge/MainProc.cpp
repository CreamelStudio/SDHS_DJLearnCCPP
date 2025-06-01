#include "pch.h"
#include "MainProc.h"

extern INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
extern HINSTANCE hInst;
extern float numberRotations[3][6][2][10];

CLOCKDATA* g_ClockData[12][6];

float x = 100.0f;
float y = 100.0f;

float xOffset = 100.0f; // X축 오프셋
float yOffset = 100.0f; // Y축 오프셋

float xScale = 100.0f; // X축 스케일
float yScale = 100.0f; // Y축 스케일

float rotations[12][6][2];

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

int OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam) {
    int wmId = LOWORD(wParam);
    // 메뉴 선택을 구문 분석합니다:
    switch (wmId)
    {
    case IDM_ABOUT:
        DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
        break;
    case IDM_EXIT:
        DestroyWindow(hWnd);
        break;
    default:
        return DefWindowProc(hWnd, WM_COMMAND, wParam, lParam);
    }

    return 0;
}

int OnPaint(HWND hWnd, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);

    for(int i=0;i<12;i++) {
        for(int j=0;j<6;j++) {
			Draw(g_ClockData[i][j], hdc);
        }
	}

    EndPaint(hWnd, &ps);
    return 0;
}

int OnDestroy(HWND hWnd, WPARAM wParam, LPARAM lParam) {
    PostQuitMessage(0);
    return 0;
}

int OnCreate(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	SetTimer(hWnd, 1, 1, NULL);

    for(int i=0;i<12;i++) {
        for(int j=0;j<6;j++) {
			g_ClockData[i][j] = CreateClockData((i * xOffset) + x, (j * yOffset) + y, xScale, yScale, 0, 0, COLORREF(RGB(0,0,0)), COLORREF(RGB(0, 0, 0)), 4);
			SetHDC(g_ClockData[i][j], GetDC(hWnd));
        }
	}

    return 0;
}

struct RotationLerp {
    float startAngle[2];
    float endAngle[2];
    float progress;
    bool active;
};

RotationLerp lerps[12][6];
float Lerp(float a, float b, float t) {
    return a + (b - a) * t;
}
int GetDigit(int value, int place) {
    return (value / place) % 10;
}

int beforeDigits[4] = { -1, -1, -1, -1 };

int OnTimer(HWND hWnd, WPARAM wParam, LPARAM lParam) {
    SYSTEMTIME time;
    GetLocalTime(&time);

    int h = time.wHour;
    int m = time.wMinute;

    int digits[4] = {
        GetDigit(h, 10),
        GetDigit(h, 1),
        GetDigit(m, 10),
        GetDigit(m, 1),
    };

    //시간이 바뀌면 Lerp 시작함!!!
    for (int k = 0; k < 4; k++) {
        if (digits[k] != beforeDigits[k]) {
            int digit = digits[k];
            int rowOffset = k * 3;//칸크기

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 6; j++) {
                    for (int h = 0; h < 2; h++) {
                        lerps[rowOffset + i][j].startAngle[h] = rotations[rowOffset + i][j][h];
                        lerps[rowOffset + i][j].endAngle[h] = numberRotations[i][j][h][digit];
                    }
                    lerps[rowOffset + i][j].progress = 0.0f;
                    lerps[rowOffset + i][j].active = true;
                }
            }

            beforeDigits[k] = digit;
        }
    }

    float delta = 1.0f / 60.0f;

    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 6; j++) {
            if (lerps[i][j].active) {
                lerps[i][j].progress += delta;
                if (lerps[i][j].progress >= 1.0f) {
                    lerps[i][j].progress = 1.0f;
                    lerps[i][j].active = false;
                }

                for (int h = 0; h < 2; h++) {
                    rotations[i][j][h] = Lerp(lerps[i][j].startAngle[h],lerps[i][j].endAngle[h],lerps[i][j].progress);
                }
            }
        }
    }

    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 6; j++) {
            Update(g_ClockData[i][j], rotations[i][j][0], rotations[i][j][1]);
        }
    }

    InvalidateRect(hWnd, NULL, TRUE);
    UpdateWindow(hWnd);
    return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	    case WM_TIMER: return OnTimer(hWnd, wParam, lParam);
	    case WM_CREATE: return OnCreate(hWnd, wParam, lParam);
        case WM_COMMAND: return OnCommand(hWnd, wParam, lParam);
        case WM_PAINT: return OnPaint(hWnd, wParam, lParam);
        case WM_DESTROY: return OnDestroy(hWnd, wParam, lParam);
        default: return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}