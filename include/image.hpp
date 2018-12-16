#ifndef IMAGE_H
#define IMAGE_H
#pragma once

#include <string>
#include <vector>
#include <glad/glad.h>

#include <nlohmann/json.hpp>

using Json = nlohmann::json;

namespace Engenie
{
class Image
{
public:
  std::string name;
  int width;
  int height;
  int component;
  std::vector<unsigned char> data;
  std::string mimeType;
  std::string uri;
  Json extras;

  void load(std::string path);
};
}; // namespace Engenie
#endif