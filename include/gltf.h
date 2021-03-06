#ifndef ENGENIE_GLTF_H
#define ENGENIE_GLTF_H
#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <iterator>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <nlohmann/json.hpp>
#include "image.hpp"
#include "material.hpp"

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
    ARRAY_BUFFER = GL_ARRAY_BUFFER,
    ELEMENT_ARRAY_BUFFER = GL_ELEMENT_ARRAY_BUFFER,
};

struct Buffer
{
    std::vector<unsigned char> data;
    GPUTarget target;

    bool operator==(const Buffer &) const;
};

struct VertexAttribute
{
    size_t buffer = 0;
    TypeSize type = TypeSize::NONE;
    AttributeType attributeType = AttributeType::INDEX;
    ComponentType componentType = ComponentType::BYTE;
    bool normalized = false;
    size_t count = 0;
    size_t byteOffset = 0;
    size_t stride = 0;

    bool operator==(const VertexAttribute &) const;
};

struct Mesh
{
    std::string name;
    std::shared_ptr<Material> material;
    std::vector<VertexAttribute> attributes;
    glm::mat4 transformation;
    size_t mode;
};

static const std::string base64_chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

static inline bool is_base64(unsigned char c)
{
    return (isalnum(c) || (c == '+') || (c == '/'));
}

static std::string base64Encode(unsigned char const *bytes_to_encode, unsigned int in_len)
{
    std::string ret;
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];

    while (in_len--)
    {
        char_array_3[i++] = *(bytes_to_encode++);
        if (i == 3)
        {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for (i = 0; (i < 4); i++)
                ret += base64_chars[char_array_4[i]];
            i = 0;
        }
    }

    if (i)
    {
        for (j = i; j < 3; j++)
            char_array_3[j] = '\0';

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;

        for (j = 0; (j < i + 1); j++)
            ret += base64_chars[char_array_4[j]];

        while ((i++ < 3))
            ret += '=';
    }

    return ret;
}

static std::string base64Decode(std::string const &encoded_string)
{
    int in_len = encoded_string.size();
    int i = 0;
    int j = 0;
    int in_ = 0;
    unsigned char char_array_4[4], char_array_3[3];
    std::string ret;

    while (in_len-- && (encoded_string[in_] != '=') && is_base64(encoded_string[in_]))
    {
        char_array_4[i++] = encoded_string[in_];
        in_++;
        if (i == 4)
        {
            for (i = 0; i < 4; i++)
                char_array_4[i] = base64_chars.find(char_array_4[i]);

            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

            for (i = 0; (i < 3); i++)
                ret += char_array_3[i];
            i = 0;
        }
    }

    if (i)
    {
        for (j = i; j < 4; j++)
            char_array_4[j] = 0;

        for (j = 0; j < 4; j++)
            char_array_4[j] = base64_chars.find(char_array_4[j]);

        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

        for (j = 0; (j < i - 1); j++)
            ret += char_array_3[j];
    }

    return ret;
}

static bool isDataURI(const std::string &in)
{
    std::string header = "data:application/octet-stream;base64,";
    if (in.find(header) == 0)
    {
        return true;
    }

    header = "data:image/jpeg;base64,";
    if (in.find(header) == 0)
    {
        return true;
    }

    header = "data:image/png;base64,";
    if (in.find(header) == 0)
    {
        return true;
    }

    header = "data:image/bmp;base64,";
    if (in.find(header) == 0)
    {
        return true;
    }

    header = "data:image/gif;base64,";
    if (in.find(header) == 0)
    {
        return true;
    }

    header = "data:text/plain;base64,";
    if (in.find(header) == 0)
    {
        return true;
    }

    header = "data:application/gltf-buffer;base64,";
    if (in.find(header) == 0)
    {
        return true;
    }

    return false;
}

