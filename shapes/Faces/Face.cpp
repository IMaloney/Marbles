#include "Face.h"

Face::Face()
{

}

Face::~Face()
{

}
void Face::rotate(glm::mat4 mat)
{
    std::vector<float> ret;
    glm::vec3 point, rotatedPoint;
    std::vector<float> p = this->p();
    int size = p.size();
    for (int i = 2; i < size; i+=3) {
        point = glm::vec3(p[i-2], p[i-1], p[i]);
        rotatedPoint = ((mat * glm::vec4(point, 1.0)).xyz());
        insertVec3(ret, rotatedPoint);
    }
    this->setP(ret);

}

void Face::translate(glm::vec3 v)
{
    std::vector<float> ret;
    std::vector<float> p = this->p();
    int size = p.size();
    glm::mat4 mat = glm::translate(v);
    glm::vec4 T;
    glm::vec3 temp;
    for (int i = 2; i < size; i += 3) {
        T = glm::vec4(p[i-2], p[i-1], p[i], 1.0f);
        temp = (mat * T).xyz();
        insertVec3(ret, temp);
    }
    this->setP(ret);
}

void Face::scale(glm::vec3 v)
{
    std::vector<float> ret;
    std::vector<float> p = this->p();
    int size = p.size();
    glm::mat4 mat = glm::scale(v);
    glm::vec4 T;
    glm::vec3 temp;
    for (int i = 2; i < size; i += 3) {
        T = glm::vec4(p[i-2], p[i-1], p[i], 1.0f);
        temp = (mat * T).xyz();
        insertVec3(ret, temp);
    }
    this->setP(ret);
}

