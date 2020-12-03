#ifndef CONE_H
#define CONE_H

#include "Shape.h"
#include "shapes/Faces/TessalatedTriangle.h"
#include "shapes/Faces/Circle.h"

class Cone
    : public Shape
{
public:
    Cone(int param1, int param2);
    virtual ~Cone();

protected:
    virtual std::vector<float> buildShape();

    void buildBase(std::vector<float> *ret, float angle);
    void buildFaces(std::vector<float> *ret, float angle);

    std::unique_ptr<Circle> m_base;
    std::unique_ptr<TessalatedTriangle> m_side;
};

#endif // CONE_H
