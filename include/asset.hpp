#ifndef ASSET_H
#define ASSET_H
#pragma once

#include <string>

namespace Engenie
{
class Asset
{
public:
  Asset() {}
  Asset(std::string const &filePath) {}
  virtual void loadFromFile(std::string const &filePath) = 0;
};
}; // namespace Engenie

#endif