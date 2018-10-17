#include "viewport.hpp"

namespace Engenie
{
void Viewport::init(sf::Window *window)
{
    sf::Vector2u size = window->getSize();
    width = size.x;
    height = size.y;
    glViewport(0, 0, width, height);
}

glm::mat4 Viewport::getProjectionMatrix()
{
    switch (projectionType)
    {
    case ORTHOGRAPHIC_PROJECTION:
        return glm::ortho(0.0f, (float)width, 0.0f, (float)height);
        break;
    case PERSPECTIVE_PROJECTION:
    default:
        return glm::perspective(glm::radians(fov), (float)width / (float)height, nearZ, farZ);
        break;
    }
}
}; // namespace Engenie