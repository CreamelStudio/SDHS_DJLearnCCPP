#include "pch.h"
#include "Vector2D.h"
#include <cmath>

// 생성자
Vector2D::Vector2D(float x, float y) : x(x), y(y) {}

// 연산자 오버로딩  //벡터 사칙연산
Vector2D Vector2D::operator+(const Vector2D& other) const 
{
    return Vector2D(x + other.x, y + other.y);
}

Vector2D Vector2D::operator-(const Vector2D& other) const 
{
    return Vector2D(x - other.x, y - other.y);
}

Vector2D Vector2D::operator*(float scalar) const 
{
    return Vector2D(x * scalar, y * scalar);
}

Vector2D Vector2D::operator/(float scalar) const 
{
    return Vector2D(x / scalar, y / scalar);
}

Vector2D& Vector2D::operator+=(const Vector2D& other) 
{
    x += other.x;
    y += other.y;
    return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& other) 
{
    x -= other.x;
    y -= other.y;
    return *this;
}

Vector2D& Vector2D::operator*=(float scalar) 
{
    x *= scalar;
    y *= scalar;
    return *this;
}

Vector2D& Vector2D::operator/=(float scalar) 
{
    x /= scalar;
    y /= scalar;
    return *this;
}

bool Vector2D::operator==(const Vector2D& other) const 
{
    return (x == other.x && y == other.y);
}

bool Vector2D::operator!=(const Vector2D& other) const 
{
    return !(*this == other);
}

// 벡터 연산
float Vector2D::dot(const Vector2D& other) const //내적
{
    return x * other.x + y * other.y;
}

float Vector2D::cross(const Vector2D& other) const //외적
{
    return x * other.y - y * other.x;
}

float Vector2D::length() const 
{
    return std::sqrt(x * x + y * y);
}

float Vector2D::lengthSquared() const 
{
    return x * x + y * y;
}

Vector2D Vector2D::normalize() const 
{
    float len = length();
    if (len == 0) return Vector2D(0, 0);
    return Vector2D(x / len, y / len);
}

float Vector2D::angle() const 
{
    return std::atan2(y, x);
}

//내적을 한 각도 구하기
float Vector2D::angleBetween(const Vector2D& other) const 
{
    float dotProd = dot(other);
    float lengths = length() * other.length();
    if (lengths == 0) return 0.0f;
    float cosTheta = dotProd / lengths;
    if (cosTheta > 1.0f) cosTheta = 1.0f;
    if (cosTheta < -1.0f) cosTheta = -1.0f;
    return std::acos(cosTheta);
}

// 거리
float Vector2D::distance(const Vector2D& other) const 
{
    return (*this - other).length();
}

float Vector2D::distanceSquared(const Vector2D& other) const 
{
    return (*this - other).lengthSquared();
}

// 수직 벡터
Vector2D Vector2D::perpendicular() const 
{
    return Vector2D(-y, x);
}

// 보간
Vector2D Vector2D::lerp(const Vector2D& other, float t) const 
{
    return (*this) + (other - (*this)) * t;
}

// 스트림 출력
std::ostream& operator<<(std::ostream& os, const Vector2D& v) 
{
    os << (float)v.x << " " << (float)v.y;
    return os;
}

// 스트림 입력
std::istream& operator>>(std::istream& is, Vector2D& v)
{
    is >> v.x >> v.y;
    return is;
}

// 정적 메서드
Vector2D Vector2D::Zero() { return Vector2D(0, 0); }
Vector2D Vector2D::One() { return Vector2D(1, 1); }
Vector2D Vector2D::UnitX() { return Vector2D(1, 0); }
Vector2D Vector2D::UnitY() { return Vector2D(0, 1); }
