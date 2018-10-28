#include "scene.hpp"

namespace Engenie
{

void Scene::setupViewport(Json v)
{
    viewport = Viewport(
        GLfloat(v["near"]),
        GLfloat(v["far"]),
        GLfloat(v["fov"]),
        v["projection"]);
}
void Scene::loadAssets(Json assets)
{
    loadModels(assets["models"]);
    loadFonts(assets["fonts"]);
    loadShaders(assets["shaders"]);
}

void Scene::loadModels(Json models)
{
    for (Json::iterator it = models.begin(); it != models.end(); ++it)
    {
        std::string path = it.value();
        assets.insert_or_assign(it.key(), new Model(PROJECT_SOURCE_DIR + path));
    }
}

void Scene::loadFonts(Json fonts)
{
    for (Json::iterator it = fonts.begin(); it != fonts.end(); ++it)
    {
        std::string path = it.value();
        assets.insert_or_assign(it.key(), new Font(PROJECT_SOURCE_DIR + path));
    }
}

void Scene::loadShaders(Json shaders)
{
    for (Json::iterator it = shaders.begin(); it != shaders.end(); ++it)
    {
        Json files = it.value();
        assets.insert_or_assign(it.key(), new Shader(files));
    }
}

void Scene::createEntities(Json entities)
{
    createLights(entities["lights"]);
    createObjects(entities["objects"]);
    createTexts(entities["texts"]);
}

void Scene::createLights(Json lights)
{
    for (Json data : lights["point"])
    {
        glm::vec3 ambient = glm::vec3(data["ambient"][0], data["ambient"][1], data["ambient"][2]);
        glm::vec3 diffuse = glm::vec3(data["diffuse"][0], data["diffuse"][1], data["diffuse"][2]);
        glm::vec3 specular = glm::vec3(data["specular"][0], data["specular"][1], data["specular"][2]);
        glm::vec3 position = glm::vec3(data["position"][0], data["position"][1], data["position"][2]);
        float constant = data["constant"];
        float linear = data["linear"];
        float quadratic = data["quadratic"];
        PointLight p = {ambient, diffuse, specular, position, constant, linear, quadratic};
        pointLights.push_back(p);
    }

    if (lights["directional"].size() > 0)
    {
        Json data = lights["directional"];
        glm::vec3 ambient = glm::vec3(data["ambient"][0], data["ambient"][1], data["ambient"][2]);
        glm::vec3 diffuse = glm::vec3(data["diffuse"][0], data["diffuse"][1], data["diffuse"][2]);
        glm::vec3 specular = glm::vec3(data["specular"][0], data["specular"][1], data["specular"][2]);
        glm::vec3 direction = glm::vec3(data["direction"][0], data["direction"][1], data["direction"][2]);
        directionalLight = {ambient, diffuse, specular, direction};
    }
}

void Scene::createObjects(Json objects)
{
    for (Json s : objects)
    {
        entities.push_back((new Object(s)));
    }
}

void Scene::createTexts(Json texts)
{
    for (Json s : texts)
    {
        entities.push_back(new Text(s));
    }
}

} // namespace Engenie