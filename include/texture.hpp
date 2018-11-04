#ifndef TEXTURE_H
#define TEXTURE_H
#pragma once

#include "image.hpp"
namespace Engenie
{
struct Sampler
{
    std::string name;
    GLuint minFilter;
    GLuint magFilter;
    GLuint wrapS;
    GLuint wrapT;
};
class Texture
{
  public:
    std::string name;
    Image source;
    Sampler sampler;

    Texture() {}
    Texture(Json props)
    {
    }
};
}; // namespace Engenie
#endif