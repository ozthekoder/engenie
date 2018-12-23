#ifndef MODEL_H
#define MODEL_H

#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <iostream>
#include "gltf.h"

#include "asset.hpp"
#include "image.hpp"
#include <nlohmann/json.hpp>
using Json = nlohmann::json;

namespace Engenie
{

class Model : public Asset
{

public:
  Json gltf;
  std::vector<Buffer> buffers;
  std::vector<Image> images;
  std::vector<Mesh> meshes;

  Model() : Asset() {}
  Model(std::string const &filePath) : Asset(filePath)
  {
    loadFromFile(filePath);
  }

  void loadFromFile(std::string const &filePath);
  void bufferData();
};

}; // namespace Engenie

#endif