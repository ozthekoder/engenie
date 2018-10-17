#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#pragma once

#include <string>
#include <stack>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <nlohmann/json.hpp>

#include "scene.hpp"

using Json = nlohmann::json;

namespace Engenie
{
class SceneManager
{
  public:
    Scene *loadScene(Json config);
    void addScene(Scene *scene);
    Scene *getScene(std::string const &sceneName);
    void pushScene(Scene *scene);
    Scene *popScene();
    Scene *getActiveScene();

  private:
    std::stack<Scene *> sceneState;
    std::unordered_map<std::string, Scene *> scenes;
    Scene *activeScene;
};
}; // namespace Engenie
#endif