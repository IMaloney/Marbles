#include "Sphere.h"

Sphere::Sphere()
{
}

Sphere::Sphere(float radius) :
    Shape(),
    // changed it to be a multiple of four for the quadrants
    m_param1(24),
    m_param2(24),
    m_cylinder(),
    m_radius(radius),
    m_broken(false)
{
    m_vertexData = generateVertexData(m_param1, m_param2);
    /** build the VAO so that the shape is ready to be drawn */
//    buildVAO();
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
//    buildVAO();
}

Sphere::~Sphere()
{
}

std::vector<GLfloat> Sphere::generateVertexData(int param1, int param2) {
//    std::cout << "param 2: " << param2 << std::endl;
    std::vector<GLfloat> data = std::vector<GLfloat>();
    int switchQuad = m_param2 / 4;
    std::vector<GLfloat> anglesLat = generateLatitudeAngleVector(param1);
    std::vector<GLfloat> anglesLon = m_cylinder.generateAngleVector(param2);
    int quad = -2;
    for (int i = 0; i < param1; i++) {
        for (int j = 0; j < param2; j++) {
            if ((j) && !((j) % switchQuad)) {
                quad += 1;
                // skip zero so the quads are -2, -1, 1, 2 --> rotate the point to find what normal you will use
                if (!quad) quad += 1;
            }
            std::cout << "current quad: " << quad << std::endl;
            std::cout << "j value: " << j << std::endl;
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

                addPointAndNorm(&data, point3, quad);
                addUVCoords(&data, point3);
                addPointAndNorm(&data, point2, quad);
                addUVCoords(&data, point2);
                addPointAndNorm(&data, point1, quad);
                addUVCoords(&data, point1);


            } else if (i == param1 - 1) {
                glm::vec3 point1 = sphereToCartesian(m_radius, anglesLat[param1 - 1], angleLon1);
                glm::vec3 point2 = sphereToCartesian(m_radius, anglesLat[param1], angleLon1);
                glm::vec3 point3 = sphereToCartesian(m_radius, anglesLat[param1 - 1], angleLon2);

                addPointAndNorm(&data, point3, quad);
                addUVCoords(&data, point3);
                addPointAndNorm(&data, point2, quad);
                addUVCoords(&data, point2);
                addPointAndNorm(&data, point1, quad);
                addUVCoords(&data, point1);
            } else {
                glm::vec3 point1 = sphereToCartesian(m_radius, anglesLat[i], angleLon1);
                glm::vec3 point2 = sphereToCartesian(m_radius, anglesLat[i+1], angleLon1);
                glm::vec3 point3 = sphereToCartesian(m_radius, anglesLat[i], angleLon2);
                glm::vec3 point4 = sphereToCartesian(m_radius, anglesLat[i+1], angleLon2);

                addPointAndNorm(&data, point3, quad);
                addUVCoords(&data, point3);
                addPointAndNorm(&data, point2, quad);
                addUVCoords(&data, point2);
                addPointAndNorm(&data, point1, quad);
                addUVCoords(&data, point1);

                addPointAndNorm(&data, point4, quad);
                addUVCoords(&data, point4);
                addPointAndNorm(&data, point2, quad);
                addUVCoords(&data, point2);
                addPointAndNorm(&data, point3, quad);
                addUVCoords(&data, point3);
            }
        }
        // reset since we gonna do another loop
        quad = -2;
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

void Sphere::addPointAndNorm(std::vector<GLfloat>* data, glm::vec3 point, int quad) {
    std::map<int, std::vector<std::pair<int, int>>>::iterator qtrIt;
    // this will store array at ->second
    data->push_back(point.x);
    data->push_back(point.y);
    data->push_back(point.z);
    // Normal is the same as the point!!!
    data->push_back(point.x);
    data->push_back(point.y);
    data->push_back(point.z);
    // keep track of size to optimize
    int lastIdx = data->size() - 1;
// iterators for maps:
// (key: vec3 point --> value int quadrant)
// (key: int --> value vector of ranges of points inside the original list quadrant)
//    std::map<glm::vec3, int>::iterator ptqIt;
    // to optimize, just pass a reference to this vector into the function
    qtrIt = m_quadToRangeMap.find(quad);
    if (qtrIt == m_quadToRangeMap.end()) {
        std::pair<std::map<int, std::vector<std::pair<int, int>>>::iterator, bool> p;
        // place a vector inside the map at quad that holds the pairs that will make up the range for the points (range will either just be the point or will include the uv points)
        p = m_quadToRangeMap.insert(std::pair<int, std::vector<std::pair<int, int>>>(quad, std::vector<std::pair<int, int>>()));
        qtrIt = std::get<0>(p);
    }
    qtrIt->second.push_back(std::pair<int, int>(lastIdx - 5, lastIdx));

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

// seems like triangles are already drawn individually so this may not be necessary
void Sphere::isBroken(){
    // if the sphere is broken, change the drawing mode so that there are individual triangles
    if (m_broken) m_VAO->setDrawMode(CS123::GL::VBO::GEOMETRY_LAYOUT::LAYOUT_TRIANGLES);
}


void Sphere::printQuadInfo() {
    std::cout << "size of full vertex array: " << m_vertexData.size() << std::endl;
    for (auto const& x : m_quadToRangeMap)
    {
        std::cout << x.first  // key (-2,-1,1,2)
                  << ':'
                  << x.second.size() // value (len of array)
                  << std::endl ;
    }
}
