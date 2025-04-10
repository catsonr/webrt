#ifndef MAT4_H
#define MAT4_H

#include <memory.h>
#include <iostream>

#include <cmath>
#include <algorithm>

class Mat4
{
private:
    static const int ROWS = 4;
    static const int COLS = 4;
    static const int ELEMS = 16;


public:
    float m[ROWS][4];

    Mat4();
    Mat4(float _m[ELEMS]);
    Mat4(float _m[ROWS][COLS]);
    Mat4(float t00, float t01, float t02, float t03,
         float t10, float t11, float t12, float t13,
         float t20, float t21, float t22, float t23,
         float t30, float t31, float t32, float t33);
    
    std::shared_ptr<Mat4> transpose() const;
    std::shared_ptr<Mat4> multiply(const std::shared_ptr<Mat4> m1, const std::shared_ptr<Mat4> m2) const;
    std::shared_ptr<Mat4> inverse() const;
};

#endif