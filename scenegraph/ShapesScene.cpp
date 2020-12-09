#include "ShapesScene.h"
#include "Camera.h"
#include "shapes/Shape.h"
#include <SupportCanvas3D.h>
#include <QFileDialog>

#include "gl/shaders/ShaderAttribLocations.h"

#include <sstream>
#include <iostream>
#include <cstdio>
#include <iostream>
#include <fstream>

#include "shapes/Cube.h"
#include "shapes/Cone.h"
#include "shapes/Cylinder.h"
#include "shapes/Sphere.h"


using namespace CS123::GL;
#include "gl/shaders/CS123Shader.h"
#include "gl/shaders/Shader.h"

#include "gl/GLDebug.h"

#include "ResourceLoader.h"

ShapesScene::ShapesScene(int width, int height) :
    m_shape(nullptr),
    m_modelMable(nullptr),
    m_marbles(),
    m_width(width),
    m_height(height),
    m_yMove(0.0f),
    m_marbleTrans(),
    m_vecTrans()


{

    initializeSceneMaterial();
    initializeSceneLight();
    loadPhongShader();
    loadWireframeShader();
    loadNormalsShader();
    loadNormalsArrowShader();

    m_shape = std::make_unique<Box>(1.5f); //std::make_unique<Box>(1.5f);
    m_modelMable = std::make_unique<Sphere>(10, 10, .25); //std::make_unique<WoodMarble>(settings.gravity, .5, settings.marbleWeight);//

    QString qstring = QString("/Users/wtauten/Desktop/Notes/Master's Fall Semester/Graphics/final/Marbles/textures/real_marble.png");
    m_boxTexture = QGLWidget::convertToGLFormat(QImage(qstring));
    qstring = QString("/Users/wtauten/Desktop/Notes/Master's Fall Semester/Graphics/final/Marbles/textures/wood.jpg");
    m_woodMarbleTexture = QGLWidget::convertToGLFormat(QImage(qstring));
}

ShapesScene::~ShapesScene()
{
    // Pro-tip: If you use smart pointers properly, this destructor should be empty
}

void ShapesScene::initializeSceneMaterial() {
    // Use a shiny orange material
    m_material.clear();
    m_material.cAmbient.r = 0.2f;
    m_material.cAmbient.g = 0.1f;
    m_material.cDiffuse.r = 1.0f;
    m_material.cDiffuse.g = 0.5f;
    m_material.cSpecular.r = m_material.cSpecular.g = m_material.cSpecular.b = 1;
    m_material.shininess = 64;
}

void ShapesScene::initializeSceneLight() {
    // Use a white directional light from the upper left corner
    memset(&m_light, 0, sizeof(m_light));
    m_light.type = LightType::LIGHT_DIRECTIONAL;
    m_light.dir = m_lightDirection;
    m_light.color.r = m_light.color.g = m_light.color.b = 1;
    m_light.id = 0;
}

void ShapesScene::loadPhongShader() {
    std::string vertexSource = ResourceLoader::loadResourceFileToString(":/shaders/default.vert");
    std::string fragmentSource = ResourceLoader::loadResourceFileToString(":/shaders/default.frag");
    m_phongShader = std::make_unique<CS123Shader>(vertexSource, fragmentSource);
}

void ShapesScene::loadWireframeShader() {
    std::string vertexSource = ResourceLoader::loadResourceFileToString(":/shaders/wireframe.vert");
    std::string fragmentSource = ResourceLoader::loadResourceFileToString(":/shaders/wireframe.frag");
    m_wireframeShader = std::make_unique<Shader>(vertexSource, fragmentSource);
}

void ShapesScene::loadNormalsShader() {
    std::string vertexSource = ResourceLoader::loadResourceFileToString(":/shaders/normals.vert");
    std::string geometrySource = ResourceLoader::loadResourceFileToString(":/shaders/normals.gsh");
    std::string fragmentSource = ResourceLoader::loadResourceFileToString(":/shaders/normals.frag");
    m_normalsShader = std::make_unique<Shader>(vertexSource, geometrySource, fragmentSource);
}

void ShapesScene::loadNormalsArrowShader() {
    std::string vertexSource = ResourceLoader::loadResourceFileToString(":/shaders/normalsArrow.vert");
    std::string geometrySource = ResourceLoader::loadResourceFileToString(":/shaders/normalsArrow.gsh");
    std::string fragmentSource = ResourceLoader::loadResourceFileToString(":/shaders/normalsArrow.frag");
    m_normalsArrowShader = std::make_unique<Shader>(vertexSource, geometrySource, fragmentSource);
}

void ShapesScene::render(SupportCanvas3D *context) {
    // Clear the screen in preparation for the next frame. (Use a gray background instead of a
    // black one for drawing wireframe or normals so they will show up against the background.)
    setClearColor();

    renderPhongPass(context);


//    if (settings.drawWireframe) {
//        renderWireframePass(context);
//    }

//    if (settings.drawNormals) {
//        renderNormalsPass(context);
//    }
}

