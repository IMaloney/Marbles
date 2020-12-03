#include "Point.h"



Point::Point(float x, float y, float z) :
    m_x(x),
    m_y(y),
    m_z(z)
{

}

Point::Point(glm::vec3 v)
{
    Point(v.x, v.y, v.z);
}

Point::Point(glm::vec4 v){
    Point(v.x, v.y, v.z);
}

Point::Point() {
    Point(0.f,0.f,0.f);
}

Point::~Point()
{

}

void Point::printValues()
{
    std::cout << "x: " << m_x << " y: " << m_y << " z: " << m_z << std::endl;
}

glm::vec3 Point::toVec3()
{
    return glm::vec3(m_x, m_y, m_z);
}

glm::vec4 Point::toVec4()
{
    return glm::vec4(m_x, m_y, m_z, 1.0f);
}

float Point::getX()
{
    return m_x;
}

float Point::getY()
{
    return m_y;
}

float Point::getZ()
{
 return m_z;
}

void Point::addToVector(std::vector<float> *vec)
{
    (*vec).push_back(m_x);
    (*vec).push_back(m_y);
    (*vec).push_back(m_z);
}

void Point::vectorShift(std::vector<float> *vec, float x, float y, float z)
{
    (*vec).push_back(m_x + x);
    (*vec).push_back(m_y + y);
    (*vec).push_back(m_z + z);
}

void Point::updateXYZ(float x, float y, float z)
{
    m_x = x;
    m_y = y;
    m_z = z;
}

void Point::updateXYZ(Point  p)
{
    this->updateXYZ(p.getX(), p.getY(), p.getZ());

}


void Point::incXYZ(float x, float y, float z)
{
    m_x += x;
    m_y += y;
    m_z += z;
}

void Point::incXYZ(Point p)
{
    this->incXYZ(p.getX(), p.getY(), p.getZ());
}


void Point::incX(float x)
{
    m_x += x;
}


void Point::incY(float y)
{
    m_y += y;
}

void Point::incZ(float z)
{
    m_z += z;
}

void Point::updateX(float x)
{
    m_x = x;
}
void Point::updateZ(float z)
{
    m_z = z;
}

void Point::updateY(float y)
{
    m_y = y;
}

void Point::scaleX(float v)
{
    m_x *= v;
}

void Point::scaleY(float v)
{
    m_y *= v;
}

void Point::scaleZ(float v)
{
    m_z *= v;
}


Point Point::operator+(const Point &p)
{
    return Point(m_x + p.m_x, m_y + p.m_y, m_z + p.m_z);
}

Point Point::operator-(const Point &p)
{
    return Point(m_x - p.m_x, m_y - p.m_y, m_z - p.m_z);
}

Point Point::operator*(const float &n)
{
    return Point(m_x * n, m_y * n, m_z * n);
}

Point Point::operator*(const Point &p)
{
    return Point(m_x * p.m_x, m_y * p.m_y, m_z * p.m_z);
}

