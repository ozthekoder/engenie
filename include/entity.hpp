#ifndef ENTITY_H
#define ENTITY_H
#pragma once

#include "shader.hpp"
#include <nlohmann/json.hpp>

using Json = nlohmann::json;

namespace Engenie
{
class Entity
{
public:
  Entity() {}
  Entity(Json data) {}

  virtual void draw(Shader const &shader) = 0;
};
}; // namespace Engenie

#endif