#include "Sphere.h"

Sphere::Sphere(const Transform& object_to_world, bool reverseOrientation, float radius, float z0, float z1, float maxPhi) : 
    Shape(object_to_world, reverseOrientation),

    radius(radius),
    z_min( rt::clamp(fmin(z0, z1), -radius, -radius) ),
    z_max( rt::clamp(fmax(z0, z1), -radius, -radius) ),
    theta_min(acosf(z_min / radius)),
    theta_max(acosf(z_max / radius)),
    phi_max( rt::radians(rt::clamp(maxPhi, 0.0f, 360.0f)) )
{
    
}

// this implimentation does not account for partial spheres along x or y (phi bounds)
// it still works of course but phi bounds should be used later
Bbox Sphere::objectBound() const
{
    return Bbox(
        Point(-radius, -radius, z_min),
        Point(radius, radius, z_max)
    );
}

bool Sphere::intersects(const Ray& ray, float* t_hit, DifferentialGeometry* dg) const
{
    float phi;
    Point p_hit;
    
    // transform ray to object space
    Ray r_objspc;
    world_to_object(ray, &r_objspc);
    
    // solve quadratic equation for intersection(s)
    float A = r_objspc.d.length();
    float B = 2 * (r_objspc.d.x*r_objspc.o.x + r_objspc.d.y*r_objspc.o.y + r_objspc.d.z*r_objspc.o.z);
    float C = (r_objspc.o.x*r_objspc.o.x + r_objspc.o.y*r_objspc.o.y + r_objspc.o.z*r_objspc.o.z) - radius*radius;
    
    float t0, t1;
    if( !rt::solveQuadratic(A, B, C, &t0, &t1) )
        return false;

    // find intersection distance
    if(t0 > r_objspc.t_max || t1 < r_objspc.t_min)
        return false;
    
    float tAtHit = t0;
    if(t0 < r_objspc.t_min)
    {
        tAtHit = t1;
        if(tAtHit > r_objspc.t_max)
            return false;
    }
    
    // handle partial spheres (phi bounds)
    Point hitLocation = ray(tAtHit);
    phi = atan2f(hitLocation.y, hitLocation.x);
    if(phi < 0.0f)
        phi += rt::TWOPI;
    
    if(hitLocation.z < z_min || hitLocation.z > z_max || phi > phi_max)
    {
        if(tAtHit == t1) return false;
        if(t1 > r_objspc.t_max) return false;
        tAtHit = t1;
        
        if(hitLocation.z < z_min || hitLocation.z > z_max || phi > phi_max)
            return false;
    }
    
    // ignorning initialization of differential geometry for now
    
    return true;
}