#include "Cylinder.h"

Cylinder::Cylinder(int param1, int param2)
    :Shape(param1, param2)
{
    m_top = nullptr;
    m_minParam1 = 1;
    m_minParam2 = 3;
    this->checkMins();
    this->createShape();
}

Cylinder::~Cylinder()
{

}


std::vector<float> Cylinder::buildShape(){
    std::vector<float> ret;
    float angle = 360.f/m_sParam2;
    this->buildCaps(&ret, angle);
    this->buildSides(&ret, angle);
    return ret;
}

void Cylinder::buildSides(std::vector<float> *ret, float angle)
{
    std::vector<float> side;
    TessalatedTriangle topT= m_top->getT();
    std::unique_ptr<Rectangle> rect;
    float size = -1.f/m_sParam1;
    Point p1 = topT.getP3(), p2 = topT.getP2(),
          p3 = topT.getP2(), p4 = topT.getP3();
    p3.incY(size);
    p4.incY(size);
    for (int i = 0; i < m_sParam1; i++){
        rect = std::make_unique<Rectangle>(p1, p2, p3, p4);
        ShapeUtils::combine(&side, rect->getPoints());
        p1.incY(size);
        p2.incY(size);
        p3.incY(size);
        p4.incY(size);
    }
    ShapeUtils::combine(ret, side);
    glm::mat4 mat = glm::rotate(ShapeUtils::rad(angle), glm::vec3(0.f,1.f, 0.f));
    for (int i = 1; i < m_sParam2; i++) {
        side = ShapeUtils::rotate(side, mat);
        ShapeUtils::combine(ret, side);
    }
}

void Cylinder::buildCaps(std::vector<float> *ret, float angle)
{
    Point p1, p2, p3;
    p1 = Point(0.f, -0.5f, 0.f);
    p2 = Point(.5f * std::cos(ShapeUtils::rad(angle)), -0.5f, .5f * std::sin(ShapeUtils::rad(angle)));
    p3 = Point(.5f * std::cos(ShapeUtils::rad(0.f)), -0.5f, .5f * std::sin(ShapeUtils::rad(0.f)));
    std::unique_ptr<Circle> bottom = std::make_unique<Circle>(p1, p2, p3, m_sParam1, m_sParam2);
    ShapeUtils::combine(ret, bottom->getPoints());

    p1 = Point(0.f, 0.5f, 0.f);
    p2 = Point(.5f * std::cos(ShapeUtils::rad(angle)), 0.5f, .5f * std::sin(ShapeUtils::rad(angle)));
    p3 = Point(.5f * std::cos(ShapeUtils::rad(0.f)), 0.5f, .5f * std::sin(ShapeUtils::rad(0.f)));
    m_top = std::make_unique<Circle>(p1, p3, p2, m_sParam1, m_sParam2);
    ShapeUtils::combine(ret, m_top->getPoints());
}
