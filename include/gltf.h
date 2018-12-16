#ifndef GLTF_H
#define GLTF_H

#include <string>
#include <vector>
#include <nlohmann/json.hpp>
using Json = nlohmann::json;

namespace Engenie
{

enum ComponentType
{
    BYTE = 5120,
    UNSIGNED_BYTE = 5121,
    SHORT = 5122,
    UNSIGNED_SHORT = 5123,
    UNSIGNED_INT = 5125,
    FLOAT = 5126
};

enum TypeSize
{
    NONE = 0,
    SCALAR = 1,
    VEC2 = 2,
    VEC3 = 3,
    VEC4 = 4,
    MAT2 = 4,
    MAT3 = 9,
    MAT4 = 16
};

enum AttributeType
{
    INDEX = 0,
    POSITION = 1,
    NORMAL = 2,
    TANGENT = 3,
    TEXCOORD_0 = 4,
    TEXCOORD_1 = 5,
    COLOR_0 = 6,
    JOINTS_0 = 7,
    WEIGHTS_0 = 8,
};

enum GPUTarget
{
    ARRAY_BUFFER = 34962,
    ELEMENT_ARRAY_BUFFER = 34963,
};

static TypeSize get_type_size(std::string const &typeName)
{
    if (typeName == "SCALAR")
    {
        return TypeSize::SCALAR;
    }
    else if (typeName == "VEC2")
    {
        return TypeSize::VEC2;
    }
    else if (typeName == "VEC3")
    {
        return TypeSize::VEC3;
    }
    else if (typeName == "VEC4")
    {
        return TypeSize::VEC4;
    }
    else if (typeName == "MAT2")
    {
        return TypeSize::MAT2;
    }
    else if (typeName == "MAT3")
    {
        return TypeSize::MAT3;
    }
    else if (typeName == "MAT4")
    {
        return TypeSize::MAT4;
    }
    else
    {
        return TypeSize::NONE;
    }
}

struct Buffer
{
    std::string name;
    std::vector<unsigned char> data;
    std::string uri;
    size_t byteLength;
    Json extras;

    bool operator==(const Buffer &) const;
};

struct VertexAttribute
{
    std::string name = "";
    std::string type = "SCALAR";
    AttributeType attributeType;
    ComponentType componentType;
    bool normalized = false;
    size_t count;
    size_t max;
    size_t min;
};

}; // namespace Engenie

#endif