#ifndef ENTITY_H
#define ENTITY_H
#pragma once

#include "shader.hpp"
#include <nlohmann/json.hpp>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using Json = nlohmann::json;

namespace Engenie
{
class Entity
{
public:
  GLuint VAO, VBO, EBO;
  glm::mat4 transformation;

  Entity()
  {
    VAO = 0;
    VBO = 0;
    EBO = 0;
    transformation = glm::mat4(1.0f);
  }
  Entity(Json data) {}

  virtual void draw(Shader const &shader) = 0;
};
}; // namespace Engenie

#endif