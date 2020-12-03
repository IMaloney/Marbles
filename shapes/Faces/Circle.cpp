#include "Circle.h"
#include "shapes/Shape.h"


Circle::Circle(Point p1, Point p2, Point p3, int param1, int param2) :
    m_p1(p1),
    m_p2(p2),
    m_p3(p3),
    m_radius(0.f),
    m_sParam1(param1),
    m_sParam2(param2),
    m_angle(0),
    m_t(nullptr)
{

    this->generatePoints();
}

Circle::~Circle()
{

}

void Circle::generatePoints()
{
    m_angle = 360.f / m_sParam2;
    m_radius = ShapeUtils::distance(m_p1, m_p2);
    m_t = std::make_unique<TessalatedTriangle>(m_p1, m_p2, m_p3, m_sParam1);
    ShapeUtils::combine(&m_points, m_t->getPoints());
    glm::mat4 mat;
    TessalatedTriangle t = *m_t;
    for (int i = 1; i < m_sParam2; i++){
        mat = glm::rotate(ShapeUtils::rad(m_angle), glm::vec3(0.f, 1.f, 0.f));
        t.Face::rotate(mat);
        ShapeUtils::combine(&m_points, t.getPoints());

    }
}


float Circle::getAngle()
{
    return m_angle;
}


std::vector<float> Circle::getPoints()
{
    return m_points;
}

TessalatedTriangle Circle::getT()
{
    return *m_t;
}

std::vector<float> Circle::p()
{
    return this->getPoints();
}

void Circle::setP(std::vector<float> p)
{
    m_points = p;
}

bool Circle::xPlane()
{
    return m_p2.getX() == m_p3.getX();
}

bool Circle::yPlane()
{
    return m_p2.getY() == m_p3.getY();
}

bool Circle::zPlane()
{
    return m_p2.getZ() == m_p3.getZ();
}

