// cmdProject1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

float PI = 3.14;

#include <iostream>
#include <Windows.h>
#include "LineAlgebra.h"

using namespace LineAlgebra;

int main()
{
    int sw = 100;
    int sh = 25;
    int cx = sw / 2 + 0.5f;
    int cy = sh / 2 + 0.5f;

    while (1) {
        Rect(-20 + cx, -10 + cy, 20 + cx, 10 + cy);
        TwoPointLine(cx, cy, cx + 10, cy + -10);
        /*for (int i = 0; i < 360; i += 1) {
            float theta = 180.0f / PI * (float)i;
            int x = ((float)cos(theta) - (float)sin(theta)) * 10;
            int y = ((float)cos(theta) + (float)sin(theta)) * 10;
            TwoPointLine(cx, cy, cx + x, cy + y);
        }*/

        Sleep(1);
     }
}