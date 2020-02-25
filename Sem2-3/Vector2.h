#pragma once
#include <iostream>
#include <cmath>

using namespace std;

class Vector2
{
public:
    Vector2();
    Vector2(double _x, double _y);

    Vector2 operator+(const Vector2& other) const;//
    Vector2& operator+=(const Vector2& other);//
    Vector2 operator-(const Vector2& other) const;//
    Vector2& operator-=(const Vector2& other);//

    double operator*(const Vector2& other) const;//
    double operator^(const Vector2& rhs) const;//

    Vector2 operator*(const double& rhs);//
    Vector2 operator/(const double& rhs);//

    double SquareLen();//
    double Len();//
    Vector2 Norm();//
    Vector2 Perpendicular();//
    Vector2 operator-() const;//
    Vector2& Rotate(double angle);
    Vector2 GetRotated(double angle);//

    double x, y;
};

ostream& operator <<(ostream& os, const Vector2& other);//
istream& operator >>(istream& is, Vector2& other);//


Vector2 operator*(const double& lhs, const Vector2& rhs);//
