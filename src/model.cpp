#define STB_IMAGE_IMPLEMENTATION
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
}

} // namespace Engenie