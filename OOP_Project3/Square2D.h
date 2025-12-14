#pragma once
#include "Matrix.h"

class Square2D
{
public:
    VERTEX v[4];

    void Init();
    void Process();
    void Render();
    void Release();
};
