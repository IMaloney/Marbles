#include "Box.h"

// testing
#include <iostream>
#include "gl/GLDebug.h"

// not a fan of putting this file in the shapes but I guess its
// inheriting from shape so


// no need for parameters since this will be a consitent size, need to make sure the marbles never
// get larger than the initial box
Box::Box(float size) :
    m_size(size),
    m_textureID(0)
{
    m_texture = QImage("../textures/real_marble.png");
    std::cout<< "width: " << m_texture.width() << std::endl;
    this->buildBox();
    this->buildVAO();
    this->initializeTexture();
}


Box::~Box() {
    // box gets redrawn every time so I guess it wouldn't make sense to just delete it after drawing
    glDeleteTextures(1, &m_textureID);

}



void Box::buildBox() {
    glm::mat4 mat;

    GLfloat ogFace []= {
        // TRIANGLE 1
        // p1
        -m_size, m_size, m_size,
        // uv1
        0.f, 1.f,
        //p2
        m_size, m_size, m_size,
        1.f, 1.f,

        // p3
        m_size, -m_size, m_size,
        1.f, 0.f,

        // TRIANGLE 2
        // p1
        -m_size, m_size, m_size,
        0.f, 1.f,

        // p2
        m_size, -m_size, m_size,
        1.f, 0.f,

        // p3
        -m_size, -m_size, m_size,
        0.f, 0.f

    };

    // because we don't want to actually count up how many things are in the array
    int size = sizeof(ogFace) / sizeof(ogFace[0]);

    // adding first face
    ShapeUtils::addPoints(ogFace, size, m_vertexData);

    // bottom face
    mat = glm::rotate((float) M_PI * -.5f, glm::vec3(0, 1, 0));
    ShapeUtils::rotateUV(mat, ogFace, size, m_vertexData);

    // top face
    mat = glm::rotate((float) M_PI * .5f, glm::vec3(0, 1, 0));
    ShapeUtils::rotateUV(mat, ogFace, size, m_vertexData);

    // right face
    mat = glm::rotate((float) M_PI * .5f, glm::vec3(1, 0, 0));
    ShapeUtils::rotateUV(mat, ogFace, size, m_vertexData);

    // left face
    mat = glm::rotate((float) M_PI * -.5f, glm::vec3(1, 0, 0));
    ShapeUtils::rotateUV(mat, ogFace, size, m_vertexData);
    // back face
    mat = glm::rotate((float) M_PI, glm::vec3(0, 1, 0));
    ShapeUtils::rotateUV(mat, ogFace, size, m_vertexData);
}

void Box::draw() {
    // depending on the order this may not be necessary --> probably safer to have it though
//    glBindTexture(m_textureID, GL_TEXTURE_2D);
    this->Shape::draw();

}


void Box::initializeTexture() {
    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID); //not sure where to unbind the texture
    // maybe GL_LINEAR rather than GL_NEAREST
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // horizontal wrap --> this will not extend area
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    // no tiling
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_texture.width(), m_texture.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_texture.bits());
}
