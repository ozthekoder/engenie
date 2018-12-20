#ifndef SCENE_H
#define SCENE_H

#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include "camera.hpp"
#include "viewport.hpp"
#include "model.hpp"
#include "font.hpp"
#include "lighting.h"
#include "glsl.hpp"
#include "shader.hpp"
#include "text.hpp"
#include "object.hpp"

using Json = nlohmann::json;

namespace Engenie
{
class Scene
{
public:
  std::string name;
  std::unordered_map<std::string, std::shared_ptr<Model>> models;
  std::unordered_map<std::string, std::shared_ptr<Font>> fonts;
  std::unordered_map<std::string, std::shared_ptr<GLSL>> shaders;
  std::vector<PointLight> pointLights;
  std::vector<Entity *> entities;
  DirectionalLight directionalLight;
  Camera camera;
  Viewport viewport;
  Scene() {}
  Scene(Json scene)
  {
    name = scene["name"];
    loadAssets(scene["assets"]);
    createEntities(scene);
    setupViewport(scene["viewport"]);
  }

  void setupViewport(Json v);
  void loadAssets(Json assets);
  void loadModels(Json models);
  void loadFonts(Json fonts);
  void createEntities(Json scene);
  void createLights(Json lighting);
  void createMapElements(Json map);
};
}; // namespace Engenie
#endif