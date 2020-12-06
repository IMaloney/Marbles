#include "SceneviewScene.h"
#include "GL/glew.h"
#include <QGLWidget>
#include "Camera.h"

#include "Settings.h"
#include "SupportCanvas3D.h"
#include "ResourceLoader.h"
#include "gl/shaders/CS123Shader.h"
#include "CS123SceneData.h"

#include <iostream>

using namespace CS123::GL;


SceneviewScene::SceneviewScene()
{
    // TODO: [SCENEVIEW] Set up anything you need for your Sceneview scene here...
    loadPhongShader();
    loadWireframeShader();
    loadNormalsShader();
    loadNormalsArrowShader();
}

SceneviewScene::~SceneviewScene()
{
}

void SceneviewScene::loadPhongShader() {
    std::string vertexSource = ResourceLoader::loadResourceFileToString(":/shaders/default.vert");
    std::string fragmentSource = ResourceLoader::loadResourceFileToString(":/shaders/default.frag");
    m_phongShader = std::make_unique<CS123Shader>(vertexSource, fragmentSource);
}

void SceneviewScene::loadWireframeShader() {
    std::string vertexSource = ResourceLoader::loadResourceFileToString(":/shaders/wireframe.vert");
    std::string fragmentSource = ResourceLoader::loadResourceFileToString(":/shaders/wireframe.frag");
    m_wireframeShader = std::make_unique<Shader>(vertexSource, fragmentSource);
}

void SceneviewScene::loadNormalsShader() {
    std::string vertexSource = ResourceLoader::loadResourceFileToString(":/shaders/normals.vert");
    std::string geometrySource = ResourceLoader::loadResourceFileToString(":/shaders/normals.gsh");
    std::string fragmentSource = ResourceLoader::loadResourceFileToString(":/shaders/normals.frag");
    m_normalsShader = std::make_unique<Shader>(vertexSource, geometrySource, fragmentSource);
}

void SceneviewScene::loadNormalsArrowShader() {
    std::string vertexSource = ResourceLoader::loadResourceFileToString(":/shaders/normalsArrow.vert");
    std::string geometrySource = ResourceLoader::loadResourceFileToString(":/shaders/normalsArrow.gsh");
    std::string fragmentSource = ResourceLoader::loadResourceFileToString(":/shaders/normalsArrow.frag");
    m_normalsArrowShader = std::make_unique<Shader>(vertexSource, geometrySource, fragmentSource);
}

void SceneviewScene::render(SupportCanvas3D *context) {
    setClearColor();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_phongShader->bind();
    setSceneUniforms(context);
    setLights();
    setLevelOfDetail();
    renderGeometry();
    glBindTexture(GL_TEXTURE_2D, 0);
    m_phongShader->unbind();

}

void SceneviewScene::setSceneUniforms(SupportCanvas3D *context) {
    Camera *camera = context->getCamera();
    m_phongShader->setUniform("useLighting", settings.useLighting);
    m_phongShader->setUniform("useArrowOffsets", false);
    m_phongShader->setUniform("p" , camera->getProjectionMatrix());
    m_phongShader->setUniform("v", camera->getViewMatrix());
}

void SceneviewScene::setMatrixUniforms(Shader *shader, SupportCanvas3D *context) {
    shader->setUniform("p", context->getCamera()->getProjectionMatrix());
    shader->setUniform("v", context->getCamera()->getViewMatrix());
}

void SceneviewScene::setLights()
{
    for (int i = 0; i < (int) m_lightData.size(); i++) {
        m_phongShader->setLight(m_lightData[i]);
    }
}

void SceneviewScene::setLevelOfDetail() {
    int lodFactor = (int) std::floor(m_flattenedGraph.size() / 100) + 1;

    int param1 = std::max((int) floor(20/lodFactor), 3);
    int param2 = std::max((int) floor(20/lodFactor), 3);
    float param3 = 20.0f;

//    if (lodFactor > 0) {
//        param1 = std::max((int) floor(20/lodFactor), 3);
//        param2 = std::max((int) floor(20/lodFactor), 3);
//    }

    m_shape = std::make_shared<Shape>();
    m_cone = std::make_shared<Cone>(param1, param2);
    m_cube = std::make_shared<Cube>(param1, param2);
    m_cylinder = std::make_shared<Cylinder>(param1, param2);
    m_sphere = std::make_shared<Sphere>(param1, param2, 0.5f);
//    m_torus = std::make_shared<Torus>(param1, param2, param3);
}

void SceneviewScene::getPrimative(CS123ScenePrimitive primitive) {
    switch (primitive.type) {
        case PrimitiveType::PRIMITIVE_CUBE:
            m_shape = m_cube;
            break;
        case PrimitiveType::PRIMITIVE_CONE:
            m_shape = m_cone;
            break;
        case PrimitiveType::PRIMITIVE_CYLINDER:
            m_shape = m_cylinder;
            break;
        case PrimitiveType::PRIMITIVE_TORUS:
//            m_shape = m_torus;
            break;
        case PrimitiveType::PRIMITIVE_SPHERE:
            m_shape = m_sphere;
            break;
        case PrimitiveType::PRIMITIVE_MESH:
            std::cerr << "Mesh not yet implemented" << std::endl;
            break;
        default:
            std::cerr << "Error, no primitive type detected" << std::endl;
            break;
    }
}

void SceneviewScene::renderGeometry() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    for (int i = 0; i < (int) m_flattenedGraph.size(); i++) {
        CS123FlatSceneNode node = m_flattenedGraph[i];
        CS123ScenePrimitive prim = node.primitive;
        glm::mat4x4 trans = node.transformation;

        // Sets m_shape to be our current primitive type
        getPrimative(prim);

        // Apply material
        // Multiply ambient and diffuse by global coefficients
        prim.material.cAmbient *= m_globalData.ka;
        prim.material.cDiffuse *= m_globalData.kd;
        m_phongShader->applyMaterial(prim.material);

//        // Add texture
//        QImage image = m_textures[node.texFilename];
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits());

        // Set model transformation matrix to our transformation matrix
        m_phongShader->setUniform("m" , trans);

        m_shape->draw();
    }
}

void SceneviewScene::settingsChanged() {
    // TODO: [SCENEVIEW] Fill this in if applicable.
}

