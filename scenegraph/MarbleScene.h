#ifndef MARBLESCENE_H
#define MARBLESCENE_H

#include "OpenGLScene.h"

#include <memory>
#include <QTimer>
#include "marble/Marble.h"
#include "marble/MetalMarble.h"
#include "marble/WoodMarble.h"
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

    bool checkMarbleCollision(Marble *m1, Marble *m2);


private:
    // keep a vector of all the created marbles --> depending on how bad the memory gets(put it on the heap or just store a pointer)
    std::unique_ptr<CS123::GL::Shader> m_boxShader;
    std::vector<Marble> m_marbles;

    int nextMarble;

    void loadBoxShader();

    /** Timer calls tick() 60 times per second. */
    QTimer m_timer;
    float m_fps;

    float m_tick;
    float m_angle;

};

#endif // MARBLESCENE_H
