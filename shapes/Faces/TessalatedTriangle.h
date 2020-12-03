#ifndef TESSALATEDTRIANGLE_H
#define TESSALATEDTRIANGLE_H

#include "Rectangle.h"

class TessalatedTriangle
      : public Triangle, public Face
{
public:
    TessalatedTriangle(Point p1, Point p2, Point p3, int sParam1);
    virtual ~TessalatedTriangle();


protected:
    float m_sParam1;

    void generatePoints();
    std::vector<float> p();
    void setP(std::vector<float> p);

};

#endif // TESSALATEDTRIANGLE_H
