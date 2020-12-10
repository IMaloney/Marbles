#ifndef SPHERE_H
#define SPHERE_H

#include "Shape.h"
#include "Cylinder.h"

#include <map>

class Sphere : public Shape
{
public:
    Sphere();
    Sphere(float radius);
    Sphere(int param1, int param2, float radius);
    ~Sphere();

    void isBroken();

    std::vector<GLfloat> getVetexData() { return m_vertexData; }

    // test method
    void printQuadInfo();

protected:
    int m_param1;
    int m_param2;
    Cylinder m_cylinder;

    float m_radius;

    std::vector<GLfloat> generateVertexData(int param1, int param2) override;

private:

    std::vector<GLfloat> generateLatitudeAngleVector(int param1);
    glm::vec3 sphereToCartesian(float radius, float lat, float lon);
    void addPointAndNorm(std::vector<GLfloat> * data, glm::vec3 point, int quad);
    void addUVCoords(std::vector<GLfloat>* data, glm::vec3 point);
//    std::map<glm::vec3, int> m_pointToQuadMap; --> can't use this map because the value will change
    // maps the quadrant to a vector of points that are stored in the quadrant
    std::map<int, std::vector<std::pair<int, int>>> m_quadToRangeMap;
    bool m_broken;

};

#endif // SPHERE_H
