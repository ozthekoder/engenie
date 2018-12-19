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

enum AlphaMode
{
    OPAQUE,
    MASK,
    BLEND,
};

struct TextureInfo
{
    size_t index = -1;
    size_t texCoord = 0;
    Json extras;
};

struct NormalTextureInfo : TextureInfo
{
    float scale = 1.0f;
};

struct OcclusionTextureInfo : TextureInfo
{
    float strength = 1.0f;
};

class Material
{
  public:
    std::string name;
    PBRModel pbrModel;

    glm::vec4 baseColorFactor;
    glm::vec3 emissiveFactor;

    float metallicFactor;
    float roughnessFactor;

    TextureInfo baseColorTexture;
    TextureInfo metallicRoughnessTexture;
    TextureInfo emissiveTexture;

    NormalTextureInfo normalTexture;
    OcclusionTextureInfo occlusionTexture;

    AlphaMode alphaMode;
    float alphaCutoff;

    bool doubleSided;

    Material()
    {
        name = std::string("default");
        pbrModel = PBRModel::MetallicRoughness;

        baseColorFactor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        metallicFactor = 1.0f;
        roughnessFactor = 1.0;
        emissiveFactor = glm::vec3(0.0f, 0.0f, 0.0f);

        alphaMode = AlphaMode::OPAQUE;
        alphaCutoff = 0.5f;

        doubleSided = false;
    }

    Material(Json props) : Material()
    {
    }
};
}; // namespace Engenie
#endif