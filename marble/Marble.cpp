#include "Marble.h"


Marble::Marble(float gravity, int radius, int weight) :
    m_gravity(gravity),
    m_radius(radius),
    m_weight(weight)
{

}


Marble::~Marble() {

}

// make sure it calls the proper updateMarble when this function is run
void Marble::updateGravity(const float &newGrav) {
    m_gravity = newGrav;
    this->updateMarble();
}

void Marble::updatePosition(glm::vec4 center) {

    glm::vec4 oldCenter = m_centerPosition; // May need this later for translation - depending on how it works
    m_centerPosition = center;

    m_boundingBoxTopLeftFront = glm::vec4(center.x - m_radius, center.y + m_radius, center.z + m_radius, 1.0f); // Double check this later
}

void Marble::updateCurrentDirection(glm::vec4 dir) {
    m_currDirection = dir;
}

void Marble::updateVelocity(float velocity) {
    m_velocity = velocity;
}

float Marble::getGravity() {
    return m_gravity;
}

glm::vec4 Marble::getPosition() {
    return m_centerPosition;
}

glm::vec4 Marble::getCurrentDirection() {
    return m_currDirection;
}

float Marble::getVelocity() {
    return m_velocity;
}

int Marble::getRadius() {
    return m_radius;
}
