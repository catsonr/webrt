#include "DifferentialGeometry.h"

DifferentialGeometry::DifferentialGeometry(const Point& P,
        const Vector& DPDU, const Vector& DPDV,
        const Vector& DNDU, const Vector& DNDV,
        float uu, float vv, const Shape* sh) :
    p(P),
    dpdu(DPDU),
    dpdv(DPDV),
    dndu(DNDU),
    dndv(DNDV),
    nn(normalize(cross(dpdu, dpdv))),
    u(uu),
    v(vv),
    shape(sh)
{
    if(shape->reverseOrientation ^ shape->transformSwapsHandedness)
        nn *= -1.0f;
}

void DifferentialGeometry::computeDifferentials(const RayDifferential& ray) const
{
    if(ray.hasDifferentials)
    {
        // estimate screen space change in p and (u, v)

        // compute auxiliary intersection points with plane
        float d = -dot(Vector(nn), Vector(p.x, p.y, p.z));
        Vector rxv(ray.rx.o.x, ray.rx.o.y, ray.rx.o.z);
        float tx = -(dot(Vector(nn), rxv) + d) / dot(Vector(nn), ray.rx.d);
        Point px = ray.rx.o + ray.rx.d * tx;
        Vector ryv(ray.ry.o.x, ray.ry.o.y, ray.ry.o.z);
        float ty = -(dot(Vector(nn), ryv) + d) / dot(Vector(nn), ray.ry.d);
        Point py = ray.ry.o + ray.ry.d * ty;

        dpdx = px - p;
        dpdy = py - p;
        
        // initialize A, Bx, and By matrices for offset computation
        float A[2][2], Bx[2], By[2], x[2];
        int axes[2];
        if(fabsf(nn.x) > fabsf(nn.y) && fabsf(nn.x) > fabsf(nn.z))
        {
            axes[0] = 1;
            axes[1] = 2;
        }
        else if(fabsf(nn.y) > fabsf(nn.z))
        {
            axes[0] = 0;
            axes[1] = 2;
        }
        else
        {
            axes[0] = 0;
            axes[1] = 1;
        }

        // intialize matrices for chosen projection plane
        A[0][0] = dpdu[axes[0]];
        A[0][1] = dpdu[axes[0]];
        A[1][0] = dpdu[axes[1]];
        A[1][1] = dpdu[axes[1]];

        Bx[0] = px[axes[0]] - p[axes[0]];
        Bx[1] = px[axes[1]] - p[axes[1]];
        By[0] = px[axes[0]] - p[axes[0]];
        By[1] = px[axes[1]] - p[axes[1]];
        
        if(rt::solveLinearSystem2x2(A, Bx, x))
        {
            dudx = x[0];
            dvdx = x[1];
        }
        else
        {
            dudx = 1.0f;
            dvdx = 0.0f;
        }
        
        if(rt::solveLinearSystem2x2(A, By, x))
        {
            dudy = x[0];
            dvdy = x[1];
        }
        else
        {
            dudy = 0.0f;
            dvdy = 1.0f;
        }
        
    }
    else
    {
        dudx = dvdx = 0.0f;
        dudy = dvdy = 0.0f;
        dpdx = dpdy = Vector(0.0f, 0.0f, 0.0f);
    }
}
