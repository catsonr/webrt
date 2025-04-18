#include "Vector.h"

// constructors
Vector::Vector() :
    x(0.0f),
    y(0.0f),
    z(0.0f)
{}
Vector::Vector(float x, float y, float z) :
    x(x),
    y(y),
    z(z)
{}
Vector::Vector(const Normal& n) :
    x(n.x),
    y(n.y),
    z(n.z)
{}

float Vector::lengthSquared() const
{
    return x * x + y * y + z * z;
}
float Vector::length() const
{
    return sqrtf( lengthSquared() );
}

// addition operator overloads
Vector Vector::operator+(const Vector &v) const
{
    return Vector(x + v.x, y + v.y, z + v.z);
}
Vector& Vector::operator+=(const Vector &v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

// subtraction operator overloads
Vector Vector::operator-(const Vector &v) const
{
    return Vector(x - v.x, y - v.y, z - v.z);
}
Vector& Vector::operator-=(const Vector &v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

// multiplication operator overloads
Vector Vector::operator*(float f) const
{
    return Vector(x * f, y * f, z * f);
}
Vector& Vector::operator*=(float f)
{
    x *= f;
    y *= f;
    z *= f;
    return *this;
}

// division operator overloads
Vector Vector::operator/(float f) const
{
    assert(f != 0);
    float inverse = 1.0f / f;
    return Vector(x * inverse, y * inverse, z * inverse);
}
Vector& Vector::operator/=(float f)
{
    assert(f != 0);
    float inverse = 1.0f / f;
    x *= inverse;
    y *= inverse;
    z *= inverse;
    return *this;
}

// inversion operator overload
Vector Vector::operator-() const
{
    return Vector(-x, -y, -z);
}

// array access operator overload
float Vector::operator[](const int i) const
{
    if(i == 0) return x;
    else if(i == 1) return y;
    else if(i == 2) return z;

    else 
    {
        printf("Vector has no member of index %i!", i);
        return NAN;
    }
}