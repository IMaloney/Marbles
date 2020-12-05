#include "Shape.h"



using namespace CS123::GL;

Shape::Shape() :
    m_drawMode(CS123::GL::VBO::LAYOUT_TRIANGLES),
    m_VAO(nullptr)
{

}

Shape::~Shape()
{
}


// TODO: update this to reflect the comment inside
void Shape::draw() {
    // this may need to be updated since the textures will depend on the order of drawing
    if (m_VAO) {
        m_VAO->bind();
        m_VAO->draw();
        m_VAO->unbind();
    }
}

void Shape::setDrawMode(CS123::GL::VBO::GEOMETRY_LAYOUT mode){
    m_drawMode = mode;
}

//void Shape::setAttribute(GLuint name, GLuint numElementsPerVertex, int offset,
//                               VBOAttribMarker::DATA_TYPE type, bool normalize) {
//    m_markers.push_back(VBOAttribMarker(name, numElementsPerVertex, offset, type, normalize));
//}


// this shape needs to be more extensible
void Shape::buildVAO() {
    // commenting out the normals for testing (will need them for lighting)
    const int numFloatsPerVertex = 3;
    const int numVertices = m_vertexData.size() / numFloatsPerVertex;

    std::vector<VBOAttribMarker> markers;
    markers.push_back(VBOAttribMarker(ShaderAttrib::POSITION, 3, 0));
//    markers.push_back(VBOAttribMarker(ShaderAttrib::NORMAL, 3, 3*sizeof(float)));
//    markers.push_back(VBOAttribMarker(ShaderAttrib::POSITION, 3, 0));
//    markers.push_back(VBOAttribMarker(ShaderAttrib::NORMAL, 3, 3*sizeof(float)));
    markers.push_back(VBOAttribMarker(ShaderAttrib::TEXCOORD0, 2, 3*sizeof(float)));
    VBO vbo = VBO(m_vertexData.data(), m_vertexData.size(), markers, m_drawMode);
    m_VAO = std::make_unique<VAO>(vbo, numVertices);
}
