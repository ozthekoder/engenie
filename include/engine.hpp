#ifndef ENGINE_H
#define ENGINE_H

#pragma once

#include <string>
#include <stack>
#include <fstream>
#include <iostream>
#include <unordered_map>

#include <SFML/Window.hpp>
#include <nlohmann/json.hpp>
#include <glad/glad.h>
#include "scene_manager.hpp"

using Json = nlohmann::json;

namespace Engenie
{
class Engine
{
public:
  Engine()
  {
    events = false;
    render = false;
    sceneManager = new SceneManager();
  }

  ~Engine()
  {
    delete window;
    delete sceneManager;
  }

  Engine &loadConfig(std::string const &path);
  Engine &startEventLoop();
  Engine &startRenderLoop();
  Engine &createWindow(Json config);
  Engine &loadOpenGL();
  void handleEvent(sf::Event const &event);

private:
  bool events, render;
  sf::Window *window;
  SceneManager *sceneManager;
};
}; // namespace Engenie
#endif