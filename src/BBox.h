#ifndef BBOX_H
#define BBOX_H

#include "Point.h"

class BBox
{
public:
    BBox();
    BBox(const Point& p);
    BBox(const Point& p1, const Point& p2);
    
    Point pMin, pMax;
};

#endif