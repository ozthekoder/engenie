#ifndef SHADER_H
#define SHADER_H
#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

#include "glsl.hpp"

using Json = nlohmann::json;
namespace Engenie
{
class Shader
{
  public:
    GLuint program;
    std::vector<GLSL *> sources;

    Shader() { program = glCreateProgram(); }

    ~Shader() { glDeleteProgram(program); }

    void activate();
    void attach(GLSL &shader);
    GLuint get() { return program; }
    void link();

    void bind(GLuint location, GLuint value);
    void bind(GLuint location, GLfloat value);
    void bind(GLuint location, glm::mat4 const &matrix);
    void bind(GLuint location, glm::vec4 const &vector);
    void bind(GLuint location, glm::vec3 const &vector);

    template <typename T>
    void bind(std::string const &name, T &&value)
    {
        int location = glGetUniformLocation(program, name.c_str());
        if (location == -1)
            fprintf(stderr, "Missing Uniform: %s\n", name.c_str());
        else
            bind(location, std::forward<T>(value));
    }
};
}; // namespace Engenie

#endif