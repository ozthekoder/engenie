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

static const std::string base64_chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

static inline bool is_base64(unsigned char c)
{
  return (isalnum(c) || (c == '+') || (c == '/'));
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

struct Image
{
  std::string name;
  int width;
  int height;
  int component;
  std::vector<unsigned char> data;
  std::string mimeType;
  std::string uri;
  Json extras;

  bool operator==(const Image &) const;
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
  bool isDataURI(const std::string &in);
  void decodeDataURI(std::vector<unsigned char> &buf, std::string &mime_type, const std::string &in, size_t reqBytes);
  std::string base64Decode(std::string const &encoded_string);
  std::string base64Encode(unsigned char const *bytes_to_encode, unsigned int in_len);
};

}; // namespace Engenie

#endif