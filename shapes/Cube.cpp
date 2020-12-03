#include "Cube.h"

Cube::Cube()
{
}

Cube::Cube(int param1, int param2) :
    m_param1(param1),
    m_param2(param2),
    Shape()
{
    m_vertexData = generateVertexData(m_param1, m_param2); //CUBE_DATA_POSITIONS;
    /** build the VAO so that the shape is ready to be drawn */
    buildVAO();
}

Cube::~Cube()
{
}

std::vector<GLfloat> Cube::generateVertexData(int param1, int param2) {
    std::vector<GLfloat> data = std::vector<GLfloat>();

    float squareSize = 1.0 / (float) param1;

    // Front face
    std::vector<GLfloat> first = {-0.5, 0.5, 0.5};
    std::vector<GLfloat> normal = {0, 0, 1};
    std::vector<GLfloat> plane = {1, -1, 0};
    data = buildZPlaneSide(data, first, normal, plane, param1, squareSize);

    // Back face
    first = {0.5, 0.5, -0.5};
    normal = {0, 0, -1};
    plane = {-1, -1, 0};
    data = buildZPlaneSide(data, first, normal, plane, param1, squareSize);

    // Top face
    first = {-0.5, 0.5, -0.5};
    normal = {0, 1, 0};
    plane = {1, 0, 1};
    data = buildYPlaneSide(data, first, normal, plane, param1, squareSize);

    // Bottom face
    first = {-0.5, -0.5, 0.5};
    normal = {0, -1, 0};
    plane = {1, 0, -1};
    data = buildYPlaneSide(data, first, normal, plane, param1, squareSize);

    // Left face
    first = {-0.5, 0.5, -0.5};
    normal = {-1, 0, 0};
    plane = {0, -1, 1};
    data = buildXPlaneSide(data, first, normal, plane, param1, squareSize);

    // Right face
    first = {0.5, 0.5, 0.5};
    normal = {1, 0, 0};
    plane = {0, -1, -1};
    data = buildXPlaneSide(data, first, normal, plane, param1, squareSize);

    return data;
}

