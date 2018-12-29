#include "shader.hpp"

// Define Namespace
namespace Engenie
{

void Shader::activate()
{
    glUseProgram(program);
}

void Shader::bind(GLuint location, GLuint value) { glUniform1i(location, value); }
void Shader::bind(GLuint location, GLfloat value) { glUniform1f(location, value); }
void Shader::bind(GLuint location, glm::mat4 const &matrix) { glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix)); }
void Shader::bind(GLuint location, glm::vec4 const &vector) { glUniform4f(location, vector.x, vector.y, vector.z, vector.w); }
void Shader::bind(GLuint location, glm::vec3 const &vector) { glUniform3f(location, vector.x, vector.y, vector.z); }

void Shader::attach(GLSL &shader)
{
    shader.compile();
    sources.push_back(&shader);
    shader.release();
}

void Shader::link()
{
    GLint status;
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status > 0)
    {
        GLint logLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
        std::unique_ptr<char[]> buffer(new char[logLength]);
        glGetProgramInfoLog(program, logLength, nullptr, buffer.get());
        fprintf(stderr, "%s", buffer.get());
    }
    assert(status > 0);
}

void Shader::generateGLSL()
{
}

} // namespace Engenie