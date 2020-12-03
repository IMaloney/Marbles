#ifndef SPHERE_H
#define SPHERE_H

#include "Shape.h"
#include "shapes/Faces/AtomicTriangle.h"
#include "shapes/Faces/Rectangle.h"

class Sphere
    : public Shape
{
public:
    Sphere(int param1, int param2);
    virtual ~Sphere();

protected:
    virtual std::vector<float> buildShape();
    AtomicTriangle buildHalves(std::vector<float> *ret, float xyAngle, float xzAngle);
    void buildBody(std::vector<float> *ret, int numTriangles, float xyAngle, float xzAngle);
    void buildSides(std::vector<float> *ret, std::vector<float> temp, float xzAngle);
};

#endif // SPHERE_H
