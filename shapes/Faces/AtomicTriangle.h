#ifndef ATOMICTRIANGLE_H
#define ATOMICTRIANGLE_H

#include "Triangle.h"

class AtomicTriangle :
        public Triangle
{
public:
    AtomicTriangle(Point p1, Point p2, Point p3);
    virtual ~AtomicTriangle();

protected:
    virtual void generatePoints();
};

#endif // ATOMICTRIANGLE_H
