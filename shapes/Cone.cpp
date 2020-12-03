#include "Cone.h"

Cone::Cone(int param1, int param2)
    : Shape (param1, param2)
{
    m_base = nullptr;
    m_side = nullptr;
    m_minParam1 = 1;
    m_minParam2 = 3;
    this->checkMins();
    this->createShape();
}

Cone::~Cone()
{

}

std::vector<float> Cone::buildShape()
{
    std::vector<float> ret;
    float angle = 360.f / m_sParam2;
    this->buildBase(&ret, angle);
    this->buildFaces(&ret, angle);
    return ret;
}

void Cone::buildBase(std::vector<float> *ret, float angle)
{
    Point p1, p2, p3;
    p1 = Point(0.f, -0.5f, 0.f);
    p2 = Point(.5f * std::cos(ShapeUtils::rad(angle)), -0.5f, .5f * std::sin(ShapeUtils::rad(angle)));
    p3 = Point(.5f * std::cos(ShapeUtils::rad(0.f)), -0.5f, .5f * std::sin(ShapeUtils::rad(0.f)));
    m_base = std::make_unique<Circle>(p1, p2, p3, m_sParam1, m_sParam2);
    ShapeUtils::combine(ret, m_base->getPoints());
}

void Cone::buildFaces(std::vector<float> *ret, float angle)
{
    TessalatedTriangle t = m_base->getT();
    Point p1 = Point(0.f, .5f, 0.f);
    m_side = std::make_unique<TessalatedTriangle>(p1, t.getP3(), t.getP2(), m_sParam1);
    ShapeUtils::combine(ret, m_side->getPoints());
    glm::mat4 mat = glm::rotate(ShapeUtils::rad(angle), glm::vec3(0.f,1.f, 0.f));
    for (int i = 1; i < m_sParam2; i++) {
        m_side->Face::rotate(mat);
        ShapeUtils::combine(ret, m_side->getPoints());
    }
}

