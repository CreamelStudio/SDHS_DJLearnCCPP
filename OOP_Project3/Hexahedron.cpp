#include "pch.h"
#include "Hexahedron.h"

extern RECT rtScreen;

// 전역 중복 방지
static VERTEX SV[8];

void Hexahedron::Init()
{
    float s = 100.0f;

    // 위(y=+s)
    v[0].x = -s; v[0].y = s; v[0].z = -s; v[0].w = 1;
    v[1].x = s; v[1].y = s; v[1].z = -s; v[1].w = 1;
    v[2].x = s; v[2].y = s; v[2].z = s; v[2].w = 1;
    v[3].x = -s; v[3].y = s; v[3].z = s; v[3].w = 1;

    // 아래(y=-s)
    v[4].x = -s; v[4].y = -s; v[4].z = -s; v[4].w = 1;
    v[5].x = s; v[5].y = -s; v[5].z = -s; v[5].w = 1;
    v[6].x = s; v[6].y = -s; v[6].z = s; v[6].w = 1;
    v[7].x = -s; v[7].y = -s; v[7].z = s; v[7].w = 1;

    // 엣지 12개 (0-1-2-3-0, 4-5-6-7-4, 세로 연결)
    int k = 0;

    // 윗면
    Idx[k++] = 0; Idx[k++] = 1;
    Idx[k++] = 1; Idx[k++] = 2;
    Idx[k++] = 2; Idx[k++] = 3;
    Idx[k++] = 3; Idx[k++] = 0;

    // 아랫면
    Idx[k++] = 4; Idx[k++] = 5;
    Idx[k++] = 5; Idx[k++] = 6;
    Idx[k++] = 6; Idx[k++] = 7;
    Idx[k++] = 7; Idx[k++] = 4;

    // 세로
    Idx[k++] = 0; Idx[k++] = 4;
    Idx[k++] = 1; Idx[k++] = 5;
    Idx[k++] = 2; Idx[k++] = 6;
    Idx[k++] = 3; Idx[k++] = 7;
}

void Hexahedron::Process()
{
    static int nCnt = 0;

    Matrix3D CTM, RxTM, RyTM, RzTM, STM, ScreenTM;
    CTM.Identity();

    RxTM.RotateX((float)nCnt);
    RyTM.RotateY(30.0f);
    RzTM.RotateZ(0.0f);

    STM.Scale(1.0f);
    ScreenTM.Move((float)rtScreen.right / 2.0f, (float)rtScreen.bottom / 2.0f, 0.0f);

    CTM = RxTM * RyTM * RzTM * STM * ScreenTM;

    for (int i = 0; i < 8; i++)
        SV[i] = v[i] * CTM;

    nCnt++;
}

void Hexahedron::Render()
{
    gdi->OrangePen();

    for (int e = 0; e < 12; e++)
    {
        int a = Idx[e * 2 + 0];
        int b = Idx[e * 2 + 1];

        gdi->Line((int)SV[a].x, (int)SV[a].y, (int)SV[b].x, (int)SV[b].y);
    }

    for (int i = 0; i < 8; i++)
        DrawBigBigDot((int)SV[i].x, (int)SV[i].y, RGB(255, 255, 0));
}

void Hexahedron::Release()
{
}
