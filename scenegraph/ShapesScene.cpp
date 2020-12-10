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

    this->makeMap();
    m_shape = std::make_unique<Box>(1.5f); //std::make_unique<Box>(1.5f);
    m_modelMable = std::make_unique<Sphere>(10, 10, .5); //std::make_unique<WoodMarble>(settings.gravity, .5, settings.marbleWeight);//

    const char *marbleTexture = "/Users/wtauten/Desktop/Notes/Master's Fall Semester/Graphics/final/Marbles/textures/real_marble.png";
    const char *woodTexture = "/Users/wtauten/Desktop/Notes/Master's Fall Semester/Graphics/final/Marbles/textures/wood.jpg";
//    const char *marbleTexture = "../textures/real_marble.png";
//    const char *woodTexture = "../textures/wood.jpg";
//    m_boxTexture = QGLWidget::convertToGLFormat(QImage(marbleTexture));
//    m_woodMarbleTexture = QGLWidget::convertToGLFormat(QImage(woodTexture));



    MarbleData marble = MarbleData();
    marble.radius = .5f;
    marble.weight = 54;
    marble.gravity = -1 * 11.51;
    marble.centerPosition = glm::vec4(-0.5f, -1.25f, -0.5f, 1.0f);
    marble.currDirection =  glm::vec4(0.0f, -1.0f, 0.0f, 0.0f);
    marble.cumulativeTransformation = marble.centerPosition.xyz();
    marble.velocity = glm::vec4(0.5f, 0.0, 0.5f, 0.0f);
    marble.scaleTransformation = glm::scale(glm::vec3(marble.radius/0.5f));
    marble.angle = glm::vec3(0.0f);
    marble.marbleType = MARBLE_WOOD;
    marble.quatAngle = 0.0f;

    m_marbles.push_back(marble);

    marble = MarbleData();
    marble.radius = .5f;
    marble.weight = 54;
    marble.gravity = -1 * 11.51;
    marble.centerPosition = glm::vec4(0.5f, -1.25f, 0.5f, 1.0f);
    marble.currDirection =  glm::vec4(0.0f, -1.0f, 0.0f, 0.0f);
    marble.cumulativeTransformation = marble.centerPosition.xyz();
    marble.velocity = glm::vec4(-0.5f, 0.0, -0.5f, 0.0f);
    marble.scaleTransformation = glm::scale(glm::vec3(marble.radius/0.5f));
    marble.angle = glm::vec3(0.0f);
    marble.marbleType = MARBLE_WOOD;
    marble.quatAngle = 0.0f;

    m_marbles.push_back(marble);

//        const char *marbleTexture = "../textures/real_marble.png";
//        const char *woodTexture = "../textures/wood.jpg";
//        m_boxTexture = QGLWidget::convertToGLFormat(QImage(marbleTexture));
//        m_woodMarbleTexture = QGLWidget::convertToGLFormat(QImage(woodTexture));

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

