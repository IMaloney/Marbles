#ifndef BOX_H
#define BOX_H

#include "Shape.h"
#include "ShapeUtils.h"
#include <vector>

#include <iostream>

class Box : public Shape
{
public:
    Box(float size=1.f);
    virtual ~Box();


// using m_vertexData from shape to store points
// methods to add: wall shading etc...
private:
    float m_size;
    // buildFace method removed (just a hardcoded face)
    void buildBox();

};

#endif // BOX_H
