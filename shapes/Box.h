#ifndef BOX_H
#define BOX_H

#include "Shape.h"
#include "ShapeUtils.h"
#include "qimage.h"

#include "GL/glew.h"

#include <vector>
#include <iostream>
#include "gl/textures/Texture2D.h"

class Box : public Shape
{
public:
    Box(float size=1.f);
    virtual ~Box();
    void draw();

    GLuint getTextureID();

    CS123::GL::Texture2D getTexture();



// using m_vertexData from shape to store points
// methods to add: wall shading etc...
private:
    float m_size;
    GLuint m_textureID;
    QImage m_texture;
    CS123::GL::Texture2D m_textureTexture;
    // buildFace method removed (just a hardcoded face)
    void buildBox();
    void initializeTexture();

};

#endif // BOX_H
