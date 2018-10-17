#ifndef TEXT_H
#define TEXT_H
#pragma once

#include <nlohmann/json.hpp>
#include "entity.hpp"
#include "font.hpp"

using Json = nlohmann::json;

namespace Engenie
{
class Text : public Entity
{
  public:
    Text() : Entity() {}
    Text(Json data) : Entity(data) {}

    void draw(sf::Shader const &shader) {}
};
}; // namespace Engenie

#endif