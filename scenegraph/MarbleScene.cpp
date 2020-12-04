#include "MarbleScene.h"

MarbleScene::MarbleScene()
{

}

MarbleScene::~MarbleScene() {

}

bool MarbleScene::checkMarbleCollision(Marble m1, Marble m2) {
    glm::vec4 m1Pos = m1.getPosition();
    glm::vec4 m2Pos = m2.getPosition();
    float dist = sqrt(pow(m1Pos.x - m2Pos.x, 2) + pow(m1Pos.y - m2Pos.y, 2) + pow(m1Pos.z - m2Pos.z, 2));

    float m1Rad = (float) m1.getRadius();
    float m2Rad = (float) m2.getRadius();

    if (dist < (m1Rad + m2Rad)) {
        return true;
    }
    return false;
}

void MarbleScene::render(SupportCanvas3D *context) {

}

void MarbleScene::settingsChanged() {

}
