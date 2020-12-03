#include "Cylinder.h"
#include "shapes/ExampleShape.h"

Cylinder::Cylinder()
{
}

Cylinder::Cylinder(int param1, int param2) :
    Shape(),
    m_param1(param1),
    m_param2(param2)
{
    m_vertexData = generateVertexData(param1, param2);

    /** build the VAO so that the shape is ready to be drawn */
    buildVAO();
}

Cylinder::~Cylinder()
{
}

std::vector<GLfloat> Cylinder::generateVertexData(int param1, int param2) {
    std::vector<GLfloat> data = std::vector<GLfloat>();

    std::vector<GLfloat> angles = generateAngleVector(param2);
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

            std::vector<GLfloat> xzNorm1 = generatePositionVector(angle1, y1, 0.5);
            std::vector<GLfloat> xzNorm2 = generatePositionVector(angle1, y2, 0.5);
            std::vector<GLfloat> xzNorm3 = generatePositionVector(angle2, y1, 0.5);
            std::vector<GLfloat> xzNorm4 = generatePositionVector(angle2, y2, 0.5);

            // Side slices:
            data.insert(data.end(), xzNorm3.begin(), xzNorm3.end());
//            // TEXTURE HERE
//            float u;
//            float v = 0.5f - xzNorm3[1];

//            float angle = atan2(xzNorm3[2], xzNorm3[1]);

//            if (angle >= 0) {
//                u = 1.0f - (angle/(2*M_PI));
//            } else {
//                u = -angle / (2*M_PI);
//            }
//            data.push_back(u);
//            data.push_back(v);

            data.insert(data.end(), xzNorm2.begin(), xzNorm2.end());
//            // TEXTURE HERE
//            v = 0.5f - xzNorm2[1];

//            angle = atan2(xzNorm2[2], xzNorm2[1]);

//            if (angle >= 0) {
//                u = 1.0f - (angle/(2*M_PI));
//            } else {
//                u = -angle / (2*M_PI);
//            }
//            data.push_back(u);
//            data.push_back(v);

            data.insert(data.end(), xzNorm1.begin(), xzNorm1.end());
//            // TEXTURE HERE
//            v = 0.5f - xzNorm1[1];

//            angle = atan2(xzNorm1[2], xzNorm1[1]);

//            if (angle >= 0) {
//                u = 1.0f - (angle/(2*M_PI));
//            } else {
//                u = -angle / (2*M_PI);
//            }
//            data.push_back(u);
//            data.push_back(v);



            data.insert(data.end(), xzNorm4.begin(), xzNorm4.end());
//            // TEXTURE HERE
//            v = 0.5f - xzNorm4[1];

//            angle = atan2(xzNorm4[2], xzNorm4[1]);

//            if (angle >= 0) {
//                u = 1.0f - (angle/(2*M_PI));
//            } else {
//                u = -angle / (2*M_PI);
//            }
//            data.push_back(u);
//            data.push_back(v);

            data.insert(data.end(), xzNorm2.begin(), xzNorm2.end());
//            // TEXTURE HERE
//            v = 0.5f - xzNorm2[1];

//            angle = atan2(xzNorm2[2], xzNorm2[1]);

//            if (angle >= 0) {
//                u = 1.0f - (angle/(2*M_PI));
//            } else {
//                u = -angle / (2*M_PI);
//            }
//            data.push_back(u);
//            data.push_back(v);

            data.insert(data.end(), xzNorm3.begin(), xzNorm3.end());
//            // TEXTURE HERE
//            v = 0.5f - xzNorm3[1];

//            angle = atan2(xzNorm3[2], xzNorm3[1]);

//            if (angle >= 0) {
//                u = 1.0f - (angle/(2*M_PI));
//            } else {
//                u = -angle / (2*M_PI);
//            }
//            data.push_back(u);
//            data.push_back(v);

            float radiusIncrements = 0.5 / (float) param1;
            std::vector<GLfloat> topNormal = {0, 1, 0};
            std::vector<GLfloat> bottomNormal = {0, -1, 0};
            if (i == 0) {
                float faceRadius = (i + 1) * radiusIncrements;
                // Top
                std::vector<GLfloat> xzNormTop1 = generatePositionVector(angle1, 0.5, faceRadius);
                std::vector<GLfloat> xzNormTop2 = generatePositionVector(angle2, 0.5, faceRadius);

                data.push_back(0);
                data.push_back(0.5);
                data.push_back(0);
                data.insert(data.end(), topNormal.begin(), topNormal.end());
//                data.push_back(0.5f);
//                data.push_back(0.5f);

                data.insert(data.end(), xzNormTop2.begin(), xzNormTop2.begin()+3);
                data.insert(data.end(), topNormal.begin(), topNormal.end());
//                data.push_back(xzNormTop2[0] + 0.5f);
//                data.push_back(xzNormTop2[2] + 0.5f);

                data.insert(data.end(), xzNormTop1.begin(), xzNormTop1.begin()+3);
                data.insert(data.end(), topNormal.begin(), topNormal.end());
//                data.push_back(xzNormTop1[0] + 0.5f);
//                data.push_back(xzNormTop1[2] + 0.5f);

                // Bottom
                std::vector<GLfloat> xzNormBot1 = generatePositionVector(angle1, -0.5, faceRadius);
                std::vector<GLfloat> xzNormBot2 = generatePositionVector(angle2, -0.5, faceRadius);

                data.push_back(0);
                data.push_back(-0.5);
                data.push_back(0);
                data.insert(data.end(), bottomNormal.begin(), bottomNormal.end());

                data.insert(data.end(), xzNormBot1.begin(), xzNormBot1.begin()+3);
                data.insert(data.end(), bottomNormal.begin(), bottomNormal.end());

                data.insert(data.end(), xzNormBot2.begin(), xzNormBot2.begin()+3);
                data.insert(data.end(), bottomNormal.begin(), bottomNormal.end());
            } else {
                float faceRadius1 = i * radiusIncrements;
                float faceRadius2 = (i + 1) * radiusIncrements;
                std::vector<GLfloat> xzNormTop1 = generatePositionVector(angle1, 0.5, faceRadius1);
                std::vector<GLfloat> xzNormTop2 = generatePositionVector(angle1, 0.5, faceRadius2);
                std::vector<GLfloat> xzNormTop3 = generatePositionVector(angle2, 0.5, faceRadius1);
                std::vector<GLfloat> xzNormTop4 = generatePositionVector(angle2, 0.5, faceRadius2);

                data.insert(data.end(), xzNormTop3.begin(), xzNormTop3.begin()+3);
                data.insert(data.end(), topNormal.begin(), topNormal.end());
//                data.push_back(xzNormTop3[0] + 0.5f);
//                data.push_back(xzNormTop3[2] + 0.5f);

                data.insert(data.end(), xzNormTop2.begin(), xzNormTop2.begin()+3);
                data.insert(data.end(), topNormal.begin(), topNormal.end());
//                data.push_back(xzNormTop2[0] + 0.5f);
//                data.push_back(xzNormTop2[2] + 0.5f);

                data.insert(data.end(), xzNormTop1.begin(), xzNormTop1.begin()+3);
                data.insert(data.end(), topNormal.begin(), topNormal.end());
//                data.push_back(xzNormTop1[0] + 0.5f);
//                data.push_back(xzNormTop1[2] + 0.5f);


                data.insert(data.end(), xzNormTop4.begin(), xzNormTop4.begin()+3);
                data.insert(data.end(), topNormal.begin(), topNormal.end());
//                data.push_back(xzNormTop4[0] + 0.5f);
//                data.push_back(xzNormTop4[2] + 0.5f);

                data.insert(data.end(), xzNormTop2.begin(), xzNormTop2.begin()+3);
                data.insert(data.end(), topNormal.begin(), topNormal.end());
//                data.push_back(xzNormTop2[0] + 0.5f);
//                data.push_back(xzNormTop2[2] + 0.5f);

                data.insert(data.end(), xzNormTop3.begin(), xzNormTop3.begin()+3);
                data.insert(data.end(), topNormal.begin(), topNormal.end());
//                data.push_back(xzNormTop3[0] + 0.5f);
//                data.push_back(xzNormTop3[2] + 0.5f);

                std::vector<GLfloat> xzNormBot1 = generatePositionVector(angle1, -0.5, faceRadius1);
                std::vector<GLfloat> xzNormBot2 = generatePositionVector(angle1, -0.5, faceRadius2);
                std::vector<GLfloat> xzNormBot3 = generatePositionVector(angle2, -0.5, faceRadius1);
                std::vector<GLfloat> xzNormBot4 = generatePositionVector(angle2, -0.5, faceRadius2);

                data.insert(data.end(), xzNormBot1.begin(), xzNormBot1.begin()+3);
                data.insert(data.end(), bottomNormal.begin(), bottomNormal.end());
//                data.push_back(xzNormBot1[0] + 0.5f);
//                data.push_back(0.5f - xzNormBot1[2]);

                data.insert(data.end(), xzNormBot2.begin(), xzNormBot2.begin()+3);
                data.insert(data.end(), bottomNormal.begin(), bottomNormal.end());
//                data.push_back(xzNormBot2[0] + 0.5f);
//                data.push_back(0.5f - xzNormBot2[2]);

                data.insert(data.end(), xzNormBot3.begin(), xzNormBot3.begin()+3);
                data.insert(data.end(), bottomNormal.begin(), bottomNormal.end());
//                data.push_back(xzNormBot3[0] + 0.5f);
//                data.push_back(0.5f - xzNormBot3[2]);


                data.insert(data.end(), xzNormBot3.begin(), xzNormBot3.begin()+3);
                data.insert(data.end(), bottomNormal.begin(), bottomNormal.end());
//                data.push_back(xzNormBot3[0] + 0.5f);
//                data.push_back(0.5f - xzNormBot3[2]);

                data.insert(data.end(), xzNormBot2.begin(), xzNormBot2.begin()+3);
                data.insert(data.end(), bottomNormal.begin(), bottomNormal.end());
//                data.push_back(xzNormBot2[0] + 0.5f);
//                data.push_back(0.5f - xzNormBot2[2]);

                data.insert(data.end(), xzNormBot4.begin(), xzNormBot4.begin()+3);
                data.insert(data.end(), bottomNormal.begin(), bottomNormal.end());
//                data.push_back(xzNormBot4[0] + 0.5f);
//                data.push_back(0.5f - xzNormBot4[2]);
            }
        }
    }
    return data;
}

std::vector<GLfloat> Cylinder::generateAngleVector(int numSlices) {
    std::vector<GLfloat> angles = std::vector<GLfloat>();

    for (int i = 0; i < numSlices; i++) {
        float angle = (2*M_PI/(float) numSlices) * (float)i;
        angles.push_back(angle);
    }
    return angles;
}

std::vector<GLfloat> Cylinder::generatePositionVector(float angle, float y, float radius) {
    std::vector<GLfloat> positionsAndNormals = std::vector<GLfloat>();

    float x = radius * cos(angle);
    float z = radius * sin(angle);

    float xNorm = cos(angle);
    float zNorm = sin(angle);

    positionsAndNormals.push_back(x);
    positionsAndNormals.push_back(y);
    positionsAndNormals.push_back(z);
    positionsAndNormals.push_back(xNorm);
    positionsAndNormals.push_back(0);
    positionsAndNormals.push_back(zNorm);

    return positionsAndNormals;
}
