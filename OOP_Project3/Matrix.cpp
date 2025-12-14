#include "pch.h"
#include "Matrix.h"

//2D 영행렬
void Matrix3D::ZeroMatrix(void)
{
	m11 = 0;		m12 = 0;		m13 = 0;	m14 = 0;
	m21 = 0;		m22 = 0;		m23 = 0;	m24 = 0;
	m31 = 0;		m32 = 0;		m33 = 0;	m34 = 0;
	m41 = 0;		m42 = 0;		m43 = 0;	m44 = 0;
}


//단위 행렬
void Matrix3D::Identity(void)
{
	m11 = 1;		m12 = 0;		m13 = 0;	m14 = 0;
	m21 = 0;		m22 = 1;		m23 = 0;	m24 = 0;
	m31 = 0;		m32 = 0;		m33 = 1;	m34 = 0;
	m41 = 0;		m42 = 0;		m43 = 0;	m44 = 1;

}

//이동 변환 행렬
void Matrix3D::Move(int dx, int dy, int dz)
{
	m11 = 1;		m12 = 0;		m13 = 0;		m14 = 0;
	m21 = 0;		m22 = 1;		m23 = 0;		m24 = 0;
	m31 = 0;		m32 = 0;		m33 = 1;		m34 = 0;
	m41 = dx;		m42 = dy;		m43 = dz;		m44 = 1;
}

//회전 변환 행렬
void Matrix3D::RotateX(float theta)
{
	float r = theta * PI / 180.0f;

	m11 = 1;   m12 = 0;        m13 = 0;        m14 = 0;
	m21 = 0;   m22 = cos(r);   m23 = sin(r);   m24 = 0;
	m31 = 0;   m32 = -sin(r);  m33 = cos(r);   m34 = 0;
	m41 = 0;   m42 = 0;        m43 = 0;        m44 = 1;
}

void Matrix3D::RotateY(float theta)
{
	float r = theta * PI / 180.0f;

	m11 = cos(r);  m12 = 0;  m13 = -sin(r); m14 = 0;
	m21 = 0;       m22 = 1;  m23 = 0;       m24 = 0;
	m31 = sin(r);  m32 = 0;  m33 = cos(r);  m34 = 0;
	m41 = 0;       m42 = 0;  m43 = 0;       m44 = 1;
}


void Matrix3D::RotateZ(float theta)
{
	float r = theta * PI / 180.0f; //라디안 값으로 변환

	m11 = cos(r);	m12 = sin(r);		m13 = 0;		m14 = 0;
	m21 = -sin(r);	m22 = cos(r);		m23 = 0;		m24 = 0;
	m31 = 0;		m32 = 0;			m33 = 1;		m34 = 0;
	m41 = 0;		m42 = 0;			m43 = 0;		m44 = 1;
}

//크기 변환 행렬
void Matrix3D::Scale(float s)
{
	m11 = s;		m12 = 0;		m13 = 0;	m14 = 0;
	m21 = 0;		m22 = s;		m23 = 0;	m24 = 0;
	m31 = 0;		m32 = 0;		m33 = s;	m34 = 0;
	m41 = 0;		m42 = 0;		m43 = 0;	m44 = 1;
}

//행렬 곱셈 연산(3X3)X(3X3)
void Matrix3D::Multiple(const Matrix3D& a, const Matrix3D& b)
{
	m11 = a.m11 * b.m11 + a.m12 * b.m21 + a.m13 * b.m31 + a.m14 * b.m41;
	m12 = a.m11 * b.m12 + a.m12 * b.m22 + a.m13 * b.m32 + a.m14 * b.m42;
	m13 = a.m11 * b.m13 + a.m12 * b.m23 + a.m13 * b.m33 + a.m14 * b.m43;
	m14 = a.m11 * b.m14 + a.m12 * b.m24 + a.m13 * b.m34 + a.m14 * b.m44;

	m21 = a.m21 * b.m11 + a.m22 * b.m21 + a.m23 * b.m31 + a.m24 * b.m41;
	m22 = a.m21 * b.m12 + a.m22 * b.m22 + a.m23 * b.m32 + a.m24 * b.m42;
	m23 = a.m21 * b.m13 + a.m22 * b.m23 + a.m23 * b.m33 + a.m24 * b.m43;
	m24 = a.m21 * b.m14 + a.m22 * b.m24 + a.m23 * b.m34 + a.m24 * b.m44;

	m31 = a.m31 * b.m11 + a.m32 * b.m21 + a.m33 * b.m31 + a.m34 * b.m41;
	m32 = a.m31 * b.m12 + a.m32 * b.m22 + a.m33 * b.m32 + a.m34 * b.m42;
	m33 = a.m31 * b.m13 + a.m32 * b.m23 + a.m33 * b.m33 + a.m34 * b.m43;
	m34 = a.m31 * b.m14 + a.m32 * b.m24 + a.m33 * b.m34 + a.m34 * b.m44;

	m41 = a.m41 * b.m11 + a.m42 * b.m21 + a.m43 * b.m31 + a.m44 * b.m41;
	m42 = a.m41 * b.m12 + a.m42 * b.m22 + a.m43 * b.m32 + a.m44 * b.m42;
	m43 = a.m41 * b.m13 + a.m42 * b.m23 + a.m43 * b.m33 + a.m44 * b.m43;
	m44 = a.m41 * b.m14 + a.m42 * b.m24 + a.m43 * b.m34 + a.m44 * b.m44;
}

//꼭지점(1X3)과 행렬 곱셈 연산(3X3)
VERTEX Multiple(VERTEX v, Matrix3D m)
{
	VERTEX vtx;

	vtx.x = v.x * m.m11 + v.y * m.m21 + v.z * m.m31 + v.w * m.m41;
	vtx.y = v.x * m.m12 + v.y * m.m22 + v.z * m.m32 + v.w * m.m42;
	vtx.z = v.z * m.m13 + v.y * m.m23 + v.z * m.m33 + v.w * m.m43;
	vtx.w = v.w * m.m14 + v.y * m.m24 + v.z * m.m34 + v.w * m.m44;

	return vtx;
}