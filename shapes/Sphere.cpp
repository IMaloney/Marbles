#include "Sphere.h"

Sphere::Sphere()
{
}

Sphere::Sphere(float radius) :
    Shape(),
    m_param1(10),
    m_param2(10),
    m_cylinder(),
    m_radius(radius)
{
    m_vertexData = generateVertexData(m_param1, m_param2);
    /** build the VAO so that the shape is ready to be drawn */
    buildVAO();
}

Sphere::Sphere(int param1, int param2, float radius) :
    Shape(),
    m_param1(param1),
    m_param2(param2),
    m_cylinder(),
    m_radius(radius)
{
    m_vertexData = generateVertexData(param1, param2);
    /** build the VAO so that the shape is ready to be drawn */
    buildVAO();
}

Sphere::~Sphere()
{
}

std::vector<GLfloat> Sphere::generateVertexData(int param1, int param2) {
    std::vector<GLfloat> data = std::vector<GLfloat>();

    std::vector<GLfloat> anglesLat = generateLatitudeAngleVector(param1);
    std::vector<GLfloat> anglesLon = m_cylinder.generateAngleVector(param2);

    for (int i = 0; i < param1; i++) {
        for (int j = 0; j < param2; j++) {

            // Save the two longitude angles for this slice
            float angleLon1 = anglesLon[j];
            float angleLon2;

            // Check that they are
            if (j == param2 - 1) {
                angleLon2 = anglesLon[0];
            } else {
                angleLon2 = anglesLon[j+1];
            }


            if (i == 0) {
                glm::vec3 point1 = sphereToCartesian(m_radius, anglesLat[0], angleLon1);
                glm::vec3 point2 = sphereToCartesian(m_radius, anglesLat[1], angleLon1);
                glm::vec3 point3 = sphereToCartesian(m_radius, anglesLat[1], angleLon2);

                addPointAndNorm(&data, point3);
                addUVCoords(&data, point3);
                addPointAndNorm(&data, point2);
                addUVCoords(&data, point2);
                addPointAndNorm(&data, point1);
                addUVCoords(&data, point1);


            } else if (i == param1 - 1) {
                glm::vec3 point1 = sphereToCartesian(m_radius, anglesLat[param1 - 1], angleLon1);
                glm::vec3 point2 = sphereToCartesian(m_radius, anglesLat[param1], angleLon1);
                glm::vec3 point3 = sphereToCartesian(m_radius, anglesLat[param1 - 1], angleLon2);

                addPointAndNorm(&data, point3);
                addUVCoords(&data, point3);
                addPointAndNorm(&data, point2);
                addUVCoords(&data, point2);
                addPointAndNorm(&data, point1);
                addUVCoords(&data, point1);
            } else {
                glm::vec3 point1 = sphereToCartesian(m_radius, anglesLat[i], angleLon1);
                glm::vec3 point2 = sphereToCartesian(m_radius, anglesLat[i+1], angleLon1);
                glm::vec3 point3 = sphereToCartesian(m_radius, anglesLat[i], angleLon2);
                glm::vec3 point4 = sphereToCartesian(m_radius, anglesLat[i+1], angleLon2);

                addPointAndNorm(&data, point3);
                addUVCoords(&data, point3);
                addPointAndNorm(&data, point2);
                addUVCoords(&data, point2);
                addPointAndNorm(&data, point1);
                addUVCoords(&data, point1);

                addPointAndNorm(&data, point4);
                addUVCoords(&data, point4);
                addPointAndNorm(&data, point2);
                addUVCoords(&data, point2);
                addPointAndNorm(&data, point3);
                addUVCoords(&data, point3);
            }
        }
    }
    return data;
}

std::vector<GLfloat> Sphere::generateLatitudeAngleVector(int param1) {
    std::vector<GLfloat> angles = std::vector<GLfloat>();

    for (int i = 0; i <= param1; i++) {
        float angle = (M_PI/(float) param1) * (float)i;
        angles.push_back(angle);
    }
    return angles;
}

glm::vec3 Sphere::sphereToCartesian(float radius, float lat, float lon) {
    glm::vec3 coords = glm::vec3();

    coords.x = radius * sin(lat) * cos(lon);
    coords.y = radius * cos(lat);
    coords.z = radius * sin(lat) * sin(lon);

    return coords;
}

void Sphere::addPointAndNorm(std::vector<GLfloat>* data, glm::vec3 point) {
    data->push_back(point.x);
    data->push_back(point.y);
    data->push_back(point.z);
    // Normal is the same as the point!!!
//    data->push_back(point.x);
//    data->push_back(point.y);
//    data->push_back(point.z);
}

void Sphere::addUVCoords(std::vector<GLfloat>* data, glm::vec3 point) {
    float u;
    float v;

    float angle = atan2(point.z, point.x);

    if (angle >= 0) {
        u = 1.0f - (angle/(2*M_PI));
    } else {
        u = -angle / (2*M_PI);
    }

    float latitude = asin(point.y/m_radius);
    v = (latitude/M_PI) + 0.5f; // I THINK - per lecture notes its just +0.5 not +radius

    data->push_back(u);
    data->push_back(v);
}


