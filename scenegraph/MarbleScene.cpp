#include "MarbleScene.h"

MarbleScene::MarbleScene()
{

}

MarbleScene::~MarbleScene() {

}

void MarbleScene::render(SupportCanvas3D *context) {

}

void MarbleScene::settingsChanged() {

}


void MarbleScene::loadBoxShader() {
    std::string vertexSource = ResourceLoader::loadResourceFileToString(":/shaders/box.vert");
    std::string fragmentSource = ResourceLoader::loadResourceFileToString(":/shaders/box.frag");
    m_boxShader = std::make_unique<CS123::GL::Shader>(vertexSource, fragmentSource);
}
