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
#include "asset.hpp"

using Json = nlohmann::json;
namespace Engenie
{
class Shader : public Asset
{
  public:
    // Implement Custom Constructor and Destructor
    Shader() : Asset() { program = glCreateProgram(); }
    Shader(Json files) : Asset()
    {
        program = glCreateProgram();
        for (auto it = files.begin(); it != files.end(); ++it)
        {
            std::string filePath = it.value();
            const char *src = loadFile(PROJECT_SOURCE_DIR + filePath).c_str();
            GLuint shader = create(filePath);

            if (shader)
            {
                attach(shader, src);
            }
        }

        link();
    }
    ~Shader() { glDeleteProgram(program); }

    void activate();
    std::string loadFile(std::string const &filename);
    void attach(unsigned int shader, const char *source);
    GLuint create(std::string const &filename);
    GLuint get() { return program; }
    void link();
    void addDirective(std::string const &varName, unsigned int value, std::string &src);

    void loadFromFile(std::string const &filePath)
    {
    }
    // Wrap Calls to glUniform
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

  private:
    // Private Member Variables
    GLuint program;
    GLint status;
    GLint strLength;
};
}; // namespace Engenie

#endif