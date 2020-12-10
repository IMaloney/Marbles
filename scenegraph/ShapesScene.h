#ifndef SHAPESSCENE_H
#define SHAPESSCENE_H

#include "OpenGLScene.h"

#include <memory>

#include <GL/glew.h>

#include "gl/datatype/FBO.h"
#include "Settings.h"
#include <QTimer>

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>


#include "shapes/Box.h"
#include "marble/Marble.h"
#include "marble/MetalMarble.h"
#include "marble/WoodMarble.h"

#include "gl/textures/Texture2D.h"
#include "gl/textures/TextureParameters.h"
#include "gl/textures/TextureParametersBuilder.h"

static constexpr float youngMod = 70.f;
static constexpr float epsilon = 0.00005f;
static constexpr float frameDuration = 1.0f / 24.0f;

namespace CS123 { namespace GL {

    class Shader;
    class CS123Shader;
    class FullScreenQuad;

}}

class Shape;

/**
 *
 * @class ShapesScene
 *
 * A scene that is used to render a single shape.
 *
 * This scene has no notion of the scene graph, so it will not be useful to you in
 * assignments requiring the display of multiple shapes. Luckily, the first time you
 * will need that kind of functionality is in the Sceneview assignment... and we've
 * left that task up to you in the SceneviewScene class.
 *
 * By default, the ShapesScene displays only a single triangle. You'll need to do
 * a little work here to render your shapes. You could render the shapes directly
 * in this class, or you could pass the work on to one or more subclasses. Think
 * carefully about your design here - you'll be reusing your shapes multiple times
 * during this course!
 */
class ShapesScene : public OpenGLScene {
public:
    ShapesScene(int width, int height);
    virtual ~ShapesScene();

    virtual void render(SupportCanvas3D *context) override;
    virtual void settingsChanged() override;

    void dropMarble(SupportCanvas3D *context);


protected:
    // Set the light uniforms for the lights in the scene. (The view matrix is used so that the
    // light can follows the camera.)
    virtual void setLights(const glm::mat4 viewMatrix);

    // Render geometry for Shapes and Sceneview.
    virtual void renderGeometry();

private:
    // Storage for private copies of the scene's light and material data. Note that these don't
    // need to be freed because they are VALUE types (not pointers) and the memory for them is
    // freed when the class itself is freed.
    std::unique_ptr<CS123::GL::CS123Shader> m_phongShader;
    std::unique_ptr<CS123::GL::CS123Shader> m_glassShader;
    std::unique_ptr<CS123::GL::CS123Shader> m_metalShader;
    std::unique_ptr<CS123::GL::Shader> m_wireframeShader;
    std::unique_ptr<CS123::GL::Shader> m_normalsShader;
    std::unique_ptr<CS123::GL::Shader> m_normalsArrowShader;
    std::unique_ptr<CS123::GL::Shader> m_fsqShader;
    CS123SceneLightData  m_light;
    CS123SceneMaterial   m_material;

    std::unique_ptr<CS123::GL::Shader> m_boxShader;

    void makeMap();



    glm::vec4 m_lightDirection = glm::normalize(glm::vec4(1.f, -1.f, -1.f, 0.f));

    //    bool useSceneviewScene;
    //    int shapeType;              // Selected shape type
    //    int shapeParameter1;
    //    int shapeParameter2;
    //    float shapeParameter3;
    //    bool useLighting;           // Enable default lighting
    //    bool drawWireframe;         // Draw wireframe only
    //    bool drawNormals;

    // essentially an OpenGLShape from lab 1
    std::unique_ptr<Box> m_shape;
    std::unique_ptr<Sphere> m_modelMable;
    std::vector<MarbleData> m_marbles;

    std::map<int, std::shared_ptr<CS123::GL::Texture2D>> m_marbleTextureMap;

    int m_nextMarble;

    int m_width;
    int m_height;

    std::shared_ptr<CS123::GL::Texture2D> m_boxTexture;
//    QImage m_woodMarbleTexture;

    float m_yMove;
    glm::mat4x4 m_marbleTrans;
    glm::vec3 m_vecTrans;

    /** Incremented on every call to paintGL. */
    int m_increment;

    void clearLights();
    void loadPhongShader();
    void loadWireframeShader();
    void loadNormalsShader();
    void loadNormalsArrowShader();
    void loadGlassShader();
    void loadMetalShader();
    void renderPhongPass(SupportCanvas3D *context);
    void renderGeometryAsFilledPolygons();
    void renderWireframePass(SupportCanvas3D *context);
    void renderGeometryAsWireframe();
    void renderNormalsPass(SupportCanvas3D *context);
    void initializeSceneMaterial();
    void initializeSceneLight();
    void setPhongSceneUniforms();
    void setMatrixUniforms(CS123::GL::Shader *shader, SupportCanvas3D *context);
    void renderFilledPolygons();
    void renderNormals();
    void renderWireframe();
    void setSceneUniforms(SupportCanvas3D *context);

    void setActiveMarble();

    void translateMarble(int i, glm::vec3 step);

    void gravity(int i);

    MarbleBoxIntersect checkBoxXCollision(MarbleData marble);
    MarbleBoxIntersect checkBoxYCollision(MarbleData marble);
    MarbleBoxIntersect checkBoxZCollision(MarbleData marble);

    void checkMarbleCollisions();

    void checkWallCollisions(int i, MarbleBoxIntersect x, MarbleBoxIntersect z);


    glm::vec4 calculateReflectionVector(glm::vec4 normal, glm::vec4 incoming);

    // glass shattering stuff
    inline bool shouldShatter(const glm::vec4 &curVel, const glm::vec4 &prevVel,const int &colliderMass, const float &collideeRadius, const int &collideeMass);
    inline float area(const float &radius);
    inline float hookesLaw(const float &r, const float &f);
    inline float getForce(const glm::vec4 &curVel, const glm::vec4 &prevVel, const int &mass);
    inline float getAcceleration(const glm::vec4 &curVel, const glm::vec4 &prevVel);

};

#endif // SHAPESSCENE_H
