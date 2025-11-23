#pragma once

//Desc : 2D 꼭지점 정의 
typedef struct tagVertex
{
	union
	{
		struct
		{
			float x, y, w; //x, y좌표 , w 동차좌표는 항상 1
		};
		float p[3];
	};
}VERTEX;

//Desc : 2D연산을 위한 3X3행렬
class Matrix2D
{
public:
	union
	{
		struct
		{
			float m11, m12, m13;
			float m21, m22, m23;
			float m31, m32, m33;
		};
		float m[3][3];
	};

public:
	void Identity(void);
	void ZeroMatrix(void);
	void Move(int dx, int dy);
	void Rotate(int theta);
	void Scale(float s);
	
	void Multiple(Matrix2D m1, Matrix2D m2);
};

VERTEX Multiple(VERTEX v, Matrix2D m);