std::vector<GLfloat> Cube::buildZPlaneSide(std::vector<GLfloat> verts, std::vector<GLfloat> first, std::vector<GLfloat> normal,
               std::vector<GLfloat> plane, int squaresPerRow, GLfloat squareSize) {

    for (int i = 0; i < squaresPerRow; i++) {
        for (int j = 0; j < squaresPerRow; j++) {
            // First triangle in square
            // Coordianates
            verts.push_back(first[0] + i*squareSize*plane[0]);
            verts.push_back(first[1] + j*squareSize*plane[1]);
            verts.push_back(first[2]);

            // Normal
            verts.insert(verts.end(), normal.begin(), normal.end());

            // TEXTURE HERE
//            if (plane[0] == 1) {
//                verts.push_back((first[0] + i*squareSize*plane[0]) + 0.5f);
//                verts.push_back(0.5f - (first[1] + j*squareSize*plane[1]));
//            } else {
//                verts.push_back(0.5f - (first[0] + i*squareSize*plane[0]));
//                verts.push_back(0.5f - (first[1] + j*squareSize*plane[1]));
//            }


            // Coordianates
            verts.push_back(first[0] + i*squareSize*plane[0]);
            verts.push_back(first[1] + (j*squareSize + squareSize)*plane[1]);
            verts.push_back(first[2]);

            // Normal
            verts.insert(verts.end(), normal.begin(), normal.end());

            // TEXTURE HERE

//            if (plane[0] == 1) {
//                verts.push_back((first[0] + i*squareSize*plane[0]) + 0.5f);
//                verts.push_back(0.5f - (first[1] + (j*squareSize + squareSize)*plane[1]));
//            } else {
//                verts.push_back(0.5f - (first[0] + i*squareSize*plane[0]));
//                verts.push_back(0.5f - (first[1] + (j*squareSize + squareSize)*plane[1]));
//            }


            // Coordianates
            verts.push_back(first[0] + (i*squareSize + squareSize)*plane[0]);
            verts.push_back(first[1] + (j*squareSize + squareSize)*plane[1]);
            verts.push_back(first[2]);

            // Normal
            verts.insert(verts.end(), normal.begin(), normal.end());

            // TEXTURE HERE

//            if (plane[0] == 1) {
//                verts.push_back((first[0] + (i*squareSize + squareSize)*plane[0]) + 0.5f);
//                verts.push_back(0.5f - (first[1] + (j*squareSize + squareSize)*plane[1]));
//            } else {
//                verts.push_back(0.5f - (first[0] + (i*squareSize + squareSize)*plane[0]));
//                verts.push_back(0.5f - (first[1] + (j*squareSize + squareSize)*plane[1]));
//            }


            // Second triangle in square
            // Coordianates
            verts.push_back(first[0] + i*squareSize*plane[0]);
            verts.push_back(first[1] + j*squareSize*plane[1]);
            verts.push_back(first[2]);

            // Normal
            verts.insert(verts.end(), normal.begin(), normal.end());

            // TEXTURE HERE

//            if (plane[0] == 1) {
//                verts.push_back((first[0] + i*squareSize*plane[0]) + 0.5f);
//                verts.push_back(0.5f - (first[1] + j*squareSize*plane[1]));
//            } else {
//                verts.push_back(0.5f - (first[0] + i*squareSize*plane[0]));
//                verts.push_back(0.5f - (first[1] + j*squareSize*plane[1]));
//            }


            // Coordianates
            verts.push_back(first[0] + (i*squareSize + squareSize)*plane[0]);
            verts.push_back(first[1] + (j*squareSize + squareSize)*plane[1]);
            verts.push_back(first[2]);

            // Normal
            verts.insert(verts.end(), normal.begin(), normal.end());

            // TEXTURE HERE

//            if (plane[0] == 1) {
//                verts.push_back((first[0] + (i*squareSize + squareSize)*plane[0]) + 0.5f);
//                verts.push_back(0.5f - (first[1] + (j*squareSize + squareSize)*plane[1]));
//            } else {
//                verts.push_back(0.5f - (first[0] + (i*squareSize + squareSize)*plane[0]));
//                verts.push_back(0.5f - (first[1] + (j*squareSize + squareSize)*plane[1]));
//            }


            // Coordianates
            verts.push_back(first[0] + (i*squareSize + squareSize)*plane[0]);
            verts.push_back(first[1] + j*squareSize*plane[1]);
            verts.push_back(first[2]);

            // Normal
            verts.insert(verts.end(), normal.begin(), normal.end());

            // TEXTURE HERE

//            if (plane[0] == 1) {
//                verts.push_back((first[0] + (i*squareSize + squareSize)*plane[0]) + 0.5f);
//                verts.push_back(0.5f - (first[1] + j*squareSize*plane[1]));
//            } else {
//                verts.push_back(0.5f - (first[0] + i*squareSize*plane[0]));
//                verts.push_back(0.5f - (first[1] + j*squareSize*plane[1]));
//            }


        }
    }
    return verts;
}

