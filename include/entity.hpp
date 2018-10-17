#ifndef ENTITY_H
#define ENTITY_H
#pragma once

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

using Json = nlohmann::json;

namespace Engenie
{
class Entity
{
  public:
    Entity() {}
    Entity(Json data) {}

    virtual void draw(sf::Shader const &shader) = 0;
};
}; // namespace Engenie

#endif