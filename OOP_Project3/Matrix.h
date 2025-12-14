#pragma once

//Desc : 2D 꼭지점 정의 
typedef struct tagVertex
{
	tagVertex() : x(0.0f), y(0.0f), w(1.0f) {}
	tagVertex(float _x, float _y, float _w = 1.0f) : x(_x), y(_y), w(_w) {}
	union
	{
		struct
		{
			float x, y, z, w; //x, y좌표 , w 동차좌표는 항상 1
		};
		float p[3];
	};
}VERTEX;

//Desc : 2D연산을 위한 3X3행렬
class Matrix3D
{
public:
	union
	{
		struct
		{
			float m11, m12, m13, m14;
			float m21, m22, m23, m24;
			float m31, m32, m33, m34;
			float m41, m42, m43, m44;
		};
		float m[4][4];
	};

public:
	void Identity(void);
	void ZeroMatrix(void);
	void Move(int dx, int dy, int dz);
	void RotateX(float theta);
	void RotateY(float theta);
	void RotateZ(float theta);
	void Scale(float s);
	
	void Multiple(const Matrix3D& a, const Matrix3D& b);
	Matrix3D operator*(const Matrix3D& other) const
	{
		Matrix3D r;

		r.m11 = m11 * other.m11 + m12 * other.m21 + m13 * other.m31 + m14 * other.m41;
		r.m12 = m11 * other.m12 + m12 * other.m22 + m13 * other.m32 + m14 * other.m42;
		r.m13 = m11 * other.m13 + m12 * other.m23 + m13 * other.m33 + m14 * other.m43;
		r.m14 = m11 * other.m14 + m12 * other.m24 + m13 * other.m34 + m14 * other.m44;

		r.m21 = m21 * other.m11 + m22 * other.m21 + m23 * other.m31 + m24 * other.m41;
		r.m22 = m21 * other.m12 + m22 * other.m22 + m23 * other.m32 + m24 * other.m42;
		r.m23 = m21 * other.m13 + m22 * other.m23 + m23 * other.m33 + m24 * other.m43;
		r.m24 = m21 * other.m14 + m22 * other.m24 + m23 * other.m34 + m24 * other.m44;

		r.m31 = m31 * other.m11 + m32 * other.m21 + m33 * other.m31 + m34 * other.m41;
		r.m32 = m31 * other.m12 + m32 * other.m22 + m33 * other.m32 + m34 * other.m42;
		r.m33 = m31 * other.m13 + m32 * other.m23 + m33 * other.m33 + m34 * other.m43;
		r.m34 = m31 * other.m14 + m32 * other.m24 + m33 * other.m34 + m34 * other.m44;

		r.m41 = m41 * other.m11 + m42 * other.m21 + m43 * other.m31 + m44 * other.m41;
		r.m42 = m41 * other.m12 + m42 * other.m22 + m43 * other.m32 + m44 * other.m42;
		r.m43 = m41 * other.m13 + m42 * other.m23 + m43 * other.m33 + m44 * other.m43;
		r.m44 = m41 * other.m14 + m42 * other.m24 + m43 * other.m34 + m44 * other.m44;

		return r;
	}

};

inline VERTEX operator*(const VERTEX& v, const Matrix3D& m)
{
	VERTEX r;
	r.x = v.x * m.m11 + v.y * m.m21 + v.z * m.m31 + v.w * m.m41;
	r.y = v.x * m.m12 + v.y * m.m22 + v.z * m.m32 + v.w * m.m42;
	r.z = v.x * m.m13 + v.y * m.m23 + v.z * m.m33 + v.w * m.m43;
	r.w = v.x * m.m14 + v.y * m.m24 + v.z * m.m34 + v.w * m.m44;
	return r;
}


inline VERTEX operator*(const Matrix3D& m, const VERTEX& v)
{
	VERTEX r; 
	r.x = m.m11 * v.x + m.m12 * v.y + m.m13 * v.z + m.m14 * v.w;
	r.y = m.m21 * v.x + m.m22 * v.y + m.m23 * v.z + m.m24 * v.w;
	r.z = m.m31 * v.x + m.m32 * v.y + m.m33 * v.z + m.m34 * v.w;
	r.w = m.m41 * v.x + m.m42 * v.y + m.m43 * v.z + m.m44 * v.w;
	return r;
}


VERTEX Multiple(VERTEX v, Matrix3D m);


