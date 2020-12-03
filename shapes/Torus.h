#ifndef TORUS_H
#define TORUS_H

#include "Shape.h"
#include "Cylinder.h"

#include <iostream>

class Torus : public Shape
{
public:
    Torus();
    Torus(int param1, int param2, float param3);
    ~Torus();

private:
    int m_param1;
    int m_param2;
    Cylinder m_cylinder;

    std::vector<GLfloat> generateVertexData(int param1, int param2, float param3);
//    std::vector<GLfloat> generateCornerAngleVector(int param1);
    glm::vec3 torusToCartesian(float a, float c, float v, float u);
    void addPoint(std::vector<GLfloat>* data, glm::vec3 point);
    void calculateAndAddNormal(std::vector<GLfloat>* data, float u, float v);
};

#endif // TORUS_H
