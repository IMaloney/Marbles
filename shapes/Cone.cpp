#include "Cone.h"

Cone::Cone()
{
}

Cone::Cone(int param1, int param2) :
    Shape(),
    m_param1(param1),
    m_param2(param2),
    m_cylinder()
{
    m_vertexData = generateVertexData(param1, param2);
    /** build the VAO so that the shape is ready to be drawn */
    buildVAO();
}

Cone::~Cone()
{
}

std::vector<GLfloat> Cone::generateVertexData(int param1, int param2) {
    std::vector<GLfloat> data = std::vector<GLfloat>();

    std::vector<GLfloat> angles = m_cylinder.generateAngleVector(param2);
    float stackHeight = 1.0 / (float) param1;

    // For each stack
    for (int i = 0; i < param1; i++) {
        // For each slice
        for (int j = 0; j < param2; j++) {
            float y1 = 0.5 - stackHeight * (float) i;
            float y2 = 0.5 - stackHeight * (float) (i + 1.0);

            float angle1 = angles[j];
            float angle2;
            if (j == param2 - 1) {
                angle2 = angles[0];
            } else {
                angle2 = angles[j+1];
            }

            float radiusIncrements = 0.5 / (float) param1;

            std::vector<GLfloat> bottomNormal = {0, -1, 0};

            float radius1 = i * radiusIncrements;
            float radius2 = (i + 1) * radiusIncrements;
            if (i == 0) {
                std::vector<GLfloat> xzNorm1 = m_cylinder.generatePositionVector(angle1, y1, radius1);
                std::vector<GLfloat> xzNorm2 = m_cylinder.generatePositionVector(angle1, y2, radius2);
                std::vector<GLfloat> xzNorm3 = m_cylinder.generatePositionVector(angle2, y2, radius2);

                data.insert(data.end(), xzNorm3.begin(), xzNorm3.begin()+3);
                glm::vec3 normal = calculateSurfaceNormal(angle2);
                glm::normalize(normal);
                data.push_back(normal.x);
                data.push_back(normal.y);
                data.push_back(normal.z);

//                // TEXTURE HERE
//                float u;
//                float v = 0.5f - xzNorm3[1];

//                float angle = atan2(xzNorm3[2], xzNorm3[0]);

//                if (angle >= 0) {
//                    u = 1.0f - (angle/(2*M_PI));
//                } else {
//                    u = -angle / (2*M_PI);
//                }
//                data.push_back(u);
//                data.push_back(v);

                data.insert(data.end(), xzNorm2.begin(), xzNorm2.begin()+3);
                normal = calculateSurfaceNormal(angle1);
                glm::normalize(normal);
                data.push_back(normal.x);
                data.push_back(normal.y);
                data.push_back(normal.z);

//                // TEXTURE HERE
//                v = 0.5f - xzNorm2[1];

//                angle = atan2(xzNorm2[2], xzNorm2[0]);

//                if (angle >= 0) {
//                    u = 1.0f - (angle/(2*M_PI));
//                } else {
//                    u = -angle / (2*M_PI);
//                }
//                data.push_back(u);
//                data.push_back(v);

                data.insert(data.end(), xzNorm1.begin(), xzNorm1.begin()+3);
                normal = calculateSurfaceNormal(angle1);
                glm::normalize(normal);
                data.push_back(normal.x);
                data.push_back(normal.y);
                data.push_back(normal.z);

//                // TEXTURE HERE
//                v = 0.5f - xzNorm1[1];

//                angle = atan2(xzNorm1[2], xzNorm1[0]);

//                if (angle >= 0) {
//                    u = 1.0f - (angle/(2*M_PI));
//                } else {
//                    u = -angle / (2*M_PI);
//                }
//                data.push_back(u);
//                data.push_back(v);

            } else {
                std::vector<GLfloat> xzNorm1 = m_cylinder.generatePositionVector(angle1, y1, radius1);
                std::vector<GLfloat> xzNorm2 = m_cylinder.generatePositionVector(angle1, y2, radius2);
                std::vector<GLfloat> xzNorm3 = m_cylinder.generatePositionVector(angle2, y1, radius1);
                std::vector<GLfloat> xzNorm4 = m_cylinder.generatePositionVector(angle2, y2, radius2);

                // Side slices:
                data.insert(data.end(), xzNorm3.begin(), xzNorm3.begin()+3);
                glm::vec3 normal = calculateSurfaceNormal(angle2);
                glm::normalize(normal);
                data.push_back(normal.x);
                data.push_back(normal.y);
                data.push_back(normal.z);

//                // TEXTURE HERE
//                float u;
//                float v = 0.5f - xzNorm3[1];

//                float angle = atan2(xzNorm3[2], xzNorm3[0]);

//                if (angle >= 0) {
//                    u = 1.0f - (angle/(2*M_PI));
//                } else {
//                    u = -angle / (2*M_PI);
//                }
//                data.push_back(u);
//                data.push_back(v);

                data.insert(data.end(), xzNorm2.begin(), xzNorm2.begin()+3);
                normal = calculateSurfaceNormal(angle1);
                glm::normalize(normal);
                data.push_back(normal.x);
                data.push_back(normal.y);
                data.push_back(normal.z);

//                // TEXTURE HERE
//                v = 0.5f - xzNorm2[1];

//                angle = atan2(xzNorm2[2], xzNorm2[0]);

//                if (angle >= 0) {
//                    u = 1.0f - (angle/(2*M_PI));
//                } else {
//                    u = -angle / (2*M_PI);
//                }
//                data.push_back(u);
//                data.push_back(v);

                data.insert(data.end(), xzNorm1.begin(), xzNorm1.begin()+3);
                normal = calculateSurfaceNormal(angle1);
                glm::normalize(normal);
                data.push_back(normal.x);
                data.push_back(normal.y);
                data.push_back(normal.z);

//                // TEXTURE HERE
//                v = 0.5f - xzNorm1[1];

//                angle = atan2(xzNorm1[2], xzNorm1[0]);

//                if (angle >= 0) {
//                    u = 1.0f - (angle/(2*M_PI));
//                } else {
//                    u = -angle / (2*M_PI);
//                }
//                data.push_back(u);
//                data.push_back(v);

                data.insert(data.end(), xzNorm4.begin(), xzNorm4.begin()+3);
                normal = calculateSurfaceNormal(angle2);
                glm::normalize(normal);
                data.push_back(normal.x);
                data.push_back(normal.y);
                data.push_back(normal.z);

//                // TEXTURE HERE
//                v = 0.5f - xzNorm4[1];

//                angle = atan2(xzNorm4[2], xzNorm4[0]);

//                if (angle >= 0) {
//                    u = 1.0f - (angle/(2*M_PI));
//                } else {
//                    u = -angle / (2*M_PI);
//                }
//                data.push_back(u);
//                data.push_back(v);

                data.insert(data.end(), xzNorm2.begin(), xzNorm2.begin()+3);
                normal = calculateSurfaceNormal(angle1);
                glm::normalize(normal);
                data.push_back(normal.x);
                data.push_back(normal.y);
                data.push_back(normal.z);

//                // TEXTURE HERE
//                v = 0.5f - xzNorm2[1];

//                angle = atan2(xzNorm2[2], xzNorm2[0]);

//                if (angle >= 0) {
//                    u = 1.0f - (angle/(2*M_PI));
//                } else {
//                    u = -angle / (2*M_PI);
//                }
//                data.push_back(u);
//                data.push_back(v);

                data.insert(data.end(), xzNorm3.begin(), xzNorm3.begin()+3);
                normal = calculateSurfaceNormal(angle2);
                glm::normalize(normal);
                data.push_back(normal.x);
                data.push_back(normal.y);
                data.push_back(normal.z);

//                // TEXTURE HERE
//                v = 0.5f - xzNorm3[1];

//                angle = atan2(xzNorm3[2], xzNorm3[0]);

//                if (angle >= 0) {
//                    u = 1.0f - (angle/(2*M_PI));
//                } else {
//                    u = -angle / (2*M_PI);
//                }
//                data.push_back(u);
//                data.push_back(v);
            }

            if (i == 0) {
                float faceRadius = (i + 1) * radiusIncrements;
                // Bottom
                std::vector<GLfloat> xzNormBot1 = m_cylinder.generatePositionVector(angle1, -0.5, faceRadius);
                std::vector<GLfloat> xzNormBot2 = m_cylinder.generatePositionVector(angle2, -0.5, faceRadius);

                data.push_back(0);
                data.push_back(-0.5);
                data.push_back(0);
                data.insert(data.end(), bottomNormal.begin(), bottomNormal.end());

//                // TEXTURE HERE
//                data.push_back(0);
//                data.push_back(.5);

                data.insert(data.end(), xzNormBot1.begin(), xzNormBot1.begin()+3);
                data.insert(data.end(), bottomNormal.begin(), bottomNormal.end());

//                // TEXTURE HERE
//                data.push_back(xzNormBot1[0] + 0.5f);
//                data.push_back(xzNormBot1[2] + 0.5f);

                data.insert(data.end(), xzNormBot2.begin(), xzNormBot2.begin()+3);
                data.insert(data.end(), bottomNormal.begin(), bottomNormal.end());

//                // TEXTURE HERE
//                data.push_back(xzNormBot2[0] + 0.5f);
//                data.push_back(xzNormBot2[2] + 0.5f);
            } else {
                float faceRadius1 = i * radiusIncrements;
                float faceRadius2 = (i + 1) * radiusIncrements;

                std::vector<GLfloat> xzNormBot1 = m_cylinder.generatePositionVector(angle1, -0.5, faceRadius1);
                std::vector<GLfloat> xzNormBot2 = m_cylinder.generatePositionVector(angle1, -0.5, faceRadius2);
                std::vector<GLfloat> xzNormBot3 = m_cylinder.generatePositionVector(angle2, -0.5, faceRadius1);
                std::vector<GLfloat> xzNormBot4 = m_cylinder.generatePositionVector(angle2, -0.5, faceRadius2);

                data.insert(data.end(), xzNormBot1.begin(), xzNormBot1.begin()+3);
                data.insert(data.end(), bottomNormal.begin(), bottomNormal.end());

//                // TEXTURE HERE
//                data.push_back(xzNormBot1[0] + 0.5f);
//                data.push_back(xzNormBot1[2] + 0.5f);

                data.insert(data.end(), xzNormBot2.begin(), xzNormBot2.begin()+3);
                data.insert(data.end(), bottomNormal.begin(), bottomNormal.end());

//                // TEXTURE HERE
//                data.push_back(xzNormBot2[0] + 0.5f);
//                data.push_back(xzNormBot2[2] + 0.5f);

                data.insert(data.end(), xzNormBot3.begin(), xzNormBot3.begin()+3);
                data.insert(data.end(), bottomNormal.begin(), bottomNormal.end());

//                // TEXTURE HERE
//                data.push_back(xzNormBot3[0] + 0.5f);
//                data.push_back(xzNormBot3[2] + 0.5f);

                data.insert(data.end(), xzNormBot3.begin(), xzNormBot3.begin()+3);
                data.insert(data.end(), bottomNormal.begin(), bottomNormal.end());

//                // TEXTURE HERE
//                data.push_back(xzNormBot3[0] + 0.5f);
//                data.push_back(xzNormBot3[2] + 0.5f);

                data.insert(data.end(), xzNormBot2.begin(), xzNormBot2.begin()+3);
                data.insert(data.end(), bottomNormal.begin(), bottomNormal.end());

//                // TEXTURE HERE
//                data.push_back(xzNormBot2[0] + 0.5f);
//                data.push_back(xzNormBot2[2] + 0.5f);

                data.insert(data.end(), xzNormBot4.begin(), xzNormBot4.begin()+3);
                data.insert(data.end(), bottomNormal.begin(), bottomNormal.end());

//                // TEXTURE HERE
//                data.push_back(xzNormBot4[0] + 0.5f);
//                data.push_back(xzNormBot4[2] + 0.5f);
            }
        }
    }
    return data;
}

glm::vec3 Cone::calculateSurfaceNormal(float angle) {
    glm::vec3 normal = glm::vec3();

    normal[0] = cos(angle) * (2/sqrt(5));
    normal[1] = 1 / sqrt(5);
    normal[2] = sin(angle) * (2/sqrt(5));

    return normal;
}
