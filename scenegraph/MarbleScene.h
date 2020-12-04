#ifndef MARBLESCENE_H
#define MARBLESCENE_H

#include "OpenGLScene.h"

#include <memory>
#include "marble/Marble.h"

// either inherit from opengl scene or shapesscene --> depends if you need
// rendergeometry or setlights
class MarbleScene : public OpenGLScene
{
public:
    MarbleScene();

    virtual ~MarbleScene();

    virtual void render(SupportCanvas3D *context) override;
    virtual void settingsChanged() override;

    bool checkMarbleCollision(Marble m1, Marble m2);


private:
    // keep a vector of all the created marbles --> depending on how bad the memory gets(put it on the heap or just store a pointer)
    std::vector<Marble> m_marbles;

};

#endif // MARBLESCENE_H
