#ifndef NORMAL_H
#define NORMAL_H

#include "Vector.h"

// forward definition to break circular dependency
class Vector;

class Normal
{
public:
    float x, y, z;
    
    Normal(float x, float y, float z);
    explicit Normal(const Vector& v);

    float lengthSquared() const;
    float length() const;

    // additon
    Normal operator+(const Normal& v) const;
    Normal &operator+=(const Normal &v);

    // substraction
    Normal operator-(const Normal& v) const;
    Normal &operator-=(const Normal& v);

    // multiplication by scalar
    Normal operator*(float f) const;
    Normal &operator*=(float f);

    // Division by scalar
    Normal operator/(float f) const;
    Normal &operator/=(float f);
    
    // inversion
    Normal operator-() const;
};

// global functions that use only normals
inline float dot(const Normal& n1, const Normal& n2)
{
    return n1.x*n2.x + n1.y*n2.y + n1.z*n2.z;
}
inline float dotAbs(const Normal& n1, const Normal& n2)
{
    return fabsf(dot(n1, n2));
}
inline Normal normalize(const Normal& n)
{
    return n / n.length();
}

#endif