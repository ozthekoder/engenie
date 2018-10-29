#ifndef ASSET_H
#define ASSET_H
#pragma once
const char pathSeparator = '/';
#include <string>

namespace Engenie
{
class Asset
{
public:
  std::string directory;
  Asset() {}
  Asset(std::string const &filePath)
  {
    size_t last = filePath.find_last_of(pathSeparator);
    directory = filePath.substr(0, last + 1);
  }
  virtual void loadFromFile(std::string const &filePath) = 0;
};
}; // namespace Engenie

#endif