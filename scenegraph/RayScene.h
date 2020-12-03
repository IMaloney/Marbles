#ifndef RAYSCENE_H
#define RAYSCENE_H

#include "Scene.h"
#include "Canvas2D.h"
#include "Camera.h"

#include <vector>

//#define EPSILON

/**
 * @class RayScene
 *
 *  Students will implement this class as necessary in the Ray project.
 */

struct CS123ShapeIntersection {
   bool found;
   CS123FlatSceneNode node;
   float t;
   glm::vec4 point;
   glm::vec4 normal;
   glm::vec4 originalRay;
   std::vector<CS123ShapeIntersection> reflections;
};

class RayScene : public Scene {
public:
    RayScene(Scene &scene);
    virtual ~RayScene();

    const float epsilon = 0.00005f;
    const int recursionLimit = 1;

    bool m_antiAliasing = false;
    bool m_shadows = false;
    bool m_texturesOn = false;
    bool m_reflection = false;
    bool m_multithreading = false;
    bool m_usekdTree = false;
    bool m_pointLights = true;
    bool m_directionalLights = true;

    int getNumObjects() {
        return m_flattenedGraph.size();
    }

    void buildKdTree();

    glm::vec4 screenToFilm(float x, float y, float width, float height);
    glm::vec4 worldToObject(glm::mat4x4 transformation, glm::vec4 point);
    glm::vec4 filmToWorld(Camera *camera, glm::vec4 point);
    glm::vec4 cameraToWorld(Camera *camera, glm::vec4 point);

    void rayTrace(Canvas2D *canvas, int width, int height, Camera *camera, int r, int c);
    void rayTraceAA(Canvas2D *canvas, int width, int height, Camera *camera, int r, int c, int numSamples);

    glm::vec4 calculateIllumination(CS123ShapeIntersection intersect, int depth);

    CS123ShapeIntersection findShapeIntersect(glm::vec4 eye, glm::vec4 direction);
    CS123ShapeIntersection findShapeIntersectKDTree(glm::vec4 eye, glm::vec4 direction, glm::vec4 pixWorld);

    static float coneBodyImplicit(glm::vec4 eye, glm::vec4 direction);
    static float coneCapImplicit(glm::vec4 eye, glm::vec4 direction);
    static float cylinderBodyImplicit(glm::vec4 eye, glm::vec4 direction);
    static float cylinderCapImplicit(glm::vec4 eye, glm::vec4 direction);
    static float sphereImplicit(glm::vec4 eye, glm::vec4 direction);
    static float cubeImplicit(glm::vec4 eye, glm::vec4 direction, float epsilon);

    glm::vec4 getNormal(glm::vec4 point, PrimitiveType type);
    static glm::vec4 cubeNormal(glm::vec4 point, float epsilon);
    static glm::vec4 cylinderCapNormal(glm::vec4 point, float epsilon);
    static glm::vec4 cylinderBodyNormal(glm::vec4 point);
    static glm::vec4 coneBodyNormal(glm::vec4 point);

    glm::vec4 calculateReflectionVector(glm::vec4 normal, glm::vec4 pointToLight);

    // u, v, j, k, w and h, where j and k are the number of repetitions in the x and
    // y directions, respectively, w is the texture width, and h is the texture height
    glm::vec2 calculateTextureCoords(float u, float v, int j, int k, int w, int h);
    glm::vec2 getTextureCoords(CS123ShapeIntersection intersect, int w, int h);

};

#endif // RAYSCENE_H
