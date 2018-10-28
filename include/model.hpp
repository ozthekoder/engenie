#ifndef MODEL_H
#define MODEL_H
#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <iostream>
#include "stb_image.h"
#include "asset.hpp"
#include <nlohmann/json.hpp>
using Json = nlohmann::json;

namespace Engenie
{
class Model : public Asset
{
  public:
    Model() : Asset() {}
    Model(std::string const &filePath) : Asset(filePath)
    {
        loadFromFile(filePath);
    }

    void loadFromFile(std::string const &filePath);

  private:
};
}; // namespace Engenie

#endif