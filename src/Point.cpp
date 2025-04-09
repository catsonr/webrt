#include "Point.h"

Point::Point() :
    x(0.0f),
    y(0.0f),
    z(0.0f)
{}
Point::Point(float x, float y, float z) :
    x(x),
    y(y),
    z(z)
{
    
}

Point Point::operator+(const Vector& v) const
{
    return Point(x + v.x, y + v.y, z + v.z);
}
Point& Point::operator+=(const Vector& v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Point Point::operator-(const Vector& v) const
{
    return Point(x - v.x, y - v.y, z - v.z);
}
Point& Point::operator-=(const Vector& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}
Vector Point::operator-(const Point& p) const
{
    return Vector(x - p.x, y - p.y, z - p.z);
}