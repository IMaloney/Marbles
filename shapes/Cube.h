#ifndef CUBE_H
#define CUBE_H

# include "Shape.h"
#include "shapes/Faces/Rectangle.h"

class Cube
    : public Shape
{
public:
    Cube(int param1);
    virtual ~Cube();

protected:

    virtual std::vector<float> buildShape();
    void buildFace(Point p);
    std::vector<float> m_points;
    std::vector<float> m_face;
};

#endif // CUBE_H
