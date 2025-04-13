#include "Bbox.h"

// constructors 
Bbox::Bbox() :
    pMin(Point(INFINITY, INFINITY, INFINITY)),
    pMax(Point(-INFINITY, -INFINITY, -INFINITY))
{}
Bbox::Bbox(const Point& p) :
    pMin(p),
    pMax(p)
{}
Bbox::Bbox(const Point& p1, const Point& p2)
{
    const float xmin = fmin(p1.x, p2.x);
    const float xmax = fmax(p1.x, p2.x);

    const float ymin = fmin(p1.y, p2.y);
    const float ymax = fmax(p1.y, p2.y);

    const float zmin = fmin(p1.z, p2.z);
    const float zmax = fmax(p1.z, p2.z);
    
    pMin = Point(xmin, ymin, zmin);
    pMax = Point(xmax, ymax, zmax);
}

// functions
bool Bbox::overlaps(const Bbox& box) const
{
    bool x = (pMax.x >= box.pMin.x) && (pMin.x <= box.pMax.x);
    bool y = (pMax.y >= box.pMin.y) && (pMin.y <= box.pMax.y);
    bool z = (pMax.z >= box.pMin.z) && (pMin.z <= box.pMax.z);
    
    return x && y && z;
}
bool Bbox::containsPoint(const Point& p) const
{
    return (
        p.x >= pMin.x && p.x <= pMax.x &&
        p.y >= pMin.y && p.y <= pMax.y &&
        p.z >= pMin.z && p.z <= pMax.z
    );
}
float Bbox::volume() const
{
    return (pMax.x - pMin.x) * (pMax.y - pMin.y) * (pMax.z - pMin.z);
}
int Bbox::maxmimumExtent() const
{
    Vector d = pMax - pMin;
    
    if(d.x > d.y && d.x > d.z)
        return 0;
    else if(d.y > d.z)
        return 1;
    
    return 2;
}

Bbox Bbox::Union(const Bbox& box, const Point& p)
{
    Bbox newbox = box;
    
    newbox.pMin.x = fmin(box.pMin.x, p.x);
    newbox.pMin.y = fmin(box.pMin.y, p.y);
    newbox.pMin.z = fmin(box.pMin.z, p.z);

    newbox.pMax.x = fmax(box.pMax.x, p.x);
    newbox.pMax.y = fmax(box.pMax.y, p.y);
    newbox.pMax.z = fmax(box.pMax.z, p.z);
    
    return newbox;
}
Bbox Bbox::Union(const Bbox& box1, const Bbox& box2)
{
    Bbox newbox = box1;

    newbox.pMin.x = fmin(box1.pMin.x, box2.pMin.x);
    newbox.pMin.y = fmin(box1.pMin.y, box2.pMin.y);
    newbox.pMin.z = fmin(box1.pMin.z, box2.pMin.z);
    
    newbox.pMax.x = fmax(box1.pMax.x, box2.pMax.x);
    newbox.pMax.y = fmax(box1.pMax.y, box2.pMax.y);
    newbox.pMax.z = fmax(box1.pMax.z, box2.pMax.z);
    
    return newbox;
}

void Bbox::expand(float delta)
{
    Vector d(delta, delta, delta);
    
    pMin -= d;
    pMax += d;
}