static void decodeDataURI(std::vector<unsigned char> &buf, std::string &mime_type, const std::string &in, size_t reqBytes)
{
    std::string header = "data:application/octet-stream;base64,";
    std::string data;
    if (in.find(header) == 0)
    {
        data = base64Decode(in.substr(header.size())); // cut mime string.
    }

    if (data.empty())
    {
        header = "data:image/jpeg;base64,";
        if (in.find(header) == 0)
        {
            mime_type = "image/jpeg";
            data = base64Decode(in.substr(header.size())); // cut mime string.
        }
    }

    if (data.empty())
    {
        header = "data:image/png;base64,";
        if (in.find(header) == 0)
        {
            mime_type = "image/png";
            data = base64Decode(in.substr(header.size())); // cut mime string.
        }
    }

    if (data.empty())
    {
        header = "data:image/bmp;base64,";
        if (in.find(header) == 0)
        {
            mime_type = "image/bmp";
            data = base64Decode(in.substr(header.size())); // cut mime string.
        }
    }

    if (data.empty())
    {
        header = "data:image/gif;base64,";
        if (in.find(header) == 0)
        {
            mime_type = "image/gif";
            data = base64Decode(in.substr(header.size())); // cut mime string.
        }
    }

    if (data.empty())
    {
        header = "data:text/plain;base64,";
        if (in.find(header) == 0)
        {
            mime_type = "text/plain";
            data = base64Decode(in.substr(header.size()));
        }
    }

    if (data.empty())
    {
        header = "data:application/gltf-buffer;base64,";
        if (in.find(header) == 0)
        {
            data = base64Decode(in.substr(header.size()));
        }
    }

    size_t sz = data.length();
    buf.resize(sz);
    std::copy(data.begin(), data.end(), buf.begin());
}

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

static AttributeType get_attribute_type(std::string const &typeName)
{
    if (typeName == "POSITION")
    {
        return AttributeType::POSITION;
    }
    else if (typeName == "NORMAL")
    {
        return AttributeType::NORMAL;
    }
    else if (typeName == "TANGENT")
    {
        return AttributeType::TANGENT;
    }
    else if (typeName == "TEXCOORD_0")
    {
        return AttributeType::TEXCOORD_0;
    }
    else if (typeName == "TEXCOORD_1")
    {
        return AttributeType::TEXCOORD_1;
    }
    else if (typeName == "COLOR_0")
    {
        return AttributeType::COLOR_0;
    }
    else if (typeName == "JOINTS_0")
    {
        return AttributeType::JOINTS_0;
    }
    else if (typeName == "WEIGHTS_0")
    {
        return AttributeType::WEIGHTS_0;
    }
    else
    {
        return AttributeType::INDEX;
    }
}

static std::vector<Buffer> loadGeometryData(std::string directory, Json &gltf)
{
    Json bffrs = gltf["buffers"];
    Json bufferViews = gltf["bufferViews"];
    std::vector<Buffer> buffers;
    std::vector<std::vector<unsigned char>> chunks;

    for (auto it = bffrs.begin(); it != bffrs.end(); ++it)
    {
        Json bfr = it.value();
        std::string uri = bfr["uri"];
        std::vector<unsigned char> data;

        if (isDataURI(uri))
        {
            std::string dummy = std::string("");
            decodeDataURI(data, dummy, uri, 0);
        }

        size_t totalLength = bfr["byteLength"];

        std::string fullPath = directory + uri;

        std::ifstream file(fullPath, std::ios::in | std::ios::binary | std::ios::ate);

        if (file.is_open())
        {
            std::streampos size;
            size_t sz;
            char *memblock;
            size = file.tellg();
            sz = static_cast<size_t>(size);
            memblock = new char[sz];
            file.seekg(0, std::ios::beg);
            file.read(memblock, size);
            file.close();

            unsigned char *dt = (unsigned char *)memblock;
            data.resize(sz);
            std::copy(dt, dt + sz, data.begin());
        }

        chunks.push_back(data);
    }

    for (auto it = bufferViews.begin(); it != bufferViews.end(); ++it)
    {
        Json bufferView = it.value();
        size_t byteOffset = bufferView["byteOffset"].get<size_t>();
        size_t byteLength = bufferView["byteLength"].get<size_t>();
        GPUTarget target = bufferView["target"].get<GPUTarget>();
        std::vector<unsigned char>::const_iterator start = chunks[bufferView["buffer"].get<size_t>()].begin() + byteOffset;
        std::vector<unsigned char>::const_iterator end = start + byteLength;
        std::vector<unsigned char> data(start, end);
        buffers.push_back({data, target});
    }

    return buffers;
}

