#ifndef GLSL_H
#define GLSL_H
#define NDEBUG

#include <string>
#include <fstream>
#include <iostream>
#include <glad/glad.h>
#include "asset.hpp"

namespace Engenie
{

enum ShaderType
{
    vertex = GL_VERTEX_SHADER,
    fragment = GL_FRAGMENT_SHADER,
    geometry = GL_GEOMETRY_SHADER,
    compute = GL_COMPUTE_SHADER,
    tesselation_control = GL_TESS_CONTROL_SHADER,
    tesselation_evaluation = GL_TESS_EVALUATION_SHADER,
    none = 0
};

class GLSL : public Asset
{
  public:
    ShaderType type;
    std::string source;
    GLuint shader;

    GLSL(ShaderType initType) : Asset()
    {
        shader = 0;
        type = initType;
    }

    GLSL(ShaderType initType, std::string src)
    {
        shader = 0;
        type = initType;
        source = src;
    }

    GLSL(std::string const &filePath) : Asset(filePath)
    {
        shader = 0;
        type = ShaderType::none;
        loadFromFile(filePath);
    }

    void loadFromFile(std::string const &filePath)
    {
        std::ifstream fd(filePath);
        source = std::string(std::istreambuf_iterator<char>(fd),
                             (std::istreambuf_iterator<char>()));
    }

    void addDirective(std::string const &varName, unsigned int value);
    void compile();
    void release();
};
}; // namespace Engenie

#endif