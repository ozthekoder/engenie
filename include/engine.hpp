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

#include "scene_manager.hpp"

using Json = nlohmann::json;

namespace Engenie
{
class Engine
{
  public:
    Engine()
    {
        sceneManager = SceneManager();
    }

    Engine &loadConfig(std::string const &path);
    Engine &startEventLoop();
    Engine &startRenderLoop();
    sf::Window *createWindow(Json config);

  private:
    double lastFrame;
    sf::Window *window;
    SceneManager sceneManager;
};
}; // namespace Engenie
#endif