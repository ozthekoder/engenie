#ifndef SHADER_H
#define SHADER_H
#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "asset.hpp"

namespace Engenie
{
class Shader : public Asset
{
  public:
    // Implement Custom Constructor and Destructor
    Shader() { mProgram = glCreateProgram(); }
    ~Shader() { glDeleteProgram(mProgram); }

    // Public Member Functions
    Shader *init();
    Shader *activate();
    std::string loadFile(std::string const &filename);
    Shader *attach(unsigned int shader, const char *source);
    GLuint create(std::string const &filename);
    GLuint get() { return mProgram; }
    Shader *link();
    Shader *addDirective(std::string const &varName, unsigned int value, std::string &src);

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
    Shader *bind(std::string const &name, T &&value)
    {
        int location = glGetUniformLocation(mProgram, name.c_str());
        if (location == -1)
            fprintf(stderr, "Missing Uniform: %s\n", name.c_str());
        else
            bind(location, std::forward<T>(value));
        return this;
    }

  private:
    // Private Member Variables
    GLuint mProgram;
    GLint mStatus;
    GLint mLength;
};
}; // namespace Engenie

#endif