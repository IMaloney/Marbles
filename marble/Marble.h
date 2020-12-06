#ifndef MARBLE_H
#define MARBLE_H


#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include "GL/glew.h"
#include "shapes/Sphere.h"

class Marble
{
public:
    Marble(float gravity, int radius, int weight);
    virtual ~Marble();

    void updateGravity(const float &newGrav);
    void updatePosition(glm::vec4 center);
    void updateCurrentDirection(glm::vec4 dir);
    void updateVelocity(float velocity);

    int getRadius();

    float getGravity();
    glm::vec4 getPosition();
    glm::vec4 getCurrentDirection();
    float getVelocity();

    bool checkBoxCollision();

protected:
    std::unique_ptr<Sphere> m_sphere;
    float m_gravity;
    int m_radius;
    int m_weight;
    std::vector<GLfloat> m_points;

    float m_velocity;

    glm::vec4 m_centerPosition;
    glm::vec4 m_currDirection;

    glm::vec4 m_boundingBoxTopLeftFront;
    // may not need this method, but just in case changing the gravity changes other aspects of the marble
    // just have a protected method that all marble types will overwrite
//    virtual void updateMarble() = 0;

};





#endif // MARBLE_H
