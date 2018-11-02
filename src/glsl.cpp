#include "glsl.hpp"

namespace Engenie
{
void GLSL::compile()
{
    if (type != ShaderType::none && shader == 0)
    {
        GLint status;
        shader = glCreateShader(type);
        const char *src = source.c_str();
        glShaderSource(shader, 1, &src, nullptr);
        glCompileShader(shader);
        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

        if (status > 0)
        {
            GLint logLength;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
            std::unique_ptr<char[]> buffer(new char[logLength]);
            glGetShaderInfoLog(shader, logLength, nullptr, buffer.get());
            fprintf(stderr, "%s", buffer.get());
        }
    }
}

void GLSL::release()
{
    if (shader > 0)
    {
        glDeleteShader(shader);
    }
}

void GLSL::addDirective(std::string const &varName, unsigned int value)
{
    std::size_t found = source.find("\n");

    std::string addition = "\n#define " + varName + " " + std::to_string(value) + "\n\n";
    source.insert(found, addition);
}

} // namespace Engenie