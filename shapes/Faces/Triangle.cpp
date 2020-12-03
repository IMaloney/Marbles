#include "Triangle.h"

Triangle::Triangle(Point p1, Point p2, Point p3) :
    m_p1(p1),
    m_p2(p2),
    m_p3(p3)
{

}

Triangle::~Triangle()
{

}

Point Triangle::getNormalP1() {
    glm::vec3 a  = ShapeUtils::findVector(m_p1, m_p2).toVec3(),
          b = ShapeUtils::findVector(m_p1, m_p3).toVec3();
    return Point(glm::cross(a, b));

}

Point Triangle::getNormalP2() {
    glm::vec3 a  = ShapeUtils::findVector(m_p2, m_p1).toVec3(),
          b = ShapeUtils::findVector(m_p2, m_p3).toVec3();
    return Point(glm::cross(a, b));
}

Point Triangle::getNormalP3 () {
    glm::vec3 a  = ShapeUtils::findVector(m_p3, m_p1).toVec3(),
          b = ShapeUtils::findVector(m_p3, m_p2).toVec3();
    return Point(glm::cross(a, b));
}

void Triangle::rotate(glm::mat4 mat)
{
    std::vector<float> ret;
    glm::vec3 point, rotatedPoint;
    int size = m_points.size();
    for (int i = 2; i < size; i+=3) {
        point = glm::vec3(m_points[i-2], m_points[i-1], m_points[i]);
        rotatedPoint = ((mat * glm::vec4(point, 1.0)).xyz());
        insertVec3(ret, rotatedPoint);
    }
    m_points = ret;
    this->updateAfterTransform(mat);
}

void Triangle::translate(glm::vec3 v)
{
    std::vector<float> ret;
    int size = m_points.size();
    glm::mat4 mat = glm::translate(v);
    glm::vec4 T;
    glm::vec3 temp;
    for (int i = 2; i < size; i += 3) {
        T = glm::vec4(m_points[i-2], m_points[i-1], m_points[i], 1.0f);
        temp = (mat * T).xyz();
        insertVec3(ret, temp);
    }
    m_points = ret;
    this->updateAfterTransform(mat);
}

void Triangle::scale(glm::vec3 v)
{
    std::vector<float> ret;
    int size = m_points.size();
    glm::mat4 mat = glm::scale(v);
    glm::vec4 T;
    glm::vec3 temp;
    for (int i = 2; i < size; i += 3) {
        T = glm::vec4(m_points[i-2], m_points[i-1], m_points[i], 1.0f);
        temp = (mat * T).xyz();
        insertVec3(ret, temp);
    }
    m_points = ret;
    this->updateAfterTransform(mat);
}

void Triangle::updateAfterTransform(glm::mat4 mat)
{
    m_p1 = Point(mat * m_p1.toVec4());
    m_p2 = Point(mat * m_p2.toVec4());
    m_p3 = Point(mat * m_p3.toVec4());

}

Point Triangle::getP1()
{
    return m_p1;
}
Point Triangle::getP2()
{
    return m_p2;
}

Point Triangle::getP3()
{
    return m_p3;
}

float Triangle::getLP1P2()
{
    return ShapeUtils::distance(m_p1, m_p2);
}

float Triangle::getLP1P3()
{
    return ShapeUtils::distance(m_p1, m_p3);
}

float Triangle::getLP2P3()
{
    return ShapeUtils::distance(m_p2, m_p3);
}

float Triangle::getAP1()
{
    return ShapeUtils::findAngle(m_p2 - m_p1, m_p3 - m_p1);
}

float Triangle::getAP2()
{
    return ShapeUtils::findAngle(m_p1 - m_p2, m_p3 - m_p2);
}

float Triangle::getAP3()
{
    return ShapeUtils::findAngle(m_p1 - m_p3, m_p2 - m_p3);
}


std::vector<float> Triangle::getPoints()
{
    return m_points;
}

Point Triangle::getVP1P2()
{
    return Point(m_p2.getX() - m_p1.getX(), m_p2.getY() - m_p1.getY(), m_p2.getZ() - m_p1.getZ());
}

Point Triangle::getVP1P3()
{
    return Point(m_p3.getX() - m_p1.getX(), m_p3.getY() - m_p1.getY(), m_p3.getZ() - m_p1.getZ());
}

//testing
void Triangle::printPoints()
{
    std::cout << "p1:" << std::endl;
    m_p1.printValues();
    std::cout << "p2:" << std::endl;
    m_p2.printValues();
    std::cout << "p3:" << std::endl;
    m_p3.printValues();
}
