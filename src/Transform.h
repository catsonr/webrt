#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Mat4.h"
#include "Vector.h"
#include "Point.h"

class Transform
{
public:
    std::shared_ptr<Mat4> m, mInv;

    Transform();
    Transform(const std::shared_ptr<Mat4> m);
    Transform(const std::shared_ptr<Mat4> _m, const std::shared_ptr<Mat4> _mInv);
    Transform(float m[4][4]);

    Transform translate(const Vector& delta);
    Transform scale(float x, float y, float z);
    Transform rotateX(float angle);
    Transform rotateY(float angle);
    Transform rotateZ(float angle);
    Transform rotate(const Vector& axis, float angle);
    
    Transform lookAt(const Point& pos, const Point& lookingAt, const Vector& up);
    
    // transform inline functions
    inline Point operator()(const Point& p) const // transforming a point
    {
        float xp = m->m[0][0]*p.x + m->m[0][1]*p.y + m->m[0][2]*p.z + m->m[0][3];
        float yp = m->m[1][0]*p.x + m->m[1][1]*p.y + m->m[1][2]*p.z + m->m[1][3];
        float zp = m->m[2][0]*p.x + m->m[2][1]*p.y + m->m[2][2]*p.z + m->m[2][3];
        float wp = m->m[3][0]*p.x + m->m[3][1]*p.y + m->m[3][2]*p.z + m->m[3][3];
        
        assert(wp != 0);
        if(wp == 1.0) return Point(xp, yp, zp);
        else return Point(xp / wp, yp / wp, zp / wp);
    }
    inline void operator()(const Point& p, Point* ptrans) const // transforming a point in place
    {
        ptrans->x = m->m[0][0]*p.x + m->m[0][1]*p.y + m->m[0][2]*p.z + m->m[0][3];
        ptrans->y = m->m[1][0]*p.x + m->m[1][1]*p.y + m->m[1][2]*p.z + m->m[1][3];
        ptrans->z = m->m[2][0]*p.x + m->m[2][1]*p.y + m->m[2][2]*p.z + m->m[2][3];
        float w   = m->m[3][0]*p.x + m->m[3][1]*p.y + m->m[3][2]*p.z + m->m[3][3];
        
        if(w != 1.0f)
        {
            ptrans->x /= w;
            ptrans->y /= w;
            ptrans->z /= w;
        }
    }
    inline Vector operator()(const Vector& v) const // transforming a vector
    {
        return Vector(
            m->m[0][0] * v.x + m->m[0][1] * v.y + m->m[0][2] * v.z + m->m[0][3],
            m->m[1][0] * v.x + m->m[1][1] * v.y + m->m[1][2] * v.z + m->m[1][3],
            m->m[2][0] * v.x + m->m[2][1] * v.y + m->m[2][2] * v.z + m->m[2][3]);
    }
    inline void operator()(const Vector &v, Vector *vtrans) const // translating a vector in place
    {
        vtrans->x = m->m[0][0] * v.x + m->m[0][1] * v.y + m->m[0][2] * v.z + m->m[0][3];
        vtrans->y = m->m[1][0] * v.x + m->m[1][1] * v.y + m->m[1][2] * v.z + m->m[1][3];
        vtrans->z = m->m[2][0] * v.x + m->m[2][1] * v.y + m->m[2][2] * v.z + m->m[2][3];
    }
};

#endif