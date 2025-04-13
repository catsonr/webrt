#ifndef VECTOR_H
#define VECTOR_H

#include <cassert>
#include <math.h>

#include "Normal.h"

// forward definition to break circular dependency
class Normal;

class Vector
{
public:
    float x, y, z;

    Vector();
    Vector(float x, float y, float z);
    explicit Vector(const Normal& n);
    
    float lengthSquared() const;
    float length() const;

    // additon
    Vector operator+(const Vector& v) const;
    Vector &operator+=(const Vector& v);

    // substraction
    Vector operator-(const Vector& v) const;
    Vector &operator-=(const Vector& v);

    // multiplication by scalar
    Vector operator*(float f) const;
    Vector &operator*=(float f);

    // Division by scalar
    Vector operator/(float f) const;
    Vector &operator/=(float f);
    
    // inversion
    Vector operator-() const;
};

// global functions that use only vectors
inline float dot(const Vector& v1, const Vector& v2)
{
    return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}
inline float dotAbs(const Vector& v1, const Vector& v2)
{
    return fabsf(dot(v1, v2));
}
inline Vector cross(const Vector& v1, const Vector& v2)
{
    return Vector(
        v1.y*v2.z - v1.z*v2.y,
        v1.z*v2.x - v1.x*v2.z,
        v1.x*v2.y - v1.y*v2.x
    );
}
inline Vector normalize(const Vector& v)
{
    return v / v.length();
}

#endif