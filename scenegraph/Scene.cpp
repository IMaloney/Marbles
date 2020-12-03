#include "Scene.h"
#include "Camera.h"
#include "CS123ISceneParser.h"

#include "glm/gtx/transform.hpp"

#include <iostream>


Scene::Scene()
{
}

Scene::Scene(Scene &scene)
{
    // We need to set the global constants to one when we duplicate a scene,
    // otherwise the global constants will be double counted (squared)
    CS123SceneGlobalData global = { 1, 1, 1, 1};
    setGlobal(global);
    m_lightData = std::vector<CS123SceneLightData>();
    m_primitives = std::vector<CS123ScenePrimitive>();
    m_transformations = std::vector<glm::mat4x4>();
    m_flattenedGraph = std::vector<CS123FlatSceneNode>();
    m_textures = std::map<std::string, QImage>();

    // TODO [INTERSECT]
    // Make sure to copy over the lights and the scenegraph from the old scene,
    // as well as any other member variables your new scene will need.
    m_globalData = scene.m_globalData;
    m_lightData = scene.m_lightData;
    m_primitives = scene.m_primitives;
    m_transformations = scene.m_transformations;
    m_flattenedGraph = scene.m_flattenedGraph;
    m_textures = scene.m_textures;
//    m_kdTree = scene.m_kdTree;
}

Scene::~Scene()
{
    // Do not delete m_camera, it is owned by SupportCanvas3D
}

void Scene::parse(Scene *sceneToFill, CS123ISceneParser *parser) {
    // TODO: load scene into sceneToFill using setGlobal(), addLight(), addPrimitive(), and
    //   finishParsing()
    // Global data parsing
    CS123SceneGlobalData global;
    bool success = parser->getGlobalData(global);

    if (success) {
        sceneToFill->setGlobal(global);
    } else {
        std::cerr << "Failure to retrieve global data" << std::endl;
    }

    // Lights data parsing
    CS123SceneLightData light;

    int numLights = parser->getNumLights();
    for (int i = 0; i < numLights; i++) {
        success = parser->getLightData(i, light);

        if (success) {
            sceneToFill->addLight(light);
        } else {
            std::cerr << "Failure to retrieve lights data for light number " << i << std::endl;
        }
    }

    // Primitives parsing
    CS123SceneNode root = *(parser->getRootNode());
    sceneToFill->dfs(root, glm::mat4x4()); // Start with identity matrix
}

void Scene::dfs(const CS123SceneNode &node, const glm::mat4x4 &matrix) {
    glm::mat4x4 finalMatrix = matrix;

    // Multiply each transformation in the order in which they appear
    std::vector<CS123SceneTransformation*> transformations = node.transformations;
    for (int i = 0; i < (int) transformations.size(); i++) {
        glm::mat4x4 nextTrans = getTransformation(*transformations[i]);
        finalMatrix = finalMatrix * nextTrans;
    }

    // Add each primitive to the flattened graph
    std::vector<CS123ScenePrimitive*> nodePrims = node.primitives;
    for (int j = 0; j < (int) nodePrims.size(); j++) {
        addPrimitive(*nodePrims[j], finalMatrix);
    }

    // Recur on each child, passing the composite transformation matrix we have built to this point
    std::vector<CS123SceneNode*> nodeChildren = node.children;
    for (int z = 0; z < (int) nodeChildren.size(); z++) {
        dfs(*nodeChildren[z], finalMatrix);
    }

}

glm::mat4x4 Scene::getTransformation(CS123SceneTransformation transformation) {

    switch (transformation.type) {
        case TRANSFORMATION_TRANSLATE:
            return glm::translate(transformation.translate);
            break;
        case TRANSFORMATION_SCALE:
            return glm::scale(transformation.scale);
            break;
        case TRANSFORMATION_ROTATE:
            return glm::rotate(transformation.angle, transformation.rotate);
            break;
        case TRANSFORMATION_MATRIX:
            return transformation.matrix;
            break;
        default:
            std::cerr << "Error: no transformation type found for node" << std::endl;
            return glm::mat4x4();
            break;
    }
}

void Scene::addPrimitive(const CS123ScenePrimitive &scenePrimitive, const glm::mat4x4 &matrix) {
    m_primitives.push_back(scenePrimitive);
    m_transformations.push_back(matrix);

    CS123FlatSceneNode flatNode = CS123FlatSceneNode();
    flatNode.primitive = scenePrimitive;
    flatNode.transformation = matrix;

    CS123SceneFileMap tex = scenePrimitive.material.textureMap;
    std::string filename = tex.filename;
    flatNode.texFilename = filename;
    std::cout << "filename in scene file: " << filename << std::endl;

    // If we have not already stored this texture, store it
    if (filename != "") {
        if (m_textures.count(filename) == 0) {
            QString qStr = QString::fromStdString(filename);
            QImage image = QImage(qStr);
            m_textures[filename] = image;
        }
    }

    m_flattenedGraph.push_back(flatNode);
}

void Scene::addLight(const CS123SceneLightData &sceneLight) {
    m_lightData.push_back(sceneLight);
}

void Scene::setGlobal(const CS123SceneGlobalData &global) {
    m_globalData = global;
}

