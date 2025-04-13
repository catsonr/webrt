#ifndef BBOX_H
#define BBOX_H

#include "Point.h"

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