#ifndef MODEL_H
#define MODEL_H
#pragma once
#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "tiny_gltf.h"
#include <string>
#include "asset.hpp"

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

    void loadFromFile(std::string const &filePath)
    {
        std::string err;
        std::string warn;
        tinygltf::TinyGLTF loader;
        bool ret = loader.LoadASCIIFromFile(model, &err, &warn, filePath); // for binary glTF(.glb)
        if (!warn.empty())
        {
            std::cout << "Model Loading Warning: " << warn << std::endl;
        }

        if (!err.empty())
        {
            std::cout << "Model Loading Error: " << err << std::endl;
        }

        if (!ret)
        {
            printf("Failed to parse glTF\n");
        }
    }

  private:
    tinygltf::Model *model;
};
}; // namespace Engenie

#endif