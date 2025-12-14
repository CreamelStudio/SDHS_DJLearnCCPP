#include "pch.h"
#include "Triangle2D.h"

extern RECT rtScreen;
static VERTEX SV[3];

void Triangle2D::Init()
{
    // 단순 2D 삼각형 (z = 0)
    v[0].x = 0;    v[0].y = -100; v[0].z = 0; v[0].w = 1;
    v[1].x = -100; v[1].y = 100;  v[1].z = 0; v[1].w = 1;
    v[2].x = 100;  v[2].y = 100;  v[2].z = 0; v[2].w = 1;
}

void Triangle2D::Process()
{
    static int nCnt = 0;

    Matrix3D CTM, RxTM, RyTM, RzTM, ScreenTM;
    CTM.Identity();

    ScreenTM.Move((float)rtScreen.right / 2.0f,
        (float)rtScreen.bottom / 2.0f,
        0.0f);

	RxTM.RotateX(0);
	RyTM.RotateY(0);
    RzTM.RotateZ(nCnt);


    // ★ 회전 → 화면이동 순서로 적용
    // (너 코드 구조: v * M 형태니까 이렇게)
    CTM = RxTM * RyTM * RzTM * ScreenTM;

    for (int i = 0; i < 3; i++)
        SV[i] = v[i] * CTM;

    nCnt += 1.0f;
}

void Triangle2D::Render()
{
    gdi->OrangePen();

    gdi->Line((int)SV[0].x, (int)SV[0].y, (int)SV[1].x, (int)SV[1].y);
    gdi->Line((int)SV[1].x, (int)SV[1].y, (int)SV[2].x, (int)SV[2].y);
    gdi->Line((int)SV[2].x, (int)SV[2].y, (int)SV[0].x, (int)SV[0].y);

    for (int i = 0; i < 3; i++)
        DrawBigBigDot((int)SV[i].x, (int)SV[i].y, RGB(255, 255, 0));
}

void Triangle2D::Release()
{
}
