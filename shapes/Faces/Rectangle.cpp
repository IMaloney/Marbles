#include "Rectangle.h"

Rectangle::Rectangle(Point p1, Point p2, Point p3, Point p4) :
    m_p1(p1),
    m_p2(p2),
    m_p3(p3),
    m_p4(p4),
    m_t1(nullptr),
    m_t2(nullptr)
{
    this->generatePoints();
}


void Rectangle::generatePoints()
{
    m_t1 = std::make_unique<AtomicTriangle>(m_p1, m_p3, m_p4);
    m_t2 = std::make_unique<AtomicTriangle>(m_p2, m_p3, m_p1);
    ShapeUtils::combine(&m_points, m_t1->getPoints());
    ShapeUtils::combine(&m_points, m_t2->getPoints());
}

Rectangle::~Rectangle()
{

}

Point Rectangle::getP1()
{
    return m_p1;
}

Point Rectangle::getP2()
{
    return m_p2;
}

Point Rectangle::getP3()
{
    return m_p3;
}

Point Rectangle::getP4()
{
    return m_p4;
}

float Rectangle::getLP2P3()
{
    return m_t2->getLP1P2();
}

float Rectangle::getLP1P4()
{
    return m_t1->getLP1P3();
}

float Rectangle::getLP3P4()
{
    return m_t1->getLP2P3();
}

float Rectangle::getLP1P2()
{
    return m_t2->getLP1P3();
}

float Rectangle::getAP1()
{
    return m_t1->getAP1() + m_t2->getAP3();
}

float Rectangle::getAP2()
{
    return m_t2->getAP1();
}

float Rectangle::getAP3()
{
    return m_t1->getAP2() + m_t2->getAP2();
}

float Rectangle::getAP4()
{
    return m_t1->getAP3();
}

Point Rectangle::getVP2P4()
{
    return Point(m_p4.getX() - m_p2.getX(), m_p4.getY() - m_p2.getY(), m_p4.getZ() - m_p2.getZ());
}

Point Rectangle::getVP1P3()
{
    return Point(m_p3.getX() - m_p1.getX(), m_p3.getY() - m_p1.getY(), m_p3.getZ() - m_p1.getZ());
}


std::vector<float> Rectangle::getPoints()
{
    return m_points;
}

std::vector<float> Rectangle::p()
{
    return this->getPoints();
}

void Rectangle::setP(std::vector<float> p)
{
    m_points = p;
}

void Rectangle::printPoints()
{
    std::cout << "p1:" << std::endl;
    m_p1.printValues();
    std::cout << "p2:" << std::endl;
    m_p2.printValues();
    std::cout << "p3:" << std::endl;
    m_p3.printValues();
    std::cout << "p4:" << std::endl;
    m_p4.printValues();
}