static std::vector<Image> loadTextureData(std::string directory, Json &gltf)
{
    Json imgs = gltf["images"];
    std::vector<Image> images;
    for (auto it = imgs.begin(); it != imgs.end(); ++it)
    {
        Json img = it.value();
        Image image;
        std::string uri = img["uri"];
        if (isDataURI(uri))
        {
            decodeDataURI(image.data, image.mimeType, uri, 0);
        }
        std::string fullPath = directory + uri;
        image.load(fullPath);
        images.push_back(image);
    }

    return images;
}

static void extractAttribute(Json gltf, size_t accessorIndex, VertexAttribute &attribute)
{
    Json accessor = gltf["accessors"][accessorIndex];
    size_t buffer = accessor["bufferView"];
    attribute.buffer = buffer;
    attribute.type = get_type_size(accessor["type"]);
    attribute.componentType = accessor["componentType"];
    attribute.byteOffset = accessor["byteOffset"];
    attribute.count = accessor["count"];
}

static std::vector<Mesh> parseNode(Json gltf, size_t index, glm::mat4 transformation)
{
    std::vector<Mesh> meshes;
    glm::mat4 trans = transformation;
    try
    {
        Json node = gltf["nodes"].at(index);

        if (node.value("matrix", false))
        {
            Json m = node["matrix"];
            trans = trans * glm::mat4(
                                m[0].get<float>(),
                                m[1].get<float>(),
                                m[2].get<float>(),
                                m[3].get<float>(),
                                m[4].get<float>(),
                                m[5].get<float>(),
                                m[6].get<float>(),
                                m[7].get<float>(),
                                m[8].get<float>(),
                                m[9].get<float>(),
                                m[10].get<float>(),
                                m[11].get<float>(),
                                m[12].get<float>(),
                                m[13].get<float>(),
                                m[14].get<float>(),
                                m[15].get<float>());
        }
        else
        {
            glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f);
            glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
            glm::quat rotation = glm::quat(0.0f, 0.0f, 0.0f, 1.0f);

            if (node.value("scale", false))
            {
                Json s = node["scale"];
                scale = glm::vec3(s[0].get<float>(), s[1].get<float>(), s[2].get<float>());
                trans = glm::scale(trans, scale);
            }

            if (node.value("rotation", false))
            {
                Json s = node["rotation"];
                rotation = glm::quat(s[0].get<float>(), s[1].get<float>(), s[2].get<float>(), s[3].get<float>());
                trans = trans * glm::mat4_cast(rotation);
            }

            if (node.value("translation", false))
            {
                Json t = node["translation"];
                translation = glm::vec3(t[0].get<float>(), t[1].get<float>(), t[2].get<float>());
                trans = glm::translate(trans, translation);
            }
        }

        if (node.value("mesh", -1) >= 0)
        {
            size_t i = node["mesh"];
            Json m = gltf["meshes"][i];
            for (auto primitive : m["primitives"])
            {
                std::shared_ptr<Material> material(new Material());
                Mesh mesh;
                mesh.material = material;
                if (primitive.value("indices", -1) >= 0)
                {
                    VertexAttribute attribute;
                    attribute.attributeType = AttributeType::INDEX;
                    extractAttribute(gltf, primitive["indices"], attribute);

                    mesh.attributes.push_back(attribute);
                }

                for (auto it = primitive["attributes"].begin(); it != primitive["attributes"].end(); ++it)
                {
                    VertexAttribute attribute;
                    attribute.attributeType = get_attribute_type(it.key());
                    extractAttribute(gltf, it.value(), attribute);

                    mesh.attributes.push_back(attribute);
                }

                mesh.transformation = trans;
                meshes.push_back(mesh);
            }
        }

        if (node.value("children", false))
        {
            for (size_t i : node["children"])
            {
                std::vector<Mesh> childrenMeshes = parseNode(gltf, i, trans);

                meshes.insert(
                    meshes.end(),
                    std::make_move_iterator(childrenMeshes.begin()),
                    std::make_move_iterator(childrenMeshes.end()));
            }
        }
    }
    catch (nlohmann::json::out_of_range &e)
    {
        std::cout << e.what() << '\n';
    }
    return meshes;
} // namespace Engenie
}; // namespace Engenie

#endif