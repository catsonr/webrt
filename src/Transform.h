#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Mat4.h"
#include "Vector.h"
#include "Point.h"
#include "Ray.h"
#include "Bbox.h"

class Transform
{
public:
    std::shared_ptr<Mat4> m, mInv;

    Transform();
    Transform(const std::shared_ptr<Mat4> m);
    Transform(const std::shared_ptr<Mat4> _m, const std::shared_ptr<Mat4> _mInv);
    Transform(float m[4][4]);
    
    bool swapsHandedness() const;

    Transform translate(const Vector& delta);
    Transform scale(float x, float y, float z);
    Transform rotateX(float angle);
    Transform rotateY(float angle);
    Transform rotateZ(float angle);
    Transform rotate(const Vector& axis, float angle);
    
    Transform lookAt(const Point& pos, const Point& lookingAt, const Vector& up);
    
    void print() const;
    
    // transform inline functions

    // points
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

     // vectors
    inline Vector operator()(const Vector& v) const // transforming a vector
    {
        return Vector(
            m->m[0][0] * v.x + m->m[0][1] * v.y + m->m[0][2] * v.z + m->m[0][3],
            m->m[1][0] * v.x + m->m[1][1] * v.y + m->m[1][2] * v.z + m->m[1][3],
            m->m[2][0] * v.x + m->m[2][1] * v.y + m->m[2][2] * v.z + m->m[2][3]);
    }
    inline void operator()(const Vector &v, Vector *vtrans) const // transforming a vector in place
    {
        vtrans->x = m->m[0][0] * v.x + m->m[0][1] * v.y + m->m[0][2] * v.z + m->m[0][3];
        vtrans->y = m->m[1][0] * v.x + m->m[1][1] * v.y + m->m[1][2] * v.z + m->m[1][3];
        vtrans->z = m->m[2][0] * v.x + m->m[2][1] * v.y + m->m[2][2] * v.z + m->m[2][3];
    }
    
    // normals
    inline Normal operator()(const Normal& n) const // transforming a normal 
    {
        return Normal(
                mInv->m[0][0]*n.x + mInv->m[1][0]*n.y + mInv->m[2][0]*n.z,
                mInv->m[0][1]*n.x + mInv->m[1][1]*n.y + mInv->m[2][1]*n.z,
                mInv->m[0][2]*n.x + mInv->m[1][2]*n.y + mInv->m[2][2]*n.z
        );
    }
    inline void operator()(const Normal &n, Normal* ntrans) const // transforming a normal in place
    {
        ntrans->x = mInv->m[0][0] * n.x + mInv->m[0][1] * n.y + mInv->m[0][2] * n.z + mInv->m[0][3];
        ntrans->y = mInv->m[1][0] * n.x + mInv->m[1][1] * n.y + mInv->m[1][2] * n.z + mInv->m[1][3];
        ntrans->z = mInv->m[2][0] * n.x + mInv->m[2][1] * n.y + mInv->m[2][2] * n.z + mInv->m[2][3];
    }
    
    // rays
    inline Ray operator()(const Ray& ray) const // transforming a ray
    {
        Ray ret;
        (*this)(ray.o, &ret.o);
        (*this)(ray.d, &ret.d);
        
        ret.t_min = ray.t_min;
        ret.t_max = ray.t_max;
        
        return ret;
    }
    inline void operator()(const Ray& ray, Ray* rtrans) const // transforming a ray in place
    {
        rtrans->o = (*this)(ray.o);
        rtrans->d = (*this)(ray.d);
        
        rtrans->t_min = ray.t_min;
        rtrans->t_max = ray.t_max;
    }
    
    // bboxes 
    inline Bbox operator()(const Bbox& box) const // transforming a bbox
    {
        const Transform& M = *this;
        
        Bbox ret(            M(Point(box.pMin.x, box.pMin.y, box.pMin.z)));
        ret = ret.Union(ret, M(Point(box.pMax.x, box.pMin.y, box.pMin.z)));
        ret = ret.Union(ret, M(Point(box.pMin.x, box.pMax.y, box.pMin.z)));
        ret = ret.Union(ret, M(Point(box.pMin.x, box.pMin.y, box.pMax.z)));
        ret = ret.Union(ret, M(Point(box.pMin.x, box.pMax.y, box.pMax.z)));
        ret = ret.Union(ret, M(Point(box.pMax.x, box.pMax.y, box.pMin.z)));
        ret = ret.Union(ret, M(Point(box.pMax.x, box.pMin.y, box.pMax.z)));
        ret = ret.Union(ret, M(Point(box.pMax.x, box.pMax.y, box.pMax.z)));
        
        return ret;
    }
};

#endif