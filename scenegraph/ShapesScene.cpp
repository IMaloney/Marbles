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

#define STB_IMAGE_IMPLEMENTATION
#include "gl/stb_image.h"

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
    m_vecTrans(),
    m_textureID()


{
    initializeSceneMaterial();
    initializeSceneLight();
    loadPhongShader();
    loadWireframeShader();
    loadNormalsShader();
    loadNormalsArrowShader();
    loadGlassShader();
    loadMetalShader();

    this->makeMap();
    m_shape = std::make_unique<Box>(1.5f); //std::make_unique<Box>(1.5f);
    // params need to be a multiple of 4 --> 12 or 24 is the best choice
    m_modelMable = std::make_unique<Sphere>(24, 24, .5); //std::make_unique<WoodMarble>(settings.gravity, .5, settings.marbleWeight);//

    // testing
//    m_modelMable->printQuadInfo();

//    std::vector<std::string> faces = {
//        "/Users/wtauten/Desktop/Notes/Master's Fall Semester/Graphics/final/Marbles/textures/marble.jpg",
//        "/Users/wtauten/Desktop/Notes/Master's Fall Semester/Graphics/final/Marbles/textures/marble.jpg",
//        "/Users/wtauten/Desktop/Notes/Master's Fall Semester/Graphics/final/Marbles/textures/marble.jpg",
//        "/Users/wtauten/Desktop/Notes/Master's Fall Semester/Graphics/final/Marbles/textures/marble.jpg",
//        "/Users/wtauten/Desktop/Notes/Master's Fall Semester/Graphics/final/Marbles/textures/marble.jpg",
//        "/Users/wtauten/Desktop/Notes/Master's Fall Semester/Graphics/final/Marbles/textures/marble.jpg"
//    };

    std::vector<std::string> faces = {
        "../textures/marble.jpg",
        "../textures/marble.jpg",
        "../textures/marble.jpg",
        "../textures/marble.jpg",
        "../textures/marble.jpg",
        "../textures/marble.jpg"
    };

    m_textureID = loadCubemap(faces);

    MarbleData marble = MarbleData();
    marble.radius = .25f;
    marble.weight = 54;
    marble.gravity = -1 * 11.51;
    marble.centerPosition = glm::vec4(-0.5f, -1.25f, -0.5f, 1.0f);
    marble.currDirection =  glm::vec4(0.0f, -1.0f, 0.0f, 0.0f);
    marble.cumulativeTransformation = marble.centerPosition.xyz();
    marble.prevVelocity = glm::vec4(0.5f, 0.0, 0.5f, 0.0f);
    marble.velocity = glm::vec4(0.5f, 0.0, 0.5f, 0.0f);
    marble.scaleTransformation = glm::scale(glm::vec3(marble.radius/0.5f));
    marble.angle = glm::vec3(0.0f);
    marble.marbleType = MARBLE_GLASS;
    marble.quatAngle = 0.0f;
    marble.broken = false;

    m_marbles.push_back(marble);

    marble = MarbleData();
    marble.radius = .25f;
    marble.weight = 54;
    marble.gravity = -1 * 11.51;
    marble.centerPosition = glm::vec4(0.5f, -1.25f, 0.5f, 1.0f);
    marble.currDirection =  glm::vec4(0.0f, -1.0f, 0.0f, 0.0f);
    marble.cumulativeTransformation = marble.centerPosition.xyz();
    marble.prevVelocity = glm::vec4(-0.5f, 0.0, -0.5f, 0.0f);
    marble.velocity = glm::vec4(-0.5f, 0.0, -0.5f, 0.0f);
    marble.scaleTransformation = glm::scale(glm::vec3(marble.radius/0.5f));
    marble.angle = glm::vec3(0.0f);
    marble.marbleType = MARBLE_GLASS;
    marble.quatAngle = 0.0f;
    marble.broken = false;

    m_marbles.push_back(marble);


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

void ShapesScene::loadGlassShader() {
    std::string vertexSource = ResourceLoader::loadResourceFileToString(":/shaders/shaders/glass.vert");
    std::string fragmentSource = ResourceLoader::loadResourceFileToString(":/shaders/shaders/glass.frag");
    m_glassShader = std::make_unique<CS123Shader>(vertexSource, fragmentSource);
}

void ShapesScene::loadMetalShader() {
    std::string vertexSource = ResourceLoader::loadResourceFileToString(":/shaders/shaders/metal.vert");
    std::string fragmentSource = ResourceLoader::loadResourceFileToString(":/shaders/shaders/metal.frag");
    m_metalShader = std::make_unique<CS123Shader>(vertexSource, fragmentSource);
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

unsigned int ShapesScene::loadCubemap(std::vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
//        const char *tex = "/Users/wtauten/Desktop/Notes/Master's Fall Semester/Graphics/final/Marbles/textures/real_marble.png";
//        QImage img = QGLWidget::convertToGLFormat(QImage(tex));
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);

        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
//            std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}

void ShapesScene::renderPhongPass(SupportCanvas3D *context) {
    // THIS COULD BE SUS
    m_glassShader->bind();
    setMatrixUniforms(m_glassShader.get(), context);
    m_glassShader->setUniform("r0" , 0.8f);
    m_glassShader->setUniform("eta" , glm::vec3(0.79f, 0.8f, 0.81f));
    m_glassShader->unbind();

    m_metalShader->bind();
    setMatrixUniforms(m_metalShader.get(), context);
    m_metalShader->setUniform("lightPosition" , glm::vec4(10.0f, 10.0f, 10.0f, 0.0f));
    m_metalShader->setUniform("r0" , 0.7f);
    m_metalShader->setUniform("rough" , 0.55f);
    m_metalShader->unbind();

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

void ShapesScene::clearMarbles() {
    m_marbles.clear();
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

            // adding somewhere here
            checkMarbleCollisions();

            MarbleBoxIntersect xIntersect = checkBoxXCollision(m_marbles[i]);
            MarbleBoxIntersect yIntersect = checkBoxYCollision(m_marbles[i]);
            MarbleBoxIntersect zIntersect = checkBoxZCollision(m_marbles[i]);

            checkWallCollisions(i, xIntersect, zIntersect);

            if (yIntersect.intersect) {
//                std::cout << "1: " << m_marbles[i].velocity.y << std::endl;
                //translateMarble(i, glm::vec3(0.0f, -0.01f, 0.0f));
                float yVel = m_marbles[i].velocity.y;
                if (yIntersect.spherePoint.y < 0) {
                    m_marbles[i].prevVelocity = m_marbles[i].velocity;
                    m_marbles[i].velocity.y = 0.0f;
                    m_marbles[i].centerPosition.y = -1.5f + m_marbles[i].radius;
                    m_marbles[i].cumulativeTransformation.y = -1.5f + m_marbles[i].radius;
                }

                if (m_marbles[i].marbleType == MARBLE_RUBBER) {
                    m_marbles[i].velocity.y = -1.0f * (yVel / 2.0f);
                    if (m_marbles[i].velocity.y < 1) {
                        m_marbles[i].prevVelocity = m_marbles[i].velocity;
                        m_marbles[i].velocity.y = 0.0f;
                        m_marbles[i].centerPosition.y = -1.5f + m_marbles[i].radius;
                        m_marbles[i].cumulativeTransformation.y = -1.5f + m_marbles[i].radius;
                    }
                }

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
              // commented out print statement
//            std::cout << "pos " << i << ": "
//                      << m_marbles[i].centerPosition.x << ", "
//                      << m_marbles[i].centerPosition.y << ", "
//                      << m_marbles[i].centerPosition.z << std::endl;

            m_marbles[i].centerPosition = m_marbles[i].centerPosition + distance; // update position
            m_marbles[i].cumulativeTransformation = glm::vec3(m_marbles[i].centerPosition.xyz());

            glm::mat4x4 translation = glm::translate(m_marbles[i].cumulativeTransformation);

            m_phongShader->setUniform("m" , translation * rotMat * m_marbles[i].scaleTransformation);

            if (m_marbles[i].marbleType == MARBLE_METAL) {
                m_phongShader->unbind();
                m_metalShader->bind();

                glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID);
                m_metalShader->setUniform("m" , translation * rotMat * m_marbles[i].scaleTransformation);
                m_modelMable->draw();

                m_metalShader->unbind();
                m_phongShader->bind();
            } else if (m_marbles[i].marbleType == MARBLE_GLASS) {
                m_phongShader->unbind();
                m_glassShader->bind();

                glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID);
                m_glassShader->setUniform("m" , translation * rotMat * m_marbles[i].scaleTransformation);
                m_modelMable->draw();

                m_glassShader->unbind();
                m_phongShader->bind();
            } else {
                m_modelMable->draw();
            }
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
    marble.prevVelocity = glm::vec4(0.0f, marble.gravity * frameDuration, 0.0f, 0.0f);
    marble.velocity = glm::vec4(0.0f, marble.gravity * frameDuration, 0.0f, 0.0f);
    marble.scaleTransformation = glm::scale(glm::vec3(settings.marbleRadius/0.5f));
    marble.quatAngle = 0.0f;
    marble.broken = false;

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
    m_marbles[i].prevVelocity = m_marbles[i].velocity;
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
                std::cout << "dist: " << dist << std::endl;
                if (dist <= (m1Rad + m2Rad)) {
                    bool m1Shatter = (m_marbles[i].marbleType == MARBLE_GLASS) ? this->shouldShatter(m_marbles[j].velocity, m_marbles[j].prevVelocity, m_marbles[j].weight, m_marbles[i].radius, m_marbles[i].weight) : false;
                    bool m2Shatter = (m_marbles[j].marbleType == MARBLE_GLASS) ? this->shouldShatter(m_marbles[i].velocity, m_marbles[i].prevVelocity, m_marbles[i].weight, m_marbles[j].radius, m_marbles[j].weight) : false;
                    if (m1Shatter) {
                        //  remove data from
                        this->shatter(i);
                    }
//
                    if (m2Shatter) {
                        this->shatter(j);
                    }
                    std::cout << this->shouldShatter(m_marbles[i].velocity, m_marbles[i].prevVelocity, m_marbles[i].weight, m_marbles[j].radius, m_marbles[j].weight) << std::endl;
                    float overlap = ((m1Rad + m2Rad) - dist) / 2.0f + epsilon;

                    m_marbles[i].centerPosition += glm::normalize(-m_marbles[i].velocity)*overlap;
                    m_marbles[i].cumulativeTransformation = m_marbles[i].centerPosition.xyz();

                    m_marbles[j].centerPosition += glm::normalize(-m_marbles[j].velocity)*overlap;
                    m_marbles[j].cumulativeTransformation = m_marbles[j].centerPosition.xyz();

                    // Only checking half
                    bool noXVel = (m2.velocity.x > -epsilon) && (m2.velocity.x < epsilon);
                    bool noZVel = (m2.velocity.z > -epsilon) && (m2.velocity.z < epsilon);

                    bool m1Dropping = m1.velocity.y < 0.0f;
                    bool m2Dropping = m2.velocity.y < 0.0f;

                    // Case where one marble dropped directly on another marble
                    if (m1Dropping) { //noXVel && noZVel
                        float downwardVelocity = glm::length(m1.velocity);

                        float randF = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX));
                        float randF2 = 1.0f - randF;

                        m_marbles[i].velocity.y = -0.5f * m_marbles[i].velocity.y;

                        m_marbles[i].velocity.x = randF * downwardVelocity;
                        m_marbles[i].velocity.z = randF2 * downwardVelocity;

                        m_marbles[j].velocity.x = -randF2 * downwardVelocity;
                        m_marbles[j].velocity.z = -randF * downwardVelocity;


                    } else if (m2Dropping) {

                        float downwardVelocity = glm::length(m2.velocity);

                        float randF = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX));
                        float randF2 = 1.0f - randF;

                        m_marbles[j].velocity.y = -0.5f * m_marbles[j].velocity.y;

                        m_marbles[j].velocity.x = randF * downwardVelocity;
                        m_marbles[j].velocity.z = randF2 * downwardVelocity;

                        m_marbles[i].velocity.x = -randF2 * downwardVelocity;
                        m_marbles[i].velocity.z = -randF * downwardVelocity;

                    } else {
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

                        float deacceleration = 0.5f;

                        m_marbles[i].prevVelocity = m_marbles[i].velocity;
                        m_marbles[i].velocity = m1FinalVel * deacceleration;

                        m_marbles[j].prevVelocity = m_marbles[j].velocity;
                        m_marbles[j].velocity = m2FinalVel * deacceleration;

                        m_marbles[i].quatAngle = -m_marbles[i].quatAngle;
                        m_marbles[j].quatAngle = -m_marbles[j].quatAngle;
                    }
                }
            }
        }
    }
}

