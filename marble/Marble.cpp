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
