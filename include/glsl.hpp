#ifndef GLSL_H
#define GLSL_H
#include <string>
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
    tesselation_evaluation = GL_TESS_EVALUATION_SHADER
};

class GLSL : public Asset
{
  public:
    ShaderType type;
    std::string source;

    GLSL(ShaderType initType) : Asset()
    {
        type = initType;
    }

    GLSL(ShaderType initType, std::string src)
    {
        type = initType;
        source = src;
    }

    GLSL(std::string const &filePath) : Asset(filePath)
    {
        loadFromFile(FilePath);
    }

    void loadFromFile(std::string const &filePath)
    {
        std::ifstream fd(FilePath);
        source = std::string(std::istreambuf_iterator<char>(fd),
                             (std::istreambuf_iterator<char>()));
    }

    GLuint create();
};
}; // namespace Engenie

#endif