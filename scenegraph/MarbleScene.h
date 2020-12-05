#ifndef MARBLESCENE_H
#define MARBLESCENE_H

#include "OpenGLScene.h"

#include <memory>
#include "marble/Marble.h"
#include <string>
#include "gl/shaders/Shader.h"

#include "ResourceLoader.h"

// either inherit from opengl scene or shapesscene --> depends if you need
// rendergeometry or setlights
class MarbleScene : public OpenGLScene
{
public:
    MarbleScene();

    virtual ~MarbleScene();

    virtual void render(SupportCanvas3D *context) override;
    virtual void settingsChanged() override;


private:
    // keep a vector of all the created marbles --> depending on how bad the memory gets(put it on the heap or just store a pointer)
    std::unique_ptr<CS123::GL::Shader> m_boxShader;
    std::vector<Marble> m_marbles;
    void loadBoxShader();

};

#endif // MARBLESCENE_H
