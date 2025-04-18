#ifndef POINT_H
#define POINT_H

#include "Vector.h"

class Point
{
public:
    Point();
    Point(float x, float y, float z);
    
    Point operator+(const Vector& v) const;
    Point& operator+=(const Vector& v);

    Point operator-(const Vector& v) const;
    Point& operator-=(const Vector& v);
    Vector operator-(const Point& p) const;
    
    float operator[](const int i) const;

    float x;
    float y;
    float z;
};

#endif