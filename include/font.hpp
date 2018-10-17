#ifndef FONT_H
#define FONT_H
#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "asset.hpp"

namespace Engenie
{
class Font : public Asset
{
  public:
    Font() : Asset() {}

    Font(std::string const &filePath) : Asset(filePath)
    {
        loadFromFile(filePath);
    }

    void loadFromFile(std::string const &filePath)
    {
        font->loadFromFile(filePath);
    }

  private:
    sf::Font *font;
};
}; // namespace Engenie

#endif