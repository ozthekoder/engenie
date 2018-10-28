#ifndef VIEWPORT_H
#define VIEWPORT_H

#pragma once

#define PERSPECTIVE_PROJECTION 0
#define ORTHOGRAPHIC_PROJECTION 1

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <SFML/Window.hpp>

namespace Engenie
{
class Viewport
{
public:
  Viewport()
  {
    width = 0;
    height = 0;
    nearZ = 0.0f;
    farZ = 0.0f;
    fov = 0.0f;
    projectionType = 0;
  }

  Viewport(GLfloat initNear, GLfloat initFar, GLfloat initFov, unsigned int initProjectionType = 0)
  {
    nearZ = initNear;
    farZ = initFar;
    fov = initFov;
    projectionType = initProjectionType;
  }

  void init(sf::Window *window);
  glm::mat4 getProjectionMatrix();
  void setSize(int w, int h);

private:
  GLfloat fov, nearZ, farZ;
  int width, height, projectionType;
};
}; // namespace Engenie

#endif