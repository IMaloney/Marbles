#ifndef KDTREE_H
#define KDTREE_H

#include "CS123SceneData.h"

const int k = 3;

struct KDTreeNode {
    glm::vec4 point;
    KDTreeNode* left;
    KDTreeNode* right;
    CS123FlatSceneNode sceneNode;
    int dim;
};

class KDTree {

public:

   KDTreeNode *m_root;
   std::vector<CS123FlatSceneNode> m_nodes;

   KDTree();
   KDTree(std::vector<CS123FlatSceneNode> nodes);
   ~KDTree();

   KDTreeNode* buildTree();
   KDTreeNode* buildTreeRecursive(std::vector<CS123FlatSceneNode> sublist, int axis);

   void deleteTreeRecursive(KDTreeNode* root);

   KDTreeNode insert(CS123FlatSceneNode node);
   KDTreeNode insertRecursive(KDTreeNode node, int dim);

   KDTreeNode* findNearest(glm::vec4 point);
   KDTreeNode* findNearestRecursive(KDTreeNode *root, glm::vec4 point);

   static bool sortX (glm::vec4 i, glm::vec4 j) { return (i[0]<j[0]); }
   static bool sortY (glm::vec4 i, glm::vec4 j) { return (i[1]<j[1]); }
   static bool sortZ (glm::vec4 i, glm::vec4 j) { return (i[2]<j[2]); }

   static bool sortNodesX (CS123FlatSceneNode i, CS123FlatSceneNode j) { return (i.boundingBoxMin[0]<j.boundingBoxMin[0]); }
   static bool sortNodesY (CS123FlatSceneNode i, CS123FlatSceneNode j) { return (i.boundingBoxMin[1]<j.boundingBoxMin[1]); }
   static bool sortNodesZ (CS123FlatSceneNode i, CS123FlatSceneNode j) { return (i.boundingBoxMin[2]<j.boundingBoxMin[2]); }

private:

};

#endif
