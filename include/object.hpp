#ifndef OBJECT_H
#define OBJECT_H
#pragma once

#include <nlohmann/json.hpp>
#include "entity.hpp"
#include "model.hpp"

using Json = nlohmann::json;

namespace Engenie
{
class Object : public Entity
{
  public:
    Object() : Entity() {}
    Object(Json data) : Entity(data) {}

    void draw(sf::Shader const &shader) {}
};
}; // namespace Engenie

#endif