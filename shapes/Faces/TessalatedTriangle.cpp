#include "TessalatedTriangle.h"

TessalatedTriangle::TessalatedTriangle(Point p1, Point p2, Point p3, int sParam1)
    : Triangle(p1, p2, p3)
{
    m_sParam1 = sParam1;
    this->generatePoints();
}

TessalatedTriangle::~TessalatedTriangle()
{

}

void TessalatedTriangle::generatePoints()
{
    float height = 1.f/m_sParam1;
    int triangles  = m_sParam1 - 1;
    Point p1, p2, p3, p4, temp1, temp2, vl, vr;
    vl = ShapeUtils::findVector(m_p1, m_p3) * height;
    vr = ShapeUtils::findVector(m_p1, m_p2) * height;
    AtomicTriangle t = AtomicTriangle(m_p1, m_p1 + vr, m_p1 + vl);
    ShapeUtils::combine(&m_points, t.getPoints());
    p1 = t.getP3();
    p2 = t.getP2();
    p3 = p2 + vr;
    p4 = p1 + vl;
    std::unique_ptr<Rectangle> rect;
    while (triangles > 0) {
        rect = std::make_unique<Rectangle>(p1, p2, p3, p4);
        ShapeUtils::combine(&m_points, rect->getPoints());
        temp1 = p4;
        temp2 = p3;
        p4.incXYZ(vl);
        p3.incXYZ(vr);
        p1 = temp1;
        p2 = temp2;
        triangles -= 1;
    }
}

std::vector<float> TessalatedTriangle::p()
{
    return this->getPoints();
}

void TessalatedTriangle::setP(std::vector<float> p)
{
    m_points = p;
}

