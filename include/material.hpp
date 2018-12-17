#ifndef MATERIAL_H
#define MATERIAL_H
#pragma once

#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <nlohmann/json.hpp>

using Json = nlohmann::json;

namespace Engenie
{

enum PBRModel
{
    MetallicRoughness,
    SpecularGlossiness,
    None,
};

class Material
{
  public:
    std::string name;
    PBRModel pbrModel;
    Material(){};
    Material(Json props){

    };
};
}; // namespace Engenie
#endif