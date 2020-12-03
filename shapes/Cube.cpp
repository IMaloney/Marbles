#include "Cube.h"
#include "gl/shaders/ShaderAttribLocations.h"

Cube::Cube(int param1)
    : Shape(param1, 4)
{
    /** build the VAO so that the shape is ready to be drawn */
    m_minParam1 = 1;
    m_minParam2 = 1;
    this->checkMins();
    this->createShape();
}

Cube::~Cube()
{

}


std::vector<float> Cube::buildShape()
{
    std::vector<float> ret;
    // og face
    this->buildFace(Point(-0.5, 0.5f, 0.5f));
    ShapeUtils::combine(&ret, m_face);

    glm::mat4 mat = glm::rotate((float) M_PI * -.5f, glm::vec3(0, 1, 0));
    std::vector<float> side = ShapeUtils::rotate(m_face, mat);
    ShapeUtils::combine(&ret, side);

    mat = glm::rotate((float) M_PI * .5f, glm::vec3(0, 1, 0));
    side = ShapeUtils::rotate(m_face, mat);
    ShapeUtils::combine(&ret, side);

    mat = glm::rotate((float) M_PI * .5f, glm::vec3(1, 0, 0));
    side = ShapeUtils::rotate(m_face, mat);
    ShapeUtils::combine(&ret, side);

    mat = glm::rotate((float) M_PI * -.5f, glm::vec3(1, 0, 0));
    side = ShapeUtils::rotate(m_face, mat);
    ShapeUtils::combine(&ret, side);


    mat = glm::rotate((float) M_PI, glm::vec3(0, 1, 0));
    side = ShapeUtils::rotate(m_face, mat);
    ShapeUtils::combine(&ret, side);

    return ret;
}


void Cube::buildFace(Point p)
{
    Point p1, p2, p3, p4;
    std::unique_ptr<Rectangle> rect;
    float px, x, y, py,
          pz = p.getZ(),
          size = 1.f/m_sParam1;
    for (int i = 0; i < m_sParam1; i++){
        y = -1 * (i * size);
        for (int j = 0; j < m_sParam1; j++) {
            x = j * size;
            px = p.getX() + x;
            py = p.getY() + y;
            p1 = Point(px, py, pz);
            p2 = Point(px + size, py, pz);
            p3 = Point(px + size, py - size, pz);
            p4 = Point(px, py - size, pz);
            rect = std::make_unique<Rectangle>(p1, p2, p3, p4);
            ShapeUtils::combine(&m_points, rect->getPoints());
            ShapeUtils::combine(&m_face, rect->getPoints());

        }
    }
}
