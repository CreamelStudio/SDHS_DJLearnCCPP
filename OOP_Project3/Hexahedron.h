#pragma once
#include "Matrix.h"

class Hexahedron
{
public:
    VERTEX v[8];      // 정점 8개
    int Idx[12 * 2];  // 엣지 12개 * 2 = 24

    void Init();
    void Process();
    void Render();
    void Release();
};
