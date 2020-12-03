#include "Torus.h"

Torus::Torus()
{
}

Torus::Torus(int param1, int param2, float param3) :
    m_param1(param1),
    m_param2(param2),
    m_cylinder()
{
    m_vertexData = generateVertexData(param1, param2, param3);
    /** build the VAO so that the shape is ready to be drawn */
    buildVAO();
}

Torus::~Torus()
{
}

std::vector<GLfloat> Torus::generateVertexData(int param1, int param2, float param3) {
    std::vector<GLfloat> data = std::vector<GLfloat>();

    std::vector<GLfloat> anglesU = m_cylinder.generateAngleVector(param1);
    std::vector<GLfloat> anglesV = m_cylinder.generateAngleVector(param2);

    float a = param3 / 100.0;
    float c = 0.5;

    for (int i = 0; i < param1; i++) {
        for (int j = 0; j < param2; j++) {
            // Save the two U angles for this slice
            float angleU1 = anglesU[i];
            float angleU2;
            if (j == param1 - 1) {
                angleU2 = anglesU[0];
            } else {
                angleU2 = anglesU[i+1];
            }

            // Save the two V angles for this slice
            float angleV1 = anglesV[j];
            float angleV2;
            if (j == param2 - 1) {
                angleV2 = anglesV[0];
            } else {
                angleV2 = anglesV[j+1];
            }

            glm::vec3 point1 = torusToCartesian(a, c, angleU1, angleV1);
            glm::vec3 point2 = torusToCartesian(a, c, angleU1, angleV2);
            glm::vec3 point3 = torusToCartesian(a, c, angleU2, angleV1);
            glm::vec3 point4 = torusToCartesian(a, c, angleU2, angleV2);

            addPoint(&data, point3);
            calculateAndAddNormal(&data, angleU2, angleV1);
            addPoint(&data, point2);
            calculateAndAddNormal(&data, angleU1, angleV2);
            addPoint(&data, point1);
            calculateAndAddNormal(&data, angleU1, angleV1);

            addPoint(&data, point4);
            calculateAndAddNormal(&data, angleU2, angleV2);
            addPoint(&data, point2);
            calculateAndAddNormal(&data, angleU1, angleV2);
            addPoint(&data, point3);
            calculateAndAddNormal(&data, angleU2, angleV1);

        }
    }
    return data;
}

// U corresponds to param1, V corresponds to param2, a is donut radius, C is center of hole to center of donut
glm::vec3 Torus::torusToCartesian(float a, float c, float u, float v) {
    glm::vec3 coords = glm::vec3();

    coords.x = (c + a*cos(v))*cos(u);
    coords.y = (c + a*cos(v))*sin(u);
    coords.z = a*sin(v);

    return coords;
}

void Torus::addPoint(std::vector<GLfloat>* data, glm::vec3 point) {
    data->push_back(point.x);
    data->push_back(point.y);
    data->push_back(point.z);
}

void Torus::calculateAndAddNormal(std::vector<GLfloat>* data, float u, float v) {
    float tx = -1 * sin(u);
    float ty = cos(u);
    float tz = 0;

    float sx = cos(u) * (-1 * sin(v));
    float sy = sin(u) * (-1 * sin(v));
    float sz = cos(v);

    glm::vec3 norm = glm::vec3();

    norm.x =  ty*sz - tz*sy;
    norm.y =  tz*sx - tx*sz;
    norm.z =  tx*sy - ty*sx;

    norm = glm::normalize(norm);

    data->push_back(norm.x);
    data->push_back(norm.y);
    data->push_back(norm.z);
}
