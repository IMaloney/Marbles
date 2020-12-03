#ifndef MESHLOADER_H
#define MESHLOADER_H

#include "Shape.h"

class MeshLoader : public Shape
{
public:
    MeshLoader();
    MeshLoader(std::string meshPath);
    ~MeshLoader();

private:
    std::ifstream m_myFile;

    std::vector<GLfloat> generateVertexData(int param1, int param2) override;

    glm::vec3 calculateSurfaceNormal(glm::vec3 faces, std::vector<glm::vec3> vertices);
};

#endif // MESHLOADER_H
