#ifndef CUBE_H
#define CUBE_H

#include "Shape.h"

#include <iostream>

class Cube : public Shape
{
public:
    Cube();
    Cube(int param1, int param2);
    ~Cube();

private:
    int m_param1;
    int m_param2;

    std::vector<GLfloat> generateVertexData(int param1, int param2) override;

    std::vector<GLfloat> buildZPlaneSide(std::vector<GLfloat> verts, std::vector<GLfloat> first, std::vector<GLfloat> normal,
                   std::vector<GLfloat> plane, int squaresPerRow, GLfloat squareSize);
    std::vector<GLfloat> buildYPlaneSide(std::vector<GLfloat> verts, std::vector<GLfloat> first, std::vector<GLfloat> normal,
                   std::vector<GLfloat> plane, int squaresPerRow, GLfloat squareSize);
    std::vector<GLfloat> buildXPlaneSide(std::vector<GLfloat> verts, std::vector<GLfloat> first, std::vector<GLfloat> normal,
                   std::vector<GLfloat> plane, int squaresPerRow, GLfloat squareSize);
};

#endif // CUBE_H
