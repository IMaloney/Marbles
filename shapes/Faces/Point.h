#ifndef POINT_H
#define POINT_H

#include <vector>
#include <iostream>

#include <glm/glm.hpp>


class Point
{
public:
    Point();
    Point(float x, float y, float z);
    Point(glm::vec3 v);
    Point(glm::vec4 v);
    virtual ~Point();
    void addToVector(std::vector<float> *vec);
    void vectorShift(std::vector<float> *vec, float x, float y, float z);
    glm::vec3 toVec3();
    glm::vec4 toVec4();
    void printValues();
    float getX();
    float getY();
    float getZ();
    void updateXYZ(float x, float y, float z);
    void updateXYZ(Point p);
    void incXYZ(float x, float y, float z);
    void incXYZ(Point p);
    void incY(float y);
    void incX(float x);
    void incZ(float z);
    void updateX(float x);
    void updateY(float y);
    void updateZ(float z);
    void scaleX(float v);
    void scaleY(float v);
    void scaleZ(float v);
    Point operator+(const Point &p);
    Point operator-(const Point &p);
    Point operator*(const float &n);
    Point operator*(const Point &p);


protected:
    float m_x;
    float m_y;
    float m_z;
};

#endif // POINT_H
