#ifndef CIRCLE_H
#define CIRCLE_H

#include <vector>
#include <glm/glm.hpp>
#include "GL/glew.h"
#include <glm/gtx/transform.hpp>
#include "shapes/Shape.h"

#include "TessalatedTriangle.h"


class Circle
        : public Face
{
public:
    Circle(Point p1, Point p2, Point p3, int param1, int param2);
    virtual ~Circle();
    float getAngle();
    std::vector<float> getPoints();
    float getDist();
    TessalatedTriangle getT();


protected:
    void generatePoints();
    bool xPlane();
    bool yPlane();
    bool zPlane();
    std::vector<float> p();
    void setP(std::vector<float> p);
    Point m_p1;
    Point m_p2;
    Point m_p3;
    float m_radius;
    int m_sParam1;
    int m_sParam2;
    float m_angle;
    std::unique_ptr<TessalatedTriangle> m_t;
    std::vector<float> m_points;

};

#endif // CIRCLE_H
