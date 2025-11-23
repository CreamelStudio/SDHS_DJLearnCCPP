#include "pch.h"
#include "Matrix.h"

//2D 영행렬
void Matrix2D::ZeroMatrix(void)
{
	m11 = 0;		m12 = 0;		m13 = 0;
	m21 = 0;		m22 = 0;		m23 = 0;
	m31 = 0;		m32 = 0;		m33 = 0;
/*
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			mat.m[i][j] = 0;
*/
}


//단위 행렬
void Matrix2D::Identity(void)
{
	m11 = 1;		m12 = 0;		m13 = 0;
	m21 = 0;		m22 = 1;		m23 = 0;
	m31 = 0;		m32 = 0;		m33 = 1;
}

//이동 변환 행렬
void Matrix2D::Move(int dx, int dy)
{
	m11 = 1;		m12 = 0;		m13 = 0;
	m21 = 0;		m22 = 1;		m23 = 0;
	m31 = dx;		m32 = dy;		m33 = 1;
}

//회전 변환 행렬
void Matrix2D::Rotate(int theta)
{
	float r = theta * PI / 180.0f; //라디안 값으로 변환

	m11 = cos(r);	m12 = sin(r);		m13 = 0;
	m21 = -sin(r);	m22 = cos(r);		m23 = 0;
	m31 = 0;		m32 = 0;			m33 = 1;
}

//크기 변환 행렬
void Matrix2D::Scale(float s)
{
	m11 = s;		m12 = 0;		m13 = 0;
	m21 = 0;		m22 = s;		m23 = 0;
	m31 = 0;		m32 = 0;		m33 = 1;
}

//행렬 곱셈 연산(3X3)X(3X3)
void Matrix2D::Multiple(Matrix2D m1, Matrix2D m2)
{
	m11 = m1.m11 * m2.m11 + m1.m12 * m2.m21 + m1.m13 * m2.m31;
	m12 = m1.m11 * m2.m12 + m1.m12 * m2.m22 + m1.m13 * m2.m32;
	m13 = m1.m11 * m2.m13 + m1.m12 * m2.m23 + m1.m13 * m2.m33;
	m21 = m1.m21 * m2.m11 + m1.m22 * m2.m21 + m1.m23 * m2.m31;
	m22 = m1.m21 * m2.m12 + m1.m22 * m2.m22 + m1.m23 * m2.m32;
	m23 = m1.m21 * m2.m13 + m1.m22 * m2.m23 + m1.m23 * m2.m33;
	m31 = m1.m31 * m2.m11 + m1.m32 * m2.m21 + m1.m33 * m2.m31;
	m32 = m1.m31 * m2.m12 + m1.m32 * m2.m22 + m1.m33 * m2.m32;
	m33 = m1.m31 * m2.m13 + m1.m32 * m2.m23 + m1.m33 * m2.m33;
}

//꼭지점(1X3)과 행렬 곱셈 연산(3X3)
VERTEX Multiple(VERTEX v, Matrix2D m)
{
	VERTEX vtx;

	vtx.x = v.x * m.m11 + v.y * m.m21 + v.w * m.m31;
	vtx.y = v.x * m.m12 + v.y * m.m22 + v.w * m.m32;
	vtx.w = v.x * m.m13 + v.y * m.m23 + v.w * m.m33;

	return vtx;
}