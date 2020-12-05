#ifndef SHAPE_H
#define SHAPE_H

/** imports the OpenGL math library https://glm.g-truc.net/0.9.2/api/a00001.html */
#include <glm/glm.hpp>
#include "GL/glew.h"
#include <glm/gtx/transform.hpp>
#include "gl/datatype/VAO.h"
#include "gl/datatype/VBO.h"
#include <memory>
#include <vector>
#include <iostream>
#include "gl/datatype/VBOAttribMarker.h"
#include "gl/shaders/ShaderAttribLocations.h"

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

//namespace CS123 { namespace GL {
//class VAO;
//}}

class Shape
{
public:
    Shape();
    virtual ~Shape();
    void draw();
    void setDrawMode(CS123::GL::VBO::GEOMETRY_LAYOUT mode);

protected:
    /** builds the VAO, pretty much the same as from lab 1 */
    CS123::GL::VBO::GEOMETRY_LAYOUT m_drawMode;
    void buildVAO();

    virtual std::vector<GLfloat> generateVertexData(int param1, int param2) {}

    std::vector<GLfloat> m_vertexData;
    std::unique_ptr<CS123::GL::VAO> m_VAO;

};

#endif // SHAPE_H
