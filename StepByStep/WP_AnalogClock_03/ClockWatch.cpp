#include "pch.h"
#include "ClockWatch.h"
#include "gdiUtil.h"
#include <math.h>

static ClockWatch gClock;
static SYSTEMTIME gST;

ClockWatch Start(int x, int y, int width, int height)
{
    gClock.id = 1; // 고정 타이머 ID
    gClock.x = x;
    gClock.y = y;
    gClock.width = width;
    gClock.height = height;
    gClock.rotation1 = 0;
    gClock.rotation2 = 0;

    HWND hWnd = gClock.hWnd = GetActiveWindow(); // 또는 외부에서 전달받아야 함
    SetTimer(hWnd, gClock.id, 1000, NULL);

    return gClock;
}

void Update()
{
    GetLocalTime(&gST);
    gClock.rotation1 = gST.wSecond * 6; // 360 / 60 = 6도
    // rotation2 = ...
}

void Draw(HDC hdc)
{
    int cx = gClock.x + gClock.width / 2;
    int cy = gClock.y + gClock.height / 2;
    int radius = gClock.width / 2 - 10;

    // 테두리
    Ellipse(hdc, gClock.x, gClock.y, gClock.x + gClock.width, gClock.y + gClock.height);

    float theta = 3.141592f / 180.0f * (gClock.rotation1 - 90); // 0초 = 위쪽

    int x2 = static_cast<int>(cos(theta) * radius) + cx;
    int y2 = static_cast<int>(sin(theta) * radius) + cy;

    gdiLine(hdc, cx, cy, x2, y2);
    gdiStar(hdc, x2, y2);
}

void Destroy(ClockWatch clock)
{
    KillTimer(clock.hWnd, clock.id);
}wq