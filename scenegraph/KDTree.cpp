#include "KDTree.h"

KDTree::KDTree() {

}

KDTree::KDTree(std::vector<CS123FlatSceneNode> nodes) { // Constructor
    m_nodes = std::vector<CS123FlatSceneNode>();

    for (int i = 0; i < (int) nodes.size(); i++) {
        std::vector<glm::vec4> allPoints = std::vector<glm::vec4>();

        glm::mat4x4 trans = nodes[i].transformation;

        glm::vec4 corner1 = {0.5f, 0.5f, 0.5f, 1.0f};
        corner1 = trans * corner1;
        allPoints.push_back(corner1);

        glm::vec4 corner2 = {-0.5f, 0.5f, 0.5f, 1.0f};
        corner2 = trans * corner2;
        allPoints.push_back(corner2);

        glm::vec4 corner3 = {0.5f, -0.5f, 0.5f, 1.0f};
        corner3 = trans * corner3;
        allPoints.push_back(corner3);

        glm::vec4 corner4 = {0.5f, 0.5f, -0.5f, 1.0f};
        corner4 = trans * corner4;
        allPoints.push_back(corner4);

        glm::vec4 corner5 = {-0.5f, -0.5f, 0.5f, 1.0f};
        corner5 = trans * corner5;
        allPoints.push_back(corner5);

        glm::vec4 corner6 = {0.5f, -0.5f, -0.5f, 1.0f};
        corner6 = trans * corner6;
        allPoints.push_back(corner6);

        glm::vec4 corner7 = {-0.5f, 0.5f, -0.5f, 1.0f};
        corner7 = trans * corner7;
        allPoints.push_back(corner7);

        glm::vec4 corner8 = {-0.5f, -0.5f, -0.5f, 1.0f};
        corner8 = trans * corner8;
        allPoints.push_back(corner8);

        std::sort(allPoints.begin(), allPoints.end(), sortX);
        float minX = allPoints[0].x;
        float maxX = allPoints[7].x;

        std::sort(allPoints.begin(), allPoints.end(), sortY);
        float minY = allPoints[0].x;
        float maxY = allPoints[7].x;

        std::sort(allPoints.begin(), allPoints.end(), sortZ);
        float minZ = allPoints[0].z;
        float maxZ = allPoints[7].z;

        nodes[i].boundingBoxMin = glm::vec4(minX, minY, minZ, 1.0f);
        nodes[i].boundingBoxMax = glm::vec4(maxX, maxY, maxZ, 1.0f);
        m_nodes.push_back(nodes[i]);
    }
}

KDTree::~KDTree() { // Destructor

//    deleteTreeRecursive(m_root);
}

//void KDTree::deleteTreeRecursive(KDTreeNode* root) {
//    if (root->left) {
//        deleteTreeRecursive(root->left);
//    }

//    if (root->right) {
//        deleteTreeRecursive(root->right);
//    }

//    delete root;
//}

KDTreeNode* KDTree::buildTree() {
    std::sort(m_nodes.begin(), m_nodes.end(), sortNodesX);

    int midPoint = (int) m_nodes.size() / 2;
    CS123FlatSceneNode node = m_nodes.at(midPoint);

    m_root = new KDTreeNode();
    m_root->point = node.boundingBoxMin;
    m_root->sceneNode = node;
    m_root->dim = 0;

    std::vector<CS123FlatSceneNode>::const_iterator first1 = m_nodes.begin();
    std::vector<CS123FlatSceneNode>::const_iterator last1 = m_nodes.begin() + midPoint;
    std::vector<CS123FlatSceneNode> leftSublist(first1, last1);

    std::vector<CS123FlatSceneNode>::const_iterator first2 = m_nodes.begin() + midPoint + 1;
    std::vector<CS123FlatSceneNode>::const_iterator last2 = m_nodes.begin() + m_nodes.size() - 1;
    std::vector<CS123FlatSceneNode> rightSublist(first2, last2);

    m_root->left = buildTreeRecursive(leftSublist, 1);
    m_root->right = buildTreeRecursive(rightSublist, 1);

    return m_root;
}

