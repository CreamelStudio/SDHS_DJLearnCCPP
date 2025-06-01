#pragma once
#include <windows.h>

struct ClockWatch
{
    int id;
    int x, y, width, height;

    int rotation1;
    int rotation2;

    HWND hWnd;
};

ClockWatch Start(int x, int y, int width, int height);
void Update();
void Draw(HDC hdc);
void Destroy(ClockWatch clock);