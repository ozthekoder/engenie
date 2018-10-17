#ifndef LIGHTING_H
#define LIGHTING_H
#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Engenie
{
struct DirectionalLight
{
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    glm::vec3 direction;
};

struct PointLight
{
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    glm::vec3 position;
    float constant;
    float linear;
    float quadratic;
};

struct SpotLight
{
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    glm::vec3 direction;
    glm::vec3 position;
    float constant;
    float linear;
    float quadratic;
    float cutOff;
    float outerCutOff;
};
}; // namespace Engenie

#endif