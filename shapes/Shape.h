#ifndef SHAPE_H
#define SHAPE_H

/** imports the OpenGL math library https://glm.g-truc.net/0.9.2/api/a00001.html */
#include <glm/glm.hpp>
#include "GL/glew.h"
#include <glm/gtx/transform.hpp>

#include "shapes/Faces/Point.h"

#include <math.h>
#include<memory>
#include <vector>

#include "gl/datatype/VBO.h"
#include "gl/datatype/VBOAttribMarker.h"

#include <iostream>

using namespace CS123::GL;
/**
 *
 * inserts a glm::vec3 into a vector of floats
 * this will come in handy if you want to take advantage of vectors to build your shape
 * make sure to call reserve beforehand to speed this up
 */
inline void insertVec3(std::vector<float> &data, glm::vec3 v){
    data.push_back(v.x);
    data.push_back(v.y);
    data.push_back(v.z);
}

namespace CS123 { namespace GL {
class VAO;
}}

namespace ShapeUtils {

std::vector<float> rotate(std::vector<float> points, glm::mat4 mat);
std::vector<float> translate(std::vector<float> points, glm::vec3 vec);
void combine(std::vector<float> *shape, std::vector<float> points);
float dot(Point p1, Point p2);
float length(Point p1);
float distance(Point p1, Point p2);
Point findVector(Point start, Point end);
float findAngle(Point p1, Point p2);
float rad(float val);
Point scale(Point p, glm::vec3 mat);

}
class Shape
{
public:
    Shape(int param1, int param2);
    virtual ~Shape();
    void draw();

    /** Initialize the VBO with the given vertex data. */
    void setVertexData(GLfloat *data, int size, VBO::GEOMETRY_LAYOUT drawMode, int numVertices);

    /** Enables the specified attribute and calls glVertexAttribPointer with the given arguments. */
    void setAttribute(GLuint index, GLuint numElementsPerVertex, int offset, VBOAttribMarker::DATA_TYPE type,
                      bool normalize);

    void buildVAO();
    // wrapper for computing vertices and building vao
    void createShape();

    int getMinParam1();

    int getMinParam2();

protected:
    virtual std::vector<float> buildShape() = 0;
    void checkMins();
//    computes vertices
    GLfloat *m_data;
    std::unique_ptr<CS123::GL::VAO> m_VAO;
//    may not need these
    std::vector<VBOAttribMarker> m_markers;
    int m_numVertices;
    int m_sParam1;
    int m_sParam2;
    int m_minParam1;
    int m_minParam2;
    GLsizeiptr m_size;
    VBO::GEOMETRY_LAYOUT m_drawMode;

};

#endif // SHAPE_H
