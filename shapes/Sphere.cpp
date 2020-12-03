#include "Sphere.h"

#include <iostream>

Sphere::Sphere(int param1, int param2)
    : Shape(param1, param2)
{
    m_minParam1 = 2;
    m_minParam2 = 3;
    this->checkMins();
    this->createShape();
}

Sphere::~Sphere()
{

}

std::vector<float> Sphere::buildShape()
{
//    subtract 2 since the body contains rectangles and the halves contain the other triangle bits
    int numTriangles = m_sParam1 - 2;
    float xyAngle = 180.f/m_sParam1,
          xzAngle = 360.f/m_sParam2;
    std::vector<float> ret, temp;
//    AtomicTriangle t = this->buildHalves(&temp, xyAngle, xzAngle);
//    this->buildBody(&temp, numTriangles, xyAngle, xzAngle);
    this->buildBody(&ret, numTriangles, xyAngle, xzAngle);
//    this->buildSides(&ret, &temp, xzAngle);
    return ret;
}

void Sphere::buildSides(std::vector<float> *ret, std::vector<float> temp, float xzAngle) {
    glm::mat4 mat = glm::rotate(ShapeUtils::rad(xzAngle), glm::vec3(0.f,1.f,0.f));
    for (int i = 0; i < m_sParam2; i++) {
        temp = ShapeUtils::rotate(temp, mat);
        ShapeUtils::combine(ret, temp);
    }

}

//does not work
void Sphere::buildBody(std::vector<float> *ret, int numTriangles, float xyAngle, float xzAngle)
{
    float angle = 2 * xyAngle;
    Point p1 = Point(.5f * std::cos(ShapeUtils::rad(xzAngle)) * std::sin(ShapeUtils::rad(xyAngle)), .5f * std::cos(ShapeUtils::rad(xyAngle)), .5f * std::sin(ShapeUtils::rad(xzAngle)) * std::sin(ShapeUtils::rad(xyAngle))),
          p2 = Point(.5f * std::cos(ShapeUtils::rad(0.f)) * std::sin(ShapeUtils::rad(xyAngle)), .5f * std::cos(ShapeUtils::rad(xyAngle)), .5f * std::sin(ShapeUtils::rad(0.f)) * std::sin(ShapeUtils::rad(xyAngle))),
          p3, p4;
    std::unique_ptr<Rectangle> rect;
    int test = numTriangles;
    for (int i = numTriangles; i > 0; i --) {
        p3 = Point(.5f * std::cos(ShapeUtils::rad(0.f)) * std::sin(ShapeUtils::rad(angle)), .5f * std::cos(ShapeUtils::rad(angle)), .5f * std::sin(ShapeUtils::rad(0.f)) * std::sin(ShapeUtils::rad(angle)));
        p4 = Point(.5f * std::cos(ShapeUtils::rad(xzAngle)) * std::sin(ShapeUtils::rad(angle)), .5f * std::cos(ShapeUtils::rad(angle)), .5f * std::sin(ShapeUtils::rad(angle)) * std::sin(ShapeUtils::rad(angle)));
        rect = std::make_unique<Rectangle>(p1, p2, p3, p4);
        if (numTriangles == test) {
//            prints out points of first triangle crated at the top
            std::cout << "point 1: " << std::endl;
            p1.printValues();
            std::cout << "point 2: " << std::endl;
            p2.printValues();
            std::cout << "point 3: " << std::endl;
            p3.printValues();
            std::cout << "point 4: " << std::endl;
            p4.printValues();
        }
        angle += xyAngle;
        p1 = p4;
        p2 = p3;
        ShapeUtils::combine(ret, rect->getPoints());
    }
}

AtomicTriangle Sphere::buildHalves(std::vector<float> *ret, float xyAngle, float xzAngle)
{
    // top half
    Point p1, p2, p3;
    p1 = Point(0.f, .5f, 0.f);
    p2 = Point(.5f * std::cos(ShapeUtils::rad(0.f)) * std::sin(ShapeUtils::rad(xyAngle)), .5f * std::cos(ShapeUtils::rad(xyAngle)), .5f * std::sin(ShapeUtils::rad(0.f)) * std::sin(ShapeUtils::rad(xyAngle)));
    p3 = Point(.5f * std::cos(ShapeUtils::rad(xzAngle)) * std::sin(ShapeUtils::rad(xyAngle)), .5f * std::cos(ShapeUtils::rad(xyAngle)), .5f * std::sin(ShapeUtils::rad(xzAngle)) * std::sin(ShapeUtils::rad(xyAngle)));
    AtomicTriangle t = AtomicTriangle(p1, p2 , p3);
    ShapeUtils::combine(ret, t.getPoints());
    std::cout << "top triangle p3 (problem point):" << std::endl;
    // bottom half
    p1 = Point(0.f, -.5f, 0.f);
    p2 = Point(.5f * std::cos(ShapeUtils::rad(0.f)) * std::sin(ShapeUtils::rad(xyAngle)), -.5f * std::cos(ShapeUtils::rad(xyAngle)), .5f * std::sin(ShapeUtils::rad(0.f)) * std::sin(ShapeUtils::rad(xyAngle)));
    p3 = Point(.5f * std::cos(ShapeUtils::rad(xzAngle)) * std::sin(ShapeUtils::rad(xyAngle)), -.5f * std::cos(ShapeUtils::rad(xyAngle)), .5f * std::sin(ShapeUtils::rad(xzAngle)) * std::sin(ShapeUtils::rad(xyAngle)));
    AtomicTriangle bt = AtomicTriangle(p1, p3, p2);
    ShapeUtils::combine(ret, bt.getPoints());

    return t;
}
