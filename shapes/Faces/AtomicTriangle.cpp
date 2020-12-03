#include "AtomicTriangle.h"

AtomicTriangle::AtomicTriangle(Point p1, Point p2, Point p3)
        : Triangle(p1, p2, p3)

{
    this->generatePoints();
}

AtomicTriangle::~AtomicTriangle()
{

}


void AtomicTriangle::generatePoints()
{
    m_p1.addToVector(&m_points);
    m_p3.addToVector(&m_points);
    m_p2.addToVector(&m_points);
//    this->getNormalP1().addToVector(&m_points);
//    this->getNormalP3().addToVector(&m_points);
//    this->getNormalP2().addToVector(&m_points);
}


