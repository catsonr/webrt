#ifndef BBOX_H
#define BBOX_H

#include <algorithm>

#include "Point.h"
#include "Ray.h"

class Bbox
{
public:
    // default 0 Bbox
    Bbox();
    // enclosing a Bbox around a single point
    Bbox(const Point& p);
    // enclosing a Bbox from p1 to p2
    Bbox(const Point& p1, const Point& p2);

    // returns if b is within bbox
    bool overlaps(const Bbox& b) const;
    // returns if point p is within bbox
    bool containsPoint(const Point& p) const; // called inside() in pbrt
    // returns true if ray intersects and false if it doesn't. updates t_hit0 and t_hit1 accordingly
    bool intersectP(const Ray& ray, float* t_hit0, float* t_hit1) const;
    // returns the volume of the bbox
    float volume() const;
    // returns which of the three axes is the longest
    // x=0  y=1  z=2
    int maxmimumExtent() const;
    
    // expands box to contain point p
    Bbox Union(const Bbox& box, const Point& p);
    // expands box1 to contain box2
    Bbox Union(const Bbox& box1, const Bbox& box2);
    // expands box by a constant factor delta
    void expand(float delta);

    Point pMin, pMax;
};

#endif