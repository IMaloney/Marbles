#ifndef MARBLE_H
#define MARBLE_H


#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include "GL/glew.h"

class Marble
{
public:
    Marble(float gravity, int radius, int weight);
    virtual ~Marble();

    void updateGravity(const float &newGrav);

protected:
    float m_gravity;
    int m_radius;
    int m_weight;
    std::vector<GLfloat> m_points;
    // may not need this method, but just in case changing the gravity changes other aspects of the marble
    // just have a protected method that all marble types will overwrite
    virtual void updateMarble() = 0;

};





#endif // MARBLE_H
