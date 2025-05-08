#pragma once

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void gdiRotLineCW(HDC hdc, float x, float y, float lineLength, float theta);