void ShapesScene::renderPhongPass(SupportCanvas3D *context) {
    m_phongShader->bind();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    clearLights();
    setLights(context->getCamera()->getViewMatrix());
    setPhongSceneUniforms();
    setMatrixUniforms(m_phongShader.get(), context);
    renderGeometryAsFilledPolygons();

    m_phongShader->unbind();
}

void ShapesScene::setPhongSceneUniforms() {
    m_phongShader->setUniform("useLighting", true); // true used to be settings.useLighting
    m_phongShader->setUniform("useArrowOffsets", false);
    m_phongShader->applyMaterial(m_material);
}

void ShapesScene::setMatrixUniforms(Shader *shader, SupportCanvas3D *context) {
    shader->setUniform("p", context->getCamera()->getProjectionMatrix());
    shader->setUniform("v", context->getCamera()->getViewMatrix());
    shader->setUniform("m", glm::mat4(1.0f));
}

void ShapesScene::renderGeometryAsFilledPolygons() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    renderGeometry();
}

void ShapesScene::renderWireframePass(SupportCanvas3D *context) {
    m_wireframeShader->bind();
    setMatrixUniforms(m_wireframeShader.get(), context);
    renderGeometryAsWireframe();
    m_wireframeShader->unbind();
}

void ShapesScene::renderGeometryAsWireframe() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    renderGeometry();
}

void ShapesScene::renderNormalsPass (SupportCanvas3D *context) {
    // Render the lines.
    m_normalsShader->bind();
    setMatrixUniforms(m_normalsShader.get(), context);
    renderGeometryAsWireframe();
    m_normalsShader->unbind();

    // Render the arrows.
    m_normalsArrowShader->bind();
    setMatrixUniforms(m_normalsArrowShader.get(), context);
    renderGeometryAsFilledPolygons();
    m_normalsArrowShader->unbind();
}


void ShapesScene::loadBoxShader() {
    // TODO
//    std::string vertexSource = ResourceLoader::loadResourceFileToString("../shaders/box/box.vert");
//    std::string fragmentSource = ResourceLoader::loadResourceFileToString("../shaders/box/box.frag");
    std::string vertexSource = ResourceLoader::loadResourceFileToString("/Users/wtauten/Desktop/Notes/Master's Fall Semester/Graphics/final/Marbles/shaders/box/box.vert");
    std::string fragmentSource = ResourceLoader::loadResourceFileToString("/Users/wtauten/Desktop/Notes/Master's Fall Semester/Graphics/final/Marbles/shaders/box/box.frag");
//    /Users/wtauten/Desktop/Notes/Master's Fall Semester/Graphics/final/Marbles/shaders/box
    m_boxShader = std::make_unique<CS123::GL::Shader>(vertexSource, fragmentSource);
}


void ShapesScene::renderGeometry() {

    CS123::GL::TextureParametersBuilder builder;
    builder.setFilter(CS123::GL::TextureParameters::FILTER_METHOD::LINEAR);
    builder.setWrap(CS123::GL::TextureParameters::WRAP_METHOD::REPEAT);
    CS123::GL::TextureParameters parameters = builder.build();


    if (m_shape) {

        CS123::GL::Texture2D texture(m_boxTexture.bits(), m_boxTexture.width(), m_boxTexture.height());
        parameters.applyTo(texture);


        glm::vec2 uv = glm::vec2(1, 1);
        m_phongShader->setUniform("useTexture", 1);
        m_phongShader->setUniform("repeatUV", uv);
        m_phongShader->setTexture("tex",
                                  texture);

        m_phongShader->setUniform("m" , glm::mat4x4());
        m_shape->draw();
    }

    if (m_modelMable) {

        for (int i = 0; i < (int) m_marbles.size(); i++) {

            CS123::GL::Texture2D texture(m_woodMarbleTexture.bits(), m_woodMarbleTexture.width(), m_woodMarbleTexture.height());
            parameters.applyTo(texture);


            glm::vec2 uv = glm::vec2(1, 1);
            m_phongShader->setUniform("useTexture", 1);
            m_phongShader->setUniform("repeatUV", uv);

            m_phongShader->setTexture("tex",
                                      texture);

            MarbleBoxIntersect xIntersect = checkBoxXCollision(m_marbles[i]);
            MarbleBoxIntersect yIntersect = checkBoxYCollision(m_marbles[i]);
            MarbleBoxIntersect zIntersect = checkBoxZCollision(m_marbles[i]);

            if (yIntersect.intersect) {
                //translateMarble(i, glm::vec3(0.0f, -0.01f, 0.0f));
                m_marbles[i].velocity.y = -1.0f * (m_marbles[i].velocity.y / 2.0f);
            }

            gravity(i);

            glm::mat4x4 translation = glm::translate(m_marbles[i].cumulativeTransformation);

            m_phongShader->setUniform("m" , translation);
            m_modelMable->draw();
        }
    }
}

