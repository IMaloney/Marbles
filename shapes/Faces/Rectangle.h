#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "AtomicTriangle.h"
#include "Face.h"

class Rectangle
        : public Face
{
public:
    Rectangle(Point p1, Point p2, Point p3, Point p4);
    virtual ~Rectangle();
    Point getP1();
    Point getP2();
    Point getP3();
    Point getP4();
    float getLP1P2();
    float getLP2P3();
    float getLP1P4();
    float getLP3P4();
    float getAP1();
    float getAP2();
    float getAP3();
    float getAP4();
    Point getVP2P4();
    Point getVP1P3();
    std::vector<float> getPoints();
    void printPoints();

protected:
    Point m_p1;
    Point m_p2;
    Point m_p3;
    Point m_p4;
    std::unique_ptr<AtomicTriangle> m_t1;
    std::unique_ptr<AtomicTriangle> m_t2;
    std::vector<float> m_points;

    std::vector<float> p();
    void setP(std::vector<float> p);

    virtual void generatePoints();
};

#endif // RECTANGLE_H
