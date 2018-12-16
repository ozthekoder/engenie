#ifndef MESH_H
#define MESH_H
#pragma once

#include <nlohmann/json.hpp>
#include "material.hpp"

using Json = nlohmann::json;

namespace Engenie
{
class Mesh
{
public:
  std::string name;
  std::shared_ptr<Material> material;
  size_t mode;

  Mesh() {}
  Mesh(Json mesh)
  {
  }

  void parsePrimitive(Json primitive)
  {
  }
};
}; // namespace Engenie
#endif