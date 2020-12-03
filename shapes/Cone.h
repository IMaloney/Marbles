#ifndef CONE_H
#define CONE_H

#include "Shape.h"
#include "Cylinder.h"

class Cone : public Shape
{
public:
    Cone();
    Cone(int param1, int param2);
    ~Cone();

private:
    int m_param1;
    int m_param2;
    Cylinder m_cylinder;

    std::vector<GLfloat> generateVertexData(int param1, int param2) override;

    glm::vec3 calculateSurfaceNormal(float angle);
};

#endif // CONE_H
