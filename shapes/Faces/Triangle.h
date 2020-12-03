#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <glm/glm.hpp>
#include "GL/glew.h"
#include <glm/gtx/transform.hpp>

#include "shapes/Shape.h"

class Triangle
{
public:
    Triangle(Point p1, Point p2, Point p3);
    virtual ~Triangle();
    void rotate(glm::mat4 mat);
    void translate(glm::vec3 v);
    void scale(glm::vec3 v);
    Point getP1();
    Point getP2();
    Point getP3();
    float getLP1P2();
    float getLP1P3();
    float getLP2P3();
    float getAP1();
    float getAP2();
    float getAP3();
    Point getVP1P2();
    Point getVP1P3();
    Point getNormalP1();
    Point getNormalP2();
    Point getNormalP3();
    std::vector<float> getPoints();
    void printPoints();

protected:
    virtual void generatePoints() = 0;
    void updateAfterTransform(glm::mat4 mat);
    Point m_p1;
    Point m_p2;
    Point m_p3;
    std::vector<float> m_points;

};

#endif // TRIANGLE_H
