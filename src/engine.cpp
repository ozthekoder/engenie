#include "engine.hpp"

namespace Engenie
{
Engine &Engine::loadConfig(std::string const &path)
{
    std::ifstream fileStream(path);
    auto src = std::string(std::istreambuf_iterator<char>(fileStream), std::istreambuf_iterator<char>());
    Json config = Json::parse(src);
    return *this;
}

sf::Window *Engine::createWindow(Json config)
{
    int width = config["width"];
    int height = config["height"];
    std::string title = config["title"];
}
} // namespace Engenie