#pragma once
#include <iostream>
#include <fstream>

class Vector2D 
{
public:
    float x;
    float y;

    // 생성자
    Vector2D(float x = 0.0f, float y = 0.0f);

    // 연산자 오버로딩
    Vector2D operator+(const Vector2D& other) const;
    Vector2D operator-(const Vector2D& other) const;
    Vector2D operator*(float scalar) const;
    Vector2D operator/(float scalar) const;

    Vector2D& operator+=(const Vector2D& other);
    Vector2D& operator-=(const Vector2D& other);
    Vector2D& operator*=(float scalar);
    Vector2D& operator/=(float scalar);

    bool operator==(const Vector2D& other) const;
    bool operator!=(const Vector2D& other) const;

    // 벡터 연산
    float dot(const Vector2D& other) const;   // 내적
    float cross(const Vector2D& other) const; // 외적 (2D에서는 스칼라)
    float length() const;
    float lengthSquared() const;
    Vector2D normalize() const;
    float angle() const;                      // x축 기준 각도 (라디안)
    float angleBetween(const Vector2D& other) const; // 두 벡터 사이 각도

    // 거리 관련
    float distance(const Vector2D& other) const;
    float distanceSquared(const Vector2D& other) const;

    // 보조 함수
    Vector2D perpendicular() const;  // 수직 벡터
    Vector2D lerp(const Vector2D& other, float t) const; // 보간

    // 출력
    void print() const;

    // 정적 메서드
    static Vector2D Zero();
    static Vector2D One();
    static Vector2D UnitX();
    static Vector2D UnitY();
};

std::ostream& operator<<(std::ostream& os, const Vector2D& v);
std::istream& operator>>(std::istream& is, Vector2D& v);