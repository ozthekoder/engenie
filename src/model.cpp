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
    try
    {
        std::vector<Mesh> nodeMeshes;
        Json nodes = gltf["scenes"][gltf["scene"].get<size_t>()];
        for (auto node : nodes)
        {
            nodeMeshes = parseNode(gltf, node, transformation);
            meshes.insert(
                meshes.end(),
                std::make_move_iterator(nodeMeshes.begin()),
                std::make_move_iterator(nodeMeshes.end()));
        }
    }
    catch (nlohmann::json::type_error &e)
    {
        std::cout << e.what() << '\n';
    }
}

} // namespace Engenie