#ifndef CYLINDER_H
#define CYLINDER_H

#include "Shape.h"

class Cylinder : public Shape
{
public:
    Cylinder();
    Cylinder(int param1, int param2);
    ~Cylinder();

    std::vector<GLfloat> generateAngleVector(int numSlices);
    std::vector<GLfloat> generatePositionVector(float angle, float z, float radius);

private:
    int m_param1;
    int m_param2;

    std::vector<GLfloat> generateVertexData(int param1, int param2) override;
};

#endif // CYLINDER_H
