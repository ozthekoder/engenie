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
  std::shared_ptr<Model> model;
  Object() : Entity() {}
  Object(Json data) : Entity(data) {}

  void draw(Shader const &shader) {}
};
}; // namespace Engenie

#endif