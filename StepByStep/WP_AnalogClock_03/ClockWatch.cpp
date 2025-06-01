#include "pch.h"
#include "ClockWatch.h"
#include "gdiUtil.h"
#include <math.h>

static ClockWatch gClock;
static SYSTEMTIME gST;

ClockWatch Start(int x, int y, int width, int height)
{
    gClock.id = 1; // ���� Ÿ�̸� ID
    gClock.x = x;
    gClock.y = y;
    gClock.width = width;
    gClock.height = height;
    gClock.rotation1 = 0;
    gClock.rotation2 = 0;

    HWND hWnd = gClock.hWnd = GetActiveWindow(); // �Ǵ� �ܺο��� ���޹޾ƾ� ��
    SetTimer(hWnd, gClock.id, 1000, NULL);

    return gClock;
}

void Update()
{
    GetLocalTime(&gST);
    gClock.rotation1 = gST.wSecond * 6; // 360 / 60 = 6��
    // rotation2 = ...
}

void Draw(HDC hdc)
{
    int cx = gClock.x + gClock.width / 2;
    int cy = gClock.y + gClock.height / 2;
    int radius = gClock.width / 2 - 10;

    // �׵θ�
    Ellipse(hdc, gClock.x, gClock.y, gClock.x + gClock.width, gClock.y + gClock.height);

    float theta = 3.141592f / 180.0f * (gClock.rotation1 - 90); // 0�� = ����

    int x2 = static_cast<int>(cos(theta) * radius) + cx;
    int y2 = static_cast<int>(sin(theta) * radius) + cy;

    gdiLine(hdc, cx, cy, x2, y2);
    gdiStar(hdc, x2, y2);
}

void Destroy(ClockWatch clock)
{
    KillTimer(clock.hWnd, clock.id);
}wq