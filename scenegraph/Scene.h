#ifndef SCENE_H
#define SCENE_H

#include "CS123SceneData.h"
#include <map>
#include <string>
#include <QImage>
#include <QString>

class Camera;
class CS123ISceneParser;


/**
 * @class Scene
 *
 * @brief This is the base class for all scenes. Modify this class if you want to provide
 * common functionality to all your scenes.
 */
class Scene {
public:
    Scene();
    Scene(Scene &scene);
    virtual ~Scene();

    virtual void settingsChanged() {}

    static void parse(Scene *sceneToFill, CS123ISceneParser *parser);

protected:

    // Adds a primitive to the scene.
    virtual void addPrimitive(const CS123ScenePrimitive &scenePrimitive, const glm::mat4x4 &matrix);

    // Adds a light to the scene.
    virtual void addLight(const CS123SceneLightData &sceneLight);

    // Sets the global data for the scene.
    virtual void setGlobal(const CS123SceneGlobalData &global);

    void dfs(const CS123SceneNode &node, const glm::mat4x4 &matrix);

    glm::mat4x4 getTransformation(CS123SceneTransformation transformation);

    CS123SceneGlobalData m_globalData;
    std::vector<CS123SceneLightData> m_lightData;
    std::vector<CS123ScenePrimitive> m_primitives;
    std::vector<glm::mat4x4> m_transformations;
    std::vector<CS123FlatSceneNode> m_flattenedGraph;
    std::map<std::string, QImage> m_textures;
};

#endif // SCENE_H
