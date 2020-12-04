#ifndef WOODMARBLE_H
#define WOODMARBLE_H

#include "Marble.h"
#include "qimage.h"

class WoodMarble : public Marble
{
public:
    WoodMarble(float gravity, int radius, int weight);
    virtual ~WoodMarble();

private:
    // texture is going to be saved as a member
    QImage m_woodTexture;
    GLuint m_textureID;
    void initializeTexture();
};

#endif // WOODMARBLE_H
