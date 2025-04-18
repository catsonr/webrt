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
{}

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

float Point::operator[](const int i) const
{
    if(i == 0) return x;
    else if(i == 1) return y;
    else if(i == 2) return z;

    else 
    {
        printf("Point has no member of index %i!", i);
        return NAN;
    }

}