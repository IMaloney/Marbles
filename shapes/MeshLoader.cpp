#include "MeshLoader.h"

MeshLoader::MeshLoader()
{
}

MeshLoader::MeshLoader(std::string meshPath) :
    m_myFile()
{
    m_myFile.open(meshPath);
    m_vertexData = generateVertexData(0, 0);
    /** build the VAO so that the shape is ready to be drawn */
    buildVAO();
}

MeshLoader::~MeshLoader()
{
}

std::vector<GLfloat> MeshLoader::generateVertexData(int param1, int param2) {
    std::vector<glm::vec3> verts = std::vector<glm::vec3>();
    std::vector<glm::vec3> faces = std::vector<glm::vec3>();

    std::vector<GLfloat> data = std::vector<GLfloat>();

    if (m_myFile.is_open()){   // If the file was opened properly
          std::string line;
          while(getline(m_myFile, line)){ // While there is still data to read
             std::cout << line << std::endl;

             size_t idx = 0;
             std::string token;
             std::string delim = " ";

             // Check if it is a vertex, a face, or a comment
             idx = line.find(delim);
             token = line.substr(0, idx);
             line.erase(0, idx + delim.length());

             if (token == "v") {
                 glm::vec3 vertex = glm::vec3();
                 int counter = 0;

                 while ((idx = line.find(delim)) != std::string::npos) {
                     token = line.substr(0, idx);
                     line.erase(0, idx + delim.length());
                     float pt = std::stof(token);
                     vertex[counter++] = pt;
                 }
                 float pt = std::stof(line);
                 vertex[counter] = pt;

                 verts.push_back(vertex);
             } else if (token == "f") {
                 glm::vec3 face = glm::vec3();
                 int counter = 0;

                 while ((idx = line.find(delim)) != std::string::npos) {
                     token = line.substr(0, idx);
                     line.erase(0, idx + delim.length());
                     float pt = std::stoi(token);
                     face[counter++] = pt;
                 }
                 float pt = std::stoi(line);
                 face[counter] = pt;

                 faces.push_back(face);
             } else {
                 continue;
             }
          }
          m_myFile.close(); // Close the file

          for (int i = 0; i < faces.size(); i++) {
                glm::vec3 face = faces[i];

                for (int j = 0; j < 3; j++) {
                    int index = face[j];
                    glm::vec3 vertex = verts[index];

                    for (int k = 0; k < 3; k++) {
                        data.push_back(vertex[k]);
                    }

                    // COMPUTE NORMALS HERE
                    glm::vec3 norm = calculateSurfaceNormal(face, verts);
                    norm = glm::normalize(norm);
                    data.push_back(norm.x);
                    data.push_back(norm.y);
                    data.push_back(norm.z);
                }
          }
       }


    return data;
}

glm::vec3 MeshLoader::calculateSurfaceNormal(glm::vec3 faces, std::vector<glm::vec3> vertices) {
    glm::vec3 normal = glm::vec3();

    glm::vec3 p1 = vertices[faces[0]];
    glm::vec3 p2 = vertices[faces[1]];
    glm::vec3 p3 = vertices[faces[2]];

    glm::vec3 U = p2 - p1;
    glm::vec3 V = p3 - p1;

    normal.x = (U.y * V.z) - (U.z * V.y);
    normal.y = (U.z * V.x) - (U.x * V.z);
    normal.z = (U.x * V.y) - (U.y * V.x);

    return normal;
}
