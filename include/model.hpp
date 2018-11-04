#ifndef MODEL_H
#define MODEL_H

#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <iostream>
#include "stb_image.h"
#include "asset.hpp"
#include "image.hpp"
#include <nlohmann/json.hpp>
using Json = nlohmann::json;

namespace Engenie
{

static const std::string base64_chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

static inline bool is_base64(unsigned char c)
{
  return (isalnum(c) || (c == '+') || (c == '/'));
}

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
  Json gltf;
  std::vector<Buffer> buffers;
  std::vector<Image> images;

  void loadBuffers();
  void loadImages();
  void parseNode(Json node);
  bool isDataURI(const std::string &in);
  void decodeDataURI(std::vector<unsigned char> &buf, std::string &mime_type, const std::string &in, size_t reqBytes);
  std::string base64Decode(std::string const &encoded_string);
  std::string base64Encode(unsigned char const *bytes_to_encode, unsigned int in_len);
};

}; // namespace Engenie

#endif