std::vector<GLfloat> Cube::buildYPlaneSide(std::vector<GLfloat> verts, std::vector<GLfloat> first, std::vector<GLfloat> normal,
               std::vector<GLfloat> plane, int squaresPerRow, GLfloat squareSize) {

    for (int i = 0; i < squaresPerRow; i++) {
        for (int j = 0; j < squaresPerRow; j++) {

            // First triangle in square
            // Coordianates
            verts.push_back(first[0] + i*squareSize*plane[0]);
            verts.push_back(first[1]);
            verts.push_back(first[2] + j*squareSize*plane[2]);

            // Normal
            verts.insert(verts.end(), normal.begin(), normal.end());

            // TEXTURE HERE

//            if (plane[2] == 1) {

//                verts.push_back((first[0] + i*squareSize*plane[0]) + 0.5f);
//                verts.push_back((first[2] + j*squareSize*plane[2]) + 0.5f);
//            } else {

//                verts.push_back((first[0] + i*squareSize*plane[0]) + 0.5f);
//                verts.push_back(0.5f - (first[2] + j*squareSize*plane[2]));
//            }


            // Coordianates
            verts.push_back(first[0] + i*squareSize*plane[0]);
            verts.push_back(first[1]);
            verts.push_back(first[2] + (j*squareSize + squareSize)*plane[2]);

            // Normal
            verts.insert(verts.end(), normal.begin(), normal.end());

            // TEXTURE HERE

//            if (plane[2] == 1) {

//                verts.push_back((first[0] + i*squareSize*plane[0]) + 0.5f);
//                verts.push_back((first[2] + j*squareSize*plane[2]) + 0.5f);
//            } else {

//                verts.push_back((first[0] + i*squareSize*plane[0]) + 0.5f);
//                verts.push_back(0.5f - (first[2] + j*squareSize*plane[2]));
//            }

            // Coordianates
            verts.push_back(first[0] + i*squareSize + squareSize*plane[0]);
            verts.push_back(first[1]);
            verts.push_back(first[2] + (j*squareSize + squareSize)*plane[2]);

            // Normal
            verts.insert(verts.end(), normal.begin(), normal.end());

            // TEXTURE HERE

//            if (plane[2] == 1) {

//                verts.push_back((first[0] + i*squareSize*plane[0]) + 0.5f);
//                verts.push_back((first[2] + j*squareSize*plane[2]) + 0.5f);
//            } else {

//                verts.push_back((first[0] + i*squareSize*plane[0]) + 0.5f);
//                verts.push_back(0.5f - (first[2] + j*squareSize*plane[2]));
//            }

            // Second triangle in square
            // Coordianates
            verts.push_back(first[0] + i*squareSize*plane[0]);
            verts.push_back(first[1]);
            verts.push_back(first[2] + j*squareSize*plane[2]);

            // Normal
            verts.insert(verts.end(), normal.begin(), normal.end());

            // TEXTURE HERE

//            if (plane[2] == 1) {

//                verts.push_back((first[0] + i*squareSize*plane[0]) + 0.5f);
//                verts.push_back((first[2] + j*squareSize*plane[2]) + 0.5f);
//            } else {

//                verts.push_back((first[0] + i*squareSize*plane[0]) + 0.5f);
//                verts.push_back(0.5f - (first[2] + j*squareSize*plane[2]));
//            }

            // Coordianates
            verts.push_back(first[0] + (i*squareSize + squareSize)*plane[0]);
            verts.push_back(first[1]);
            verts.push_back(first[2] + (j*squareSize + squareSize)*plane[2]);

            // Normal
            verts.insert(verts.end(), normal.begin(), normal.end());

            // TEXTURE HERE

//            if (plane[2] == 1) {

//                verts.push_back((first[0] + i*squareSize*plane[0]) + 0.5f);
//                verts.push_back((first[2] + j*squareSize*plane[2]) + 0.5f);
//            } else {

//                verts.push_back((first[0] + i*squareSize*plane[0]) + 0.5f);
//                verts.push_back(0.5f - (first[2] + j*squareSize*plane[2]));
//            }

            // Coordianates
            verts.push_back(first[0] + (i*squareSize + squareSize)*plane[0]);
            verts.push_back(first[1]);
            verts.push_back(first[2] + j*squareSize*plane[2]);

            // Normal
            verts.insert(verts.end(), normal.begin(), normal.end());

            // TEXTURE HERE

//            if (plane[2] == 1) {

//                verts.push_back((first[0] + i*squareSize*plane[0]) + 0.5f);
//                verts.push_back((first[2] + j*squareSize*plane[2]) + 0.5f);
//            } else {

//                verts.push_back((first[0] + i*squareSize*plane[0]) + 0.5f);
//                verts.push_back(0.5f - (first[2] + j*squareSize*plane[2]));
//            }

        }
    }
    return verts;
}