void ShapesScene::makeMap() {
    // box texture
    const char *tex = "../textures/marble.jpg";
////    const char *tex = "/Users/wtauten/Desktop/Notes/Master's Fall Semester/Graphics/final/Marbles/textures/marble.jpg";
    QImage img = QGLWidget::convertToGLFormat(QImage(tex));
    m_boxTexture = std::make_shared<CS123::GL::Texture2D>(img.bits(), img.width(), img.height());

    // wood texture
     tex =  "../textures/wood.jpg";
//    tex = "/Users/wtauten/Desktop/Notes/Master's Fall Semester/Graphics/final/Marbles/textures/wood.jpg";
    img = QGLWidget::convertToGLFormat(QImage(tex));
    std::shared_ptr<CS123::GL::Texture2D> texture = std::make_shared<CS123::GL::Texture2D>(img.bits(), img.width(), img.height());
    m_marbleTextureMap.insert(std::pair<int, std::shared_ptr<CS123::GL::Texture2D>>(static_cast<int>(MARBLE_WOOD), texture));

    // rubber texture
    tex = "../textures/rubber_texture.jpg";
//    tex = "/Users/wtauten/Desktop/Notes/Master's Fall Semester/Graphics/final/Marbles/textures/rubber_texture.jpg";
    img = QGLWidget::convertToGLFormat(QImage(tex));
    texture = std::make_shared<CS123::GL::Texture2D>(img.bits(), img.width(), img.height());
    m_marbleTextureMap.insert(std::pair<int, std::shared_ptr<CS123::GL::Texture2D>>(static_cast<int>(MARBLE_RUBBER), texture));

}

