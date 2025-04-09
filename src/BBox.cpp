#include "BBox.h"

BBox::BBox() :
    pMin(Point(INFINITY, INFINITY, INFINITY)),
    pMax(Point(-INFINITY, -INFINITY, -INFINITY))
{}
BBox::BBox(const Point& p) :
    pMin(p),
    pMax(p)
{}
BBox::BBox(const Point& p1, const Point& p2)
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