KDTreeNode* KDTree::buildTreeRecursive(std::vector<CS123FlatSceneNode> sublist, int axis) {
    if (axis == 0) {
        std::sort(sublist.begin(), sublist.end(), sortNodesX);
    } else if (axis == 1) {
        std::sort(sublist.begin(), sublist.end(), sortNodesY);
    } else {
        std::sort(sublist.begin(), sublist.end(), sortNodesZ);
    }

    int nextDim = axis + 1;
    if (nextDim > 2) {
        nextDim = 0;
    }

    if (sublist.size() == 0) {

        return nullptr;

    } else if (sublist.size() == 1) {

        KDTreeNode *child = new KDTreeNode();
        child->dim = axis;
        child->point = sublist.at(0).boundingBoxMin;
        child->sceneNode = sublist.at(0);
        return child;

    } else if (sublist.size() == 2) {

        KDTreeNode *parent = new KDTreeNode();
        parent->dim = axis;
        parent->point = sublist.at(0).boundingBoxMin;
        parent->sceneNode = sublist.at(0);

        KDTreeNode *child = new KDTreeNode();
        child->dim = nextDim;
        child->point = sublist.at(1).boundingBoxMin;
        child->sceneNode = sublist.at(1);

        if (child->point[axis] < parent->point[axis]) {
            parent->left = child;
        } else {
            parent->right = child;
        }

        return parent;

    } else {
        int midPoint = (int) sublist.size() / 2;
        CS123FlatSceneNode node = sublist.at(midPoint);

        KDTreeNode *parent = new KDTreeNode();
        parent->dim = axis;
        parent->point = sublist.at(midPoint).boundingBoxMin;
        parent->sceneNode = sublist.at(midPoint);

        std::vector<CS123FlatSceneNode>::const_iterator first1 = sublist.begin();
        std::vector<CS123FlatSceneNode>::const_iterator last1 = sublist.begin() + midPoint;
        std::vector<CS123FlatSceneNode> leftSublist(first1, last1);

        std::vector<CS123FlatSceneNode>::const_iterator first2 = sublist.begin() + midPoint + 1;
        std::vector<CS123FlatSceneNode>::const_iterator last2 = sublist.begin() + sublist.size() - 1;
        std::vector<CS123FlatSceneNode> rightSublist(first2, last2);

        parent->left = buildTreeRecursive(leftSublist, 1);
        parent->right = buildTreeRecursive(rightSublist, 1);

        return parent;
    }
}


KDTreeNode* KDTree::findNearest(glm::vec4 point) {

    if (point.x < m_root->point.x) {
        if (m_root->left) {
            return findNearestRecursive(m_root->left, point);
        } else {
            return m_root;
        }

    } else {

        bool inXBounds = point.x < m_root->sceneNode.boundingBoxMax.x;
        bool inYBounds = (point.y > m_root->point.y) && (point.y < m_root->sceneNode.boundingBoxMax.y);
        //bool inZBounds = (point.z > m_root->point.z) && (point.z < m_root->sceneNode.boundingBoxMax.z);

        if (inXBounds && inYBounds /*&& inZBounds*/) {
            return m_root;
        } else {

            if (m_root->right) {
                return findNearestRecursive(m_root->right, point);
            } else {
                return m_root;
            }

        }
    }
}

KDTreeNode* KDTree::findNearestRecursive(KDTreeNode *root, glm::vec4 point) {

    int axis = root->dim;

    if (point[axis] < root->point[axis]) {
        if (root->left) {
            return findNearestRecursive(root->left, point);
        } else {
            return m_root;
        }

    } else {

        bool inXBounds = point.x < root->sceneNode.boundingBoxMax.x;
        bool inYBounds = (point.y > root->point.y) && (point.y < root->sceneNode.boundingBoxMax.y);
//        bool inZBounds = (point.z > root->point.z) && (point.z < root->sceneNode.boundingBoxMax.z);

        if (inXBounds && inYBounds /*&& inZBounds*/) {
            return root;
        } else {

            if (root->right) {
                return findNearestRecursive(root->right, point);
            } else {
                return root;
            }

        }
    }

}