void ShapesScene::checkWallCollisions(int i, MarbleBoxIntersect x, MarbleBoxIntersect z) {
    // ball hit a corner
    if (x.intersect && z.intersect) {
        m_marbles[i].prevVelocity = m_marbles[i].velocity;
        m_marbles[i].velocity = -0.5f * m_marbles[i].velocity; // reverse direction with half the velocity
        m_marbles[i].quatAngle = -m_marbles[i].quatAngle;

    } else if (x.intersect) {
        if (x.spherePoint.x < 0) {

            glm::vec4 normal = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
            m_marbles[i].prevVelocity = m_marbles[i].velocity;
            m_marbles[i].velocity = calculateReflectionVector(normal, m_marbles[i].velocity);
            m_marbles[i].quatAngle = -m_marbles[i].quatAngle;

        } else {

            glm::vec4 normal = glm::vec4(-1.0f, 0.0f, 0.0f, 0.0f);
            m_marbles[i].prevVelocity = m_marbles[i].velocity;
            m_marbles[i].velocity = calculateReflectionVector(normal, m_marbles[i].velocity);
            m_marbles[i].quatAngle = -m_marbles[i].quatAngle;

        }

    } else if (z.intersect) {
        if (z.spherePoint.z < 0) {

            glm::vec4 normal = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);
            m_marbles[i].prevVelocity = m_marbles[i].velocity;
            m_marbles[i].velocity = calculateReflectionVector(normal, m_marbles[i].velocity);
            m_marbles[i].quatAngle = -m_marbles[i].quatAngle;

        } else {

            glm::vec4 normal = glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);
            m_marbles[i].prevVelocity = m_marbles[i].velocity;
            m_marbles[i].velocity = calculateReflectionVector(normal, m_marbles[i].velocity);
            m_marbles[i].quatAngle = -m_marbles[i].quatAngle;

        }
    }
}

