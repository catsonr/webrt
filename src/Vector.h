#ifndef VECTOR_H
#define VECTOR_H

#include <cassert>
#include <math.h>

class Vector
{
public:
    Vector(float x, float y, float z);
    
    float lengthSquared() const;
    float length() const;

    // additon
    Vector operator+(const Vector &v) const;
    Vector &operator+=(const Vector &v);

    // substraction
    Vector operator-(const Vector &v) const;
    Vector &operator-=(const Vector &v);

    // multiplication by scalar
    Vector operator*(float f) const;
    Vector &operator*=(float f);

    // Division by scalar
    Vector operator/(float f) const;
    Vector &operator/=(float f);
    
    // inversion
    Vector operator-() const;
    
    float x;
    float y;
    float z;
};

#endif