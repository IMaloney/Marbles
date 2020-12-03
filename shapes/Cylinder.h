#ifndef CYLINDER_H
#define CYLINDER_H

#include "Shape.h"
#include "shapes/Faces/Circle.h"
#include "shapes/Faces/Rectangle.h"
#include "shapes/Faces/AtomicTriangle.h"

class Cylinder
    : public Shape
{
public:
    Cylinder(int param1, int param2);
    virtual ~Cylinder();

protected:
    virtual std::vector<float> buildShape();
    void buildSides(std::vector<float> *ret, float angle);
    void buildCaps(std::vector<float> *ret, float angle);
    std::unique_ptr<Circle> m_top;
};

#endif // CYLINDER_H
