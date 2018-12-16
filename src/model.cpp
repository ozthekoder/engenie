#include "model.hpp"

namespace Engenie
{
void Model::loadFromFile(std::string const &filePath)
{
    std::ifstream fileStream(filePath);
    auto src = std::string(std::istreambuf_iterator<char>(fileStream), std::istreambuf_iterator<char>());
    gltf = Json::parse(src);
    buffers = loadGeometryData(directory, gltf);
    images = loadTextureData(directory, gltf);
    glm::mat4 transformation = glm::mat4(1.0f);
    meshes = parseNode(gltf, 0, transformation);
}

} // namespace Engenie