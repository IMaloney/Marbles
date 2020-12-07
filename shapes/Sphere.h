#ifndef SPHERE_H
#define SPHERE_H

#include "Shape.h"
#include "Cylinder.h"

class Sphere : public Shape
{
public:
    Sphere();
    Sphere(float radius);
    Sphere(int param1, int param2, float radius);
    ~Sphere();

    std::vector<GLfloat> getVetexData() { return m_vertexData; }

protected:
    int m_param1;
    int m_param2;
    Cylinder m_cylinder;

    float m_radius;

    std::vector<GLfloat> generateVertexData(int param1, int param2) override;

private:

    std::vector<GLfloat> generateLatitudeAngleVector(int param1);
    glm::vec3 sphereToCartesian(float radius, float lat, float lon);
    void addPointAndNorm(std::vector<GLfloat> * data, glm::vec3 point);
    void addUVCoords(std::vector<GLfloat>* data, glm::vec3 point);
};

#endif // SPHERE_H
