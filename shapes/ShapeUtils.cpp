#include "ShapeUtils.h"

void ShapeUtils::rotate(glm::mat4 mat, const GLfloat *face, const int &size, std::vector<GLfloat> &points)
{
    glm::vec3 point, rotatedPoint;
    // based on the fact that there are three points
    // TODO: update for when there are more points
    for (int i = 2; i < size; i+=3) {
        point = glm::vec3(face[i-2], face[i-1], face[i]);
        rotatedPoint = ((mat * glm::vec4(point, 1.0)).xyz());
        ShapeUtils::insertVec3(points, rotatedPoint);
    }
}

void ShapeUtils::addPoints(const GLfloat *face, const int &size , std::vector<GLfloat> &points) {
    for (int i = 2; i < size; i+= 3) {
        points.push_back(face[i-2]);
        points.push_back(face[i-1]);
        points.push_back(face[i]);
    }
}