void ShapesScene::clearLights() {
    for (int i = 0; i < MAX_NUM_LIGHTS; i++) {
        std::ostringstream os;
        os << i;
        std::string indexString = "[" + os.str() + "]"; // e.g. [0], [1], etc.
        m_phongShader->setUniform("lightColors" + indexString, glm::vec3(0.0f, 0.0f, 0.0f));
    }
}

void ShapesScene::setLights(const glm::mat4 viewMatrix) {
    // YOU DON'T NEED TO TOUCH THIS METHOD, unless you want to do fancy lighting...

    m_light.dir = glm::inverse(viewMatrix) * m_lightDirection;

    clearLights();
    m_phongShader->setLight(m_light);
}

void ShapesScene::settingsChanged() {

}

void ShapesScene::dropMarble(SupportCanvas3D *context) {
    float radius = settings.marbleRadius; // 100.0f;

    MarbleData marble = MarbleData();
    marble.radius = radius;
    marble.weight = settings.marbleWeight;
    marble.gravity = -1 * settings.gravity;
    marble.marbleType = settings.marbleType;
    marble.centerPosition = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    marble.currDirection =  glm::vec4(0.0f, -1.0f, 0.0f, 0.0f);
    marble.cumulativeTransformation = glm::vec3(0.0f, 0.0f, 0.0f);
    marble.velocity = glm::vec4(0.0f, marble.gravity * frameDuration, 0.0f, 0.0f);

    m_marbles.push_back(marble);

}

MarbleBoxIntersect ShapesScene::checkBoxXCollision(MarbleData marble) {
    MarbleBoxIntersect intersect = MarbleBoxIntersect();
    intersect.intersect = false;

    glm::vec4 center = marble.centerPosition;

    // Intersects -x face of box
    if ((-1.5f + epsilon) > (center.x - marble.radius)) {
        intersect.intersect = true;
        intersect.spherePoint = glm::vec4(center.x - marble.radius, center.y, center.z, 1.0f);

    // Intersects +x face of box
    } else if ((1.5f - epsilon) < (center.x + marble.radius)) {
        intersect.intersect = true;
        intersect.spherePoint = glm::vec4(center.x + marble.radius, center.y, center.z, 1.0f);
    }

    return intersect;
}

MarbleBoxIntersect ShapesScene::checkBoxYCollision(MarbleData marble) {
    MarbleBoxIntersect intersect = MarbleBoxIntersect();
    intersect.intersect = false;

    glm::vec4 center = marble.centerPosition;

    // Intersects -y face of box
    if ((-1.5f + epsilon) > (center.y - marble.radius)) {
        intersect.intersect = true;
        intersect.spherePoint = glm::vec4(center.x, center.y - marble.radius, center.z, 1.0f);

    // Intersects +y face of box
    } else if ((1.5f - epsilon) < (center.y + marble.radius)) {
        intersect.intersect = true;
        intersect.spherePoint = glm::vec4(center.x, center.y + marble.radius, center.z, 1.0f);
    }

    return intersect;
}

MarbleBoxIntersect ShapesScene::checkBoxZCollision(MarbleData marble) {
    MarbleBoxIntersect intersect = MarbleBoxIntersect();
    intersect.intersect = false;

    glm::vec4 center = marble.centerPosition;

    // Intersects -z face of box
    if ((-1.5f + epsilon) > (center.z - marble.radius)) {
        intersect.intersect = true;
        intersect.spherePoint = glm::vec4(center.x, center.y, center.z - marble.radius, 1.0f);

    // Intersects +z face of box
    } else if ((1.5f - epsilon) < (center.z + marble.radius)) {
        intersect.intersect = true;
        intersect.spherePoint = glm::vec4(center.x, center.y, center.z + marble.radius, 1.0f);
    }

    return intersect;
}

void ShapesScene::translateMarble(int i, glm::vec3 step) {
    m_marbles[i].cumulativeTransformation += step;
    m_marbles[i].centerPosition += glm::vec4(step, 1.0f);
}

void ShapesScene::gravity(int i) {
    m_marbles[i].centerPosition.y = m_marbles[i].centerPosition.y + (m_marbles[i].velocity.y * frameDuration); // update position
    m_marbles[i].cumulativeTransformation.y = m_marbles[i].cumulativeTransformation.y + (m_marbles[i].velocity.y * frameDuration); // update position

    m_marbles[i].velocity.y = m_marbles[i].velocity.y + (m_marbles[i].gravity * frameDuration); // update velocity
}
