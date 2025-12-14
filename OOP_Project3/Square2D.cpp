#include "pch.h"
#include "Square2D.h"

extern RECT rtScreen;
static VERTEX SV[4];

void Square2D::Init()
{
    // 단순 2D 사각형
    v[0].x = -100; v[0].y = -100; v[0].z = 0; v[0].w = 1;
    v[1].x = 100; v[1].y = -100; v[1].z = 0; v[1].w = 1;
    v[2].x = 100; v[2].y = 100; v[2].z = 0; v[2].w = 1;
    v[3].x = -100; v[3].y = 100; v[3].z = 0; v[3].w = 1;
}

void Square2D::Process()
{
    static float nCnt = 0.0f;
    Matrix3D CTM, RxTM, RyTM, RzTM, ScreenTM;
    CTM.Identity();

    ScreenTM.Move(
        (float)rtScreen.right / 2.0f,
        (float)rtScreen.bottom / 2.0f,
        0.0f
    );

	RxTM.RotateX(0);
	RyTM.RotateY(0);
	RzTM.RotateZ(nCnt);

    CTM = RxTM * RyTM * RzTM * ScreenTM;

    for (int i = 0; i < 4; i++)
        SV[i] = v[i] * CTM;

    nCnt++;
}

void Square2D::Render()
{
    gdi->OrangePen();

    gdi->Line((int)SV[0].x, (int)SV[0].y, (int)SV[1].x, (int)SV[1].y);
    gdi->Line((int)SV[1].x, (int)SV[1].y, (int)SV[2].x, (int)SV[2].y);
    gdi->Line((int)SV[2].x, (int)SV[2].y, (int)SV[3].x, (int)SV[3].y);
    gdi->Line((int)SV[3].x, (int)SV[3].y, (int)SV[0].x, (int)SV[0].y);

    for (int i = 0; i < 4; i++)
        DrawBigBigDot((int)SV[i].x, (int)SV[i].y, RGB(255, 255, 0));
}

void Square2D::Release()
{
}
