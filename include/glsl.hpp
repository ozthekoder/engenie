#ifndef GLSL_H
#define GLSL_H
#define NDEBUG

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <glad/glad.h>
#include "koura.hpp"
#include "asset.hpp"
#include "model.hpp"

using namespace std::string_literals;

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
    std::stringstream source;
    GLuint shader;
    koura::context ctx;

    GLSL(ShaderType initType) : Asset()
    {
        shader = 0;
        type = initType;
    }

    GLSL(ShaderType initType, std::string src)
    {
        shader = 0;
        type = initType;
        source.str(src);
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
        source.str(std::string(std::istreambuf_iterator<char>(fd),
                               (std::istreambuf_iterator<char>())));
    }

    void compile();
    void release();

    GLSL &initializeContext();
    GLSL &setVersionDirective(size_t version);
    GLSL &addConstant(const std::string constName, size_t value);
    GLSL &addLayoutIdentifier(const std::string constName, const std::string type);
    GLSL &addInputVariable(const std::string varName, const std::string type);
    GLSL &addOutputVariable(const std::string varName, const std::string type);
    GLSL &addUniformVariable(const std::string varName, const std::string type);
    GLSL &generateSource();
    GLSL &generateVersionDirective();
    GLSL &generateLayoutIdentifiers();
    GLSL &generateInputVariables();
    GLSL &generateOutputVariables();
    GLSL &generateUniformVariables();

  private:
    koura::engine engine;
};

}; // namespace Engenie

#endif