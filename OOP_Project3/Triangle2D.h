#pragma once
#include "Matrix.h"

class Triangle2D
{
public:
    VERTEX v[3];

    void Init();
    void Process();
    void Render();
    void Release();
};
