#include "Box.h"


// not a fan of putting this file in the shapes but I guess its
// inheriting from shape so


// no need for parameters since this will be a consitent size, need to make sure the marbles never
// get larger than the initial box
Box::Box(float size) :
    m_size(size)
{
    std::cout << "building the boxx" << std::endl;
    this->buildBox();
    this->buildVAO();
}


Box::~Box() {

}



void Box::buildBox() {
    glm::mat4 mat;

    GLfloat ogFace []= {
        // TRIANGLE 1
        // p1
        -m_size, m_size, m_size,

        //p2
        m_size, m_size, m_size,


        // p3
        m_size, -m_size, m_size,


        // TRIANGLE 2
        // p1
        -m_size, m_size, m_size,


        // p2
        m_size, -m_size, m_size,


        // p3
        -m_size, -m_size, m_size


    };

    // because we don't want to actually count up how many things are in the array
    int size = sizeof(ogFace) / sizeof(ogFace[0]);

    // adding first face
    ShapeUtils::addPoints(ogFace, size, m_vertexData);

    // bottom face
    mat = glm::rotate((float) M_PI * -.5f, glm::vec3(0, 1, 0));
    ShapeUtils::rotate(mat, ogFace, size, m_vertexData);

    // top face
    mat = glm::rotate((float) M_PI * .5f, glm::vec3(0, 1, 0));
    ShapeUtils::rotate(mat, ogFace, size, m_vertexData);

    // right face
    mat = glm::rotate((float) M_PI * .5f, glm::vec3(1, 0, 0));
    ShapeUtils::rotate(mat, ogFace, size, m_vertexData);

    // left face
    mat = glm::rotate((float) M_PI * -.5f, glm::vec3(1, 0, 0));
    ShapeUtils::rotate(mat, ogFace, size, m_vertexData);
    // back face
    mat = glm::rotate((float) M_PI, glm::vec3(0, 1, 0));
    ShapeUtils::rotate(mat, ogFace, size, m_vertexData);
    std::cout << "vertex size: " << m_vertexData.size() << std::endl;
}

