#include "Shape.h"
#include "gl/datatype/VAO.h"
#include "gl/datatype/VBO.h"
#include "gl/datatype/VBOAttribMarker.h"
#include "gl/shaders/ShaderAttribLocations.h"

using namespace CS123::GL;

Shape::Shape(int param1, int param2) :
    m_VAO(nullptr),
    m_drawMode(VBO::GEOMETRY_LAYOUT::LAYOUT_TRIANGLES),
    m_sParam1(param1),
    m_sParam2(param2),
    m_minParam1(0),
    m_minParam2(0)
{

}

Shape::~Shape()
{
}


void Shape::draw() {
    if (m_VAO) {
        m_VAO->bind();
        m_VAO->draw();
        m_VAO->unbind();
    }
}

void Shape::buildVAO() {
//    excluding normal
    const int numFloatsPerVertex = 3;
    const int numVertices = m_size / numFloatsPerVertex;
//    markers.push_back(VBOAttribMarker(ShaderAttrib::NORMAL, 3, 3*sizeof(float)));
    // drawmode VBO::GEOMETRY_LAYOUT::LAYOUT_TRIANGLES
    VBO vbo = VBO(m_data, m_size, m_markers, m_drawMode);
    m_VAO = std::make_unique<VAO>(vbo, numVertices);
}

/**
 * @param data - Vector of floats containing the vertex data.
 * @param size - number of elements in the array.
 * @param drawMode - Drawing mode
 * @param numVertices - Number of vertices to be rendered.
 */
void Shape::setVertexData(GLfloat *data, int size, VBO::GEOMETRY_LAYOUT drawMode, int numVertices) {
    // Store the vertex data and other values to be used later when constructing the VAO
    m_data = data;
    m_size = size;
    m_numVertices = numVertices;
    m_drawMode = drawMode;
}


/**
 * @param index OpenGL handle to the attribute location. These are specified in ShaderAttribLocations.h
 * @param numElementsPerVertex Number of elements per vertex. Must be 1, 2, 3 or 4 (e.g. position = 3 for x,y,z)
 * @param offset Offset in BYTES from the start of the array to the beginning of the first element
 * @param type Primitive type (FLOAT, INT, UNSIGNED_BYTE)
 * @param normalize
 */
void Shape::setAttribute(
         GLuint index, GLuint numElementsPerVertex, int offset, VBOAttribMarker::DATA_TYPE type, bool normalize) {
    std::vector<VBOAttribMarker> markers;
//    m_markers.push_back(VBOAttribMarker(ShaderAttrib::POSITION, 3, 0));
    m_markers.push_back(VBOAttribMarker(index, numElementsPerVertex, offset, type, normalize));
}

void Shape::createShape() {
    std::vector<float> point = this->buildShape();
    this->setVertexData(point.data(), point.size(), VBO::GEOMETRY_LAYOUT::LAYOUT_TRIANGLES, point.size()/3);
    this->setAttribute(ShaderAttrib::POSITION, 3, 0, VBOAttribMarker::DATA_TYPE::FLOAT, false);
//    this->setAttribute(ShaderAttrib::NORMAL, 3, 3*sizeof(float), VBOAttribMarker::DATA_TYPE::FLOAT, false);

    this->buildVAO();

}

int Shape::getMinParam1(){
    return m_minParam1;
}

int Shape::getMinParam2(){
    return m_minParam2;
}

void Shape::checkMins()
{
    m_sParam1 = (m_sParam1 < m_minParam1) ? m_minParam1 : m_sParam1;
    m_sParam2 = (m_sParam2 < m_minParam2) ? m_minParam2 : m_sParam2;
}

std::vector<float> ShapeUtils::translate(std::vector<float> points, glm::vec3 vec)
{
    std::vector<float> ret;
    int size = points.size();
    glm::mat4 mat = glm::translate(vec);
    glm::vec4 T;
    glm::vec3 temp;
    for (int i = 2; i < size; i += 3) {
        T = glm::vec4(points[i-2], points[i-1], points[i], 1.0f);
        temp = (mat * T).xyz();
        insertVec3(ret, temp);
    }
    return ret;
}

std::vector<float> ShapeUtils::rotate(std::vector<float> points, glm::mat4 mat)
{
    std::vector<float> ret;
    glm::vec3 point, rotatedPoint;
    int size = points.size();
    for (int i = 2; i < size; i+=3) {
        point = glm::vec3(points[i-2], points[i-1], points[i]);
        rotatedPoint = ((mat * glm::vec4(point, 1.0)).xyz());
        insertVec3(ret, rotatedPoint);
    }
    return ret;
}

void ShapeUtils::combine(std::vector<float> *shape, std::vector<float> points)
{
    int s = points.size();
    for (int i =0; i < s; i++){
        shape->push_back(points[i]);
    }
}

float ShapeUtils::dot(Point p1, Point p2)
{
    return (p1.getX() * p2.getX()) + (p1.getY() * p2.getY()) + (p1.getZ() * p2.getZ());
}

float ShapeUtils::length(Point p1)
{
    return ShapeUtils::distance(p1, Point(0.f,0.f,0.f));
}

float ShapeUtils::distance(Point p1, Point p2)
{
    return std::sqrt(std::pow(p1.getX() - p2.getX(), 2.0) + std::pow(p1.getY() - p2.getY(), 2.0) + std::pow(p1.getZ() - p2.getZ(), 2.0));
}

float ShapeUtils::findAngle(Point p1, Point p2)
{
    return std::acos(ShapeUtils::dot(p1, p2)/ (ShapeUtils::length(p1)*ShapeUtils::length(p2)));
}


float ShapeUtils::rad(float val)
{
    return ((float) M_PI) / 180.f * val;
}

Point ShapeUtils::findVector(Point start, Point end)
{
    return end - start;
}

Point ShapeUtils::scale(Point p, glm::vec3 v)
 {
    glm::mat4 mat = glm::scale(v);
    return Point((mat * p.toVec4()).xyz());
 }
