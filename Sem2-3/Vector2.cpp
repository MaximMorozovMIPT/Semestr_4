#include "Vector2.h"

using namespace std;

Vector2::Vector2() :x(0), y(0)
{}

Vector2::Vector2(double _x, double _y): x(_x), y(_y)
{}

ostream& operator <<(ostream& os, const Vector2& other)
{
    os << other.x << " " << other.y;
    return os;
}

istream& operator >>(istream& is, Vector2& other)
{
    is >> other.x >> other.y;
    return is;
}

Vector2 Vector2::operator +(const Vector2& other) const
{
    return {x + other.x, y + other.y};
}

Vector2& Vector2::operator +=(const Vector2& other)
{
    x += other.x;
    y += other.y;
    return *this;
}

Vector2 Vector2::operator-(const Vector2& other) const
{
    return {x - other.x, y - other.y};
}

Vector2& Vector2::operator -=(const Vector2& other)
{
    x -= other.x;
    y -= other.y;
    return *this;
}

double Vector2::operator*(const Vector2& other) const
{
    return x * other.x + y * other.y;
}

double Vector2::operator^(const Vector2& rhs) const
{
    return x * rhs.y - y * rhs.x;
}

Vector2 Vector2::operator*(const double& rhs)
{
    return {x * rhs, y * rhs};
}

Vector2 operator*(const double& lhs, const Vector2& rhs)
{
    return {rhs.x * lhs, rhs.y * lhs};
}

Vector2 Vector2::operator/(const double& rhs)
{
    return {x / rhs, y / rhs};
}

double Vector2::SquareLen()
{
    return x * x + y * y;
}

double Vector2::Len()
{
    return sqrt(this->SquareLen());
}

Vector2 Vector2::Norm()
{
    return *this / this->Len();
}

Vector2 Vector2::Perpendicular()
{
    return {y, -x};
}

Vector2 Vector2::operator -() const
{
    return {-x, -y};
}

Vector2& Vector2::Rotate(double angle)
{
    angle = angle * 3.14159265358979323846 / 180;
    Vector2 tmp = *this;
    x = tmp.x * cos(angle) - tmp.y * sin(angle);
    y = tmp.x * sin(angle) + tmp.y * cos(angle);
    return *this;
}

Vector2 Vector2::GetRotated(double angle)
{
    angle = angle * 3.14159265358979323846 / 180;
    return {x * cos(angle) - y * sin(angle), x * sin(angle) + y * cos(angle)};
}