void ShapesScene::renderGeometry() {

    CS123::GL::TextureParametersBuilder builder;
    builder.setFilter(CS123::GL::TextureParameters::FILTER_METHOD::LINEAR);
    builder.setWrap(CS123::GL::TextureParameters::WRAP_METHOD::REPEAT);
    CS123::GL::TextureParameters parameters = builder.build();


    if (m_shape) {

//        CS123::GL::Texture2D texture(m_boxTexture.bits(), m_boxTexture.width(), m_boxTexture.height());
        parameters.applyTo(*m_boxTexture);


        glm::vec2 uv = glm::vec2(1, 1);
        m_phongShader->setUniform("useTexture", 1);
        m_phongShader->setUniform("repeatUV", uv);
        m_phongShader->setTexture("tex", *m_boxTexture);

        m_phongShader->setUniform("m" , glm::mat4x4());
        m_shape->draw();
    }

    if (m_modelMable) {
        int size = m_marbles.size();
        std::map<int, std::shared_ptr<CS123::GL::Texture2D>>::iterator it;
        for (int i = 0; i < size; i++) {

            int t = m_marbles[i].marbleType;

            it = m_marbleTextureMap.find(t);

            if (it != m_marbleTextureMap.end()) {
                parameters.applyTo(*(it->second));
                glm::vec2 uv = glm::vec2(1, 1);
                m_phongShader->setUniform("useTexture", 1);
                m_phongShader->setUniform("repeatUV", uv);

                m_phongShader->setTexture("tex", *(it->second));
                checkError();
            }


            gravity(i);
            checkMarbleCollisions();

            MarbleBoxIntersect xIntersect = checkBoxXCollision(m_marbles[i]);
            MarbleBoxIntersect yIntersect = checkBoxYCollision(m_marbles[i]);
            MarbleBoxIntersect zIntersect = checkBoxZCollision(m_marbles[i]);

            checkWallCollisions(i, xIntersect, zIntersect);

            if (yIntersect.intersect) {
                //translateMarble(i, glm::vec3(0.0f, -0.01f, 0.0f));
                if (yIntersect.spherePoint.y < 0) {
                    m_marbles[i].velocity.y = 0.0f;
                    m_marbles[i].centerPosition.y = -1.5f + m_marbles[i].radius;
                    m_marbles[i].cumulativeTransformation.y = -1.5f + m_marbles[i].radius;
                }


                // IF RUBBER:
                //m_marbles[i].velocity.y = -1.0f * (m_marbles[i].velocity.y / 2.0f);
            }

            glm::vec4 distance = m_marbles[i].velocity * frameDuration;

            glm::mat4x4 rotMat = glm::mat4x4();

            bool ballOnFloor = m_marbles[i].centerPosition.y <= -1.5f + m_marbles[i].radius + epsilon;
            bool ballRolling = m_marbles[i].velocity.x != 0.0f || m_marbles[i].velocity.z;

            // Rotational physics
            if (ballOnFloor && ballRolling) {
                glm::vec4 floorNormal = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
                glm::vec4 ballDirectionNormal = glm::normalize(m_marbles[i].velocity);

                glm::vec3 rotationAxis = glm::normalize(glm::cross(floorNormal.xyz(), ballDirectionNormal.xyz()));

                float velocity = glm::length(m_marbles[i].velocity);

                float angle = velocity*frameDuration/m_marbles[i].radius; // try adding frameduration

                m_marbles[i].quatAngle += angle;

                glm::quat rotQuat = glm::angleAxis(m_marbles[i].quatAngle, rotationAxis);
                rotMat = glm::toMat4(rotQuat);
            }

            std::cout << "pos " << i << ": "
                      << m_marbles[i].centerPosition.x << ", "
                      << m_marbles[i].centerPosition.y << ", "
                      << m_marbles[i].centerPosition.z << std::endl;

            m_marbles[i].centerPosition = m_marbles[i].centerPosition + distance; // update position
            m_marbles[i].cumulativeTransformation = glm::vec3(m_marbles[i].centerPosition.xyz());

            glm::mat4x4 translation = glm::translate(m_marbles[i].cumulativeTransformation);

            m_phongShader->setUniform("m" , translation * rotMat * m_marbles[i].scaleTransformation);
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

    MarbleData marble = MarbleData();
    marble.radius = settings.marbleRadius;
    marble.weight = settings.marbleWeight;
    marble.gravity = -1 * settings.gravity;
    marble.marbleType = settings.marbleType;
    marble.centerPosition = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    marble.currDirection =  glm::vec4(0.0f, -1.0f, 0.0f, 0.0f);
    marble.cumulativeTransformation = glm::vec3(0.0f, 0.0f, 0.0f);
    marble.velocity = glm::vec4(0.0f, marble.gravity * frameDuration, 0.0f, 0.0f);
    marble.scaleTransformation = glm::scale(glm::vec3(settings.marbleRadius/0.5f));
    marble.quatAngle = 0.0f;

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


void ShapesScene::checkMarbleCollisions() {
    int size = (int) m_marbles.size();

    for (int i = 0; i < size; i++) {
        for (int j = i+1; j < size; j++) {
            MarbleData m1 = m_marbles[i];
            MarbleData m2 = m_marbles[j];

            glm::vec4 m1Pos = m_marbles[i].centerPosition;
            float m1Rad = m_marbles[i].radius;

            glm::vec4 m2Pos = m_marbles[j].centerPosition;
            float m2Rad = m_marbles[j].radius;

            // Bounding box calculations - MAY NEED TO ADD EPSILONS HERE!!!
            float m1XMax = m1Pos.x + m1Rad;
            float m1XMin = m1Pos.x - m1Rad;
            float m2XMax = m2Pos.x + m2Rad;
            float m2XMin = m2Pos.x - m2Rad;

            bool xOverlap = (m1XMax >= m2XMin && m1XMax <= m2XMax) || (m1XMin >= m2XMin && m1XMin <= m2XMax)
                    || (m2XMax >= m1XMin && m2XMax <= m1XMax) || (m2XMin >= m1XMin && m2XMin <= m1XMax);

            float m1YMax = m1Pos.y + m1Rad;
            float m1YMin = m1Pos.y - m1Rad;
            float m2YMax = m2Pos.y + m2Rad;
            float m2YMin = m2Pos.y - m2Rad;

            bool yOverlap = (m1YMax >= m2YMin && m1YMax <= m2YMax) || (m1YMin >= m2YMin && m1YMin <= m2YMax)
                    || (m2YMax >= m1YMin && m2YMax <= m1YMax) || (m2YMin >= m1YMin && m2YMin <= m1YMax);

            float m1ZMax = m1Pos.z + m1Rad;
            float m1ZMin = m1Pos.z - m1Rad;
            float m2ZMax = m2Pos.z + m2Rad;
            float m2ZMin = m2Pos.z - m2Rad;

            bool zOverlap = (m1ZMax >= m2ZMin && m1ZMax <= m2ZMax) || (m1ZMin >= m2ZMin && m1ZMin <= m2ZMax)
                    || (m2ZMax >= m1ZMin && m2ZMax <= m1ZMax) || (m2ZMin >= m1ZMin && m2ZMin <= m1ZMax);

            if (xOverlap && yOverlap && zOverlap) {
                float dist = sqrt(pow(m1Pos.x - m2Pos.x, 2) + pow(m1Pos.y - m2Pos.y, 2) + pow(m1Pos.z - m2Pos.z, 2));

                if (dist <= (m1Rad + m2Rad)) {
                    std::cout << "Overlap found!" << std::endl;
                    // CAN DO DISTANCE CHECK HERE IF COLLISIONS ARE TOO LIBERAL
                    glm::vec4 basis = glm::normalize(m1Pos - m2Pos);
                    glm::vec4 m1Vel = m1.velocity;
                    float x1 = glm::dot(basis, m1Vel);
                    glm::vec4 m1VelX = basis * x1;
                    glm::vec4 m1VelZ = m1Vel - m1VelX;
                    float m1Weight = m1.weight;

                    basis = -1.0f * basis;
                    glm::vec4 m2Vel = m2.velocity;
                    float x2 = glm::dot(basis, m2Vel);
                    glm::vec4 m2VelX = basis * x2;
                    glm::vec4 m2VelZ = m2Vel - m2VelX;
                    float m2Weight = m2.weight;

                    glm::vec4 m1FinalVel
                            = m1VelX * (m1Weight - m2Weight) / (m1Weight + m2Weight)
                            + m2VelX * (2.0f * m2Weight) / (m1Weight + m2Weight) + m1VelZ;
                    glm::vec4 m2FinalVel
                            = m1VelX * (2.0f * m1Weight) / (m1Weight + m2Weight)
                            + m2VelX * (m2Weight - m1Weight) / (m1Weight + m2Weight) + m2VelZ;

                    m_marbles[i].velocity = m1FinalVel;
                    m_marbles[j].velocity = m2FinalVel;
                    m_marbles[i].quatAngle = -m_marbles[i].quatAngle;
                    m_marbles[j].quatAngle = -m_marbles[j].quatAngle;
                }
            }
        }
    }
}

void ShapesScene::makeMap() {
    // box texture
//    const char *tex = "../textures/real_marble.png";
    const char *tex = "/Users/wtauten/Desktop/Notes/Master's Fall Semester/Graphics/final/Marbles/textures/real_marble.png";
    QImage img = QGLWidget::convertToGLFormat(QImage(tex));
    m_boxTexture = std::make_shared<CS123::GL::Texture2D>(img.bits(), img.width(), img.height());

    // wood texture
//     tex =  "../textures/wood.jpg";
    tex = "/Users/wtauten/Desktop/Notes/Master's Fall Semester/Graphics/final/Marbles/textures/wood.jpg";
    img = QGLWidget::convertToGLFormat(QImage(tex));
    std::shared_ptr<CS123::GL::Texture2D> texture = std::make_shared<CS123::GL::Texture2D>(img.bits(), img.width(), img.height());
    m_marbleTextureMap.insert(std::pair<int, std::shared_ptr<CS123::GL::Texture2D>>(static_cast<int>(MARBLE_WOOD), texture));

    // rubber texture
//    tex = "../textures/rubber_texture.jpg";
    tex = "/Users/wtauten/Desktop/Notes/Master's Fall Semester/Graphics/final/Marbles/textures/real_marble.png";
    img = QGLWidget::convertToGLFormat(QImage(tex));
    texture = std::make_shared<CS123::GL::Texture2D>(img.bits(), img.width(), img.height());
    m_marbleTextureMap.insert(std::pair<int, std::shared_ptr<CS123::GL::Texture2D>>(static_cast<int>(MARBLE_RUBBER), texture));

}

void ShapesScene::checkWallCollisions(int i, MarbleBoxIntersect x, MarbleBoxIntersect z) {
    // ball hit a corner
    if (x.intersect && z.intersect) {

        m_marbles[i].velocity = -0.5f * m_marbles[i].velocity; // reverse direction with half the velocity
        m_marbles[i].quatAngle = -m_marbles[i].quatAngle;

    } else if (x.intersect) {
        if (x.spherePoint.x < 0) {

            glm::vec4 normal = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
            m_marbles[i].velocity = calculateReflectionVector(normal, m_marbles[i].velocity);
            m_marbles[i].quatAngle = -m_marbles[i].quatAngle;

        } else {

            glm::vec4 normal = glm::vec4(-1.0f, 0.0f, 0.0f, 0.0f);
            m_marbles[i].velocity = calculateReflectionVector(normal, m_marbles[i].velocity);
            m_marbles[i].quatAngle = -m_marbles[i].quatAngle;

        }

    } else if (z.intersect) {
        if (z.spherePoint.z < 0) {

            glm::vec4 normal = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);
            m_marbles[i].velocity = calculateReflectionVector(normal, m_marbles[i].velocity);
            m_marbles[i].quatAngle = -m_marbles[i].quatAngle;

        } else {

            glm::vec4 normal = glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);
            m_marbles[i].velocity = calculateReflectionVector(normal, m_marbles[i].velocity);
            m_marbles[i].quatAngle = -m_marbles[i].quatAngle;

        }
    }
}

glm::vec4 ShapesScene::calculateReflectionVector(glm::vec4 normal, glm::vec4 incoming) {
    glm::vec4 reflect = -1.0f * (2.0f * glm::dot(normal, incoming) * normal - incoming);
    return reflect;
}