glm::vec4 ShapesScene::calculateReflectionVector(glm::vec4 normal, glm::vec4 incoming) {
    glm::vec4 reflect = -1.0f * (2.0f * glm::dot(normal, incoming) * normal - incoming);
    return reflect;
}

void ShapesScene::shatter(int i) {
    m_marbles[i].broken = true;
    std::vector<GLfloat> *temp = m_modelMable->getVetexDataPTR();
    std::map<int, std::vector<std::pair<int, int>>>::iterator qtrIt;
    for (auto const& x : m_modelMable->getMap()) {
        auto m = x.second;
        int size = m.size();
        for (int i = 0; i < size; i++) {
            int start = std::get<0>(m[i]), end = std::get<1>(m[i])- 3;
            for (int j = start; j < end; j++) {
                (*temp)[j] +=  (*temp)[j + 3];
            }

        }
    }
}

inline bool ShapesScene::shouldShatter(const glm::vec4 &curVel, const glm::vec4 &prevVel,const int &colliderMass, const float &collideeRadius, const int &collideeMass){
    float force = this->getForce(curVel, prevVel, colliderMass),
          hlWeighted = this->hookesLaw(collideeRadius, force);
    std::cout << hlWeighted << std::endl;
    std::cout <<  collideeRadius * collideeMass << std::endl;
    return hlWeighted >= (collideeRadius * collideeMass);
}
inline float ShapesScene::area(const float &radius) {
    return M_PI * pow(radius, 2.0);
}

inline float ShapesScene::hookesLaw(const float &r, const float &f) {
    return (r* f)/(this->area(r) * youngMod);
}

inline float ShapesScene::getForce(const glm::vec4 &curVel, const glm::vec4 &prevVel, const int &mass) {
    return this->getAcceleration(curVel, prevVel) * static_cast<float>(mass);
}

// acceleration expressed as a scalar for simplicity
inline float ShapesScene::getAcceleration(const glm::vec4 &curVel, const glm::vec4 &prevVel) {
     return glm::length((curVel.xyz() - prevVel.xyz())/frameDuration);
}
