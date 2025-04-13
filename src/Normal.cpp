#include "Normal.h"

Normal::Normal() :
    x(0.0f),
    y(0.0f),
    z(0.0f)
{}
Normal::Normal(float x, float y, float z) :
    x(x),
    y(y),
    z(z)
{}
Normal::Normal(const Vector& v) :
    x(v.x),
    y(v.y),
    z(v.z)
{}

float Normal::lengthSquared() const
{
    return x * x + y * y + z * z;
}
float Normal::length() const
{
    return sqrtf( lengthSquared() );
}

// addition operator overloads
Normal Normal::operator+(const Normal &n) const
{
    return Normal(x + n.x, y + n.y, z + n.z);
}
Normal& Normal::operator+=(const Normal &n)
{
    x += n.x;
    y += n.y;
    z += n.z;
    return *this;
}

// subtraction operator overloads
Normal Normal::operator-(const Normal &n) const
{
    return Normal(x - n.x, y - n.y, z - n.z);
}
Normal& Normal::operator-=(const Normal &n)
{
    x -= n.x;
    y -= n.y;
    z -= n.z;
    return *this;
}

// multiplication operator overloads
Normal Normal::operator*(float f) const
{
    return Normal(x * f, y * f, z * f);
}
Normal& Normal::operator*=(float f)
{
    x *= f;
    y *= f;
    z *= f;
    return *this;
}

// division operator overloads
Normal Normal::operator/(float f) const
{
    assert(f != 0);
    float inverse = 1.0f / f;
    return Normal(x * inverse, y * inverse, z * inverse);
}
Normal& Normal::operator/=(float f)
{
    assert(f != 0);
    float inverse = 1.0f / f;
    x *= inverse;
    y *= inverse;
    z *= inverse;
    return *this;
}

// inversion operator overload
Normal Normal::operator-() const
{
    return Normal(-x, -y, -z);
}