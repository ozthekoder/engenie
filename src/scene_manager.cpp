#include "scene_manager.hpp"

namespace Engenie
{

void SceneManager::addScene(Scene *scene)
{
    scenes[scene->name] = scene;
}

Scene *SceneManager::loadScene(Json config)
{
    return new Scene(config);
}

Scene *SceneManager::getScene(std::string const &sceneName)
{
    return scenes[sceneName];
}

void SceneManager::pushScene(Scene *scene)
{
    activeScene = scene;
    sceneState.push(scene);
}

Scene *SceneManager::popScene()
{
    Scene *top = sceneState.top();
    sceneState.pop();
    return top;
}

Scene *SceneManager::getActiveScene()
{
    return activeScene;
}

}; // namespace Engenie