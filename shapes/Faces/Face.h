#ifndef FACE_H
#define FACE_H

#include <glm/glm.hpp>
#include "shapes/Shape.h"

class Face
{
public:
    Face();
    virtual ~Face();
    void rotate(glm::mat4 mat);
    void translate(glm::vec3 v);
    void scale(glm::vec3 v);

protected:
    virtual std::vector<float> p() = 0;
    virtual void setP(std::vector<float> p) = 0;
    virtual void generatePoints() = 0;
};

#endif // FACE_H