std::vector<GLfloat> Cube::buildXPlaneSide(std::vector<GLfloat> verts, std::vector<GLfloat> first, std::vector<GLfloat> normal,
               std::vector<GLfloat> plane, int squaresPerRow, GLfloat squareSize) {

    for (int i = 0; i < squaresPerRow; i++) {
        for (int j = 0; j < squaresPerRow; j++) {

            // First triangle in square
            // Coordianates
            verts.push_back(first[0]);
            verts.push_back(first[1] + i*squareSize*plane[1]);
            verts.push_back(first[2] + j*squareSize*plane[2]);

            // Normal
            verts.insert(verts.end(), normal.begin(), normal.end());

            // TEXTURE HERE
//            if (plane[2] == 1) {

//                verts.push_back((first[2] + j*squareSize*plane[2]) + 0.5f);
//                verts.push_back(0.5f - (first[1] + i*squareSize*plane[1]));
//            } else {

//                verts.push_back(0.5f - (first[2] + j*squareSize*plane[2]));
//                verts.push_back(0.5f - (first[1] + i*squareSize*plane[1]));
//            }

            // Coordianates
            verts.push_back(first[0]);
            verts.push_back(first[1] + (i*squareSize + squareSize)*plane[1]);
            verts.push_back(first[2] + j*squareSize*plane[2]);

            // Normal
            verts.insert(verts.end(), normal.begin(), normal.end());

            // TEXTURE HERE
//            if (plane[2] == 1) {

//                verts.push_back((first[2] + j*squareSize*plane[2]) + 0.5f);
//                verts.push_back(0.5f - (first[1] + i*squareSize*plane[1]));
//            } else {

//                verts.push_back(0.5f - (first[2] + j*squareSize*plane[2]));
//                verts.push_back(0.5f - (first[1] + i*squareSize*plane[1]));
//            }


            // Coordianates
            verts.push_back(first[0]);
            verts.push_back(first[1] + (i*squareSize + squareSize)*plane[1]);
            verts.push_back(first[2] + (j*squareSize + squareSize)*plane[2]);

            // Normal
            verts.insert(verts.end(), normal.begin(), normal.end());

            // TEXTURE HERE
//            if (plane[2] == 1) {

//                verts.push_back((first[2] + j*squareSize*plane[2]) + 0.5f);
//                verts.push_back(0.5f - (first[1] + i*squareSize*plane[1]));
//            } else {

//                verts.push_back(0.5f - (first[2] + j*squareSize*plane[2]));
//                verts.push_back(0.5f - (first[1] + i*squareSize*plane[1]));
//            }


            // Second triangle in square
            // Coordianates
            verts.push_back(first[0]);
            verts.push_back(first[1] + i*squareSize*plane[1]);
            verts.push_back(first[2] + j*squareSize*plane[2]);

            // Normal
            verts.insert(verts.end(), normal.begin(), normal.end());

            // TEXTURE HERE
//            if (plane[2] == 1) {

//                verts.push_back((first[2] + j*squareSize*plane[2]) + 0.5f);
//                verts.push_back(0.5f - (first[1] + i*squareSize*plane[1]));
//            } else {

//                verts.push_back(0.5f - (first[2] + j*squareSize*plane[2]));
//                verts.push_back(0.5f - (first[1] + i*squareSize*plane[1]));
//            }


            // Coordianates
            verts.push_back(first[0]);
            verts.push_back(first[1] + (i*squareSize + squareSize)*plane[1]);
            verts.push_back(first[2] + (j*squareSize + squareSize)*plane[2]);

            // Normal
            verts.insert(verts.end(), normal.begin(), normal.end());

            // TEXTURE HERE
//            if (plane[2] == 1) {

//                verts.push_back((first[2] + j*squareSize*plane[2]) + 0.5f);
//                verts.push_back(0.5f - (first[1] + i*squareSize*plane[1]));
//            } else {

//                verts.push_back(0.5f - (first[2] + j*squareSize*plane[2]));
//                verts.push_back(0.5f - (first[1] + i*squareSize*plane[1]));
//            }


            // Coordianates
            verts.push_back(first[0]);
            verts.push_back(first[1] + i*squareSize*plane[1]);
            verts.push_back(first[2] + (j*squareSize + squareSize)*plane[2]);

            // Normal
            verts.insert(verts.end(), normal.begin(), normal.end());

            // TEXTURE HERE
//            if (plane[2] == 1) {

//                verts.push_back((first[2] + j*squareSize*plane[2]) + 0.5f);
//                verts.push_back(0.5f - (first[1] + i*squareSize*plane[1]));
//            } else {

//                verts.push_back(0.5f - (first[2] + j*squareSize*plane[2]));
//                verts.push_back(0.5f - (first[1] + i*squareSize*plane[1]));
//            }

        }
    }
    return verts;
}
