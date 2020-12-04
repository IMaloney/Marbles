#ifndef SHAPEUTILS_H
#define SHAPEUTILS_H

#include <glm/glm.hpp>
#include "GL/glew.h"
#include <glm/gtx/transform.hpp>
#include <vector>

namespace ShapeUtils{
    void rotate(glm::mat4 mat, const GLfloat *face, const int &size, std::vector<GLfloat> &points);
    void addPoints(const GLfloat *face, const int &size , std::vector<GLfloat> &points);
    inline void insertVec3(std::vector<float> &data, glm::vec3 v){
        data.push_back(v.x);
        data.push_back(v.y);
        data.push_back(v.z);
    }
}

#endif // SHAPEUTILS_H
