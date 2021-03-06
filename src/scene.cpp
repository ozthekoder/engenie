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

void Scene::loadAssets(Json asts)
{
    for (Json::iterator it = asts.begin(); it != asts.end(); ++it)
    {
        std::string assetType = it.key();

        Json assetsOfType = it.value();
        if (assetType == "models")
        {
            loadModels(assetsOfType);
        }
        else if (assetType == "fonts")
        {
            loadFonts(assetsOfType);
        }
    }
}

void Scene::loadModels(Json mdls)
{
    for (Json::iterator it = mdls.begin(); it != mdls.end(); ++it)
    {
        std::string path = it.value();
        models.insert_or_assign(it.key(), std::make_shared<Model>(PROJECT_SOURCE_DIR + path));
    }
}

void Scene::loadFonts(Json fnts)
{
    for (Json::iterator it = fnts.begin(); it != fnts.end(); ++it)
    {
        std::string path = it.value();
        fonts.insert_or_assign(it.key(), std::make_shared<Font>(PROJECT_SOURCE_DIR + path));
    }
}

void Scene::createEntities(Json scene)
{
    createLights(scene["lighting"]);
    createMapElements(scene["map"]);
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

void Scene::createMapElements(Json map)
{
    for (Json s : map)
    {
        std::string type = s["type"];
        if (type == std::string("object"))
        {
            Object *obj = new Object();
            std::string asset = s["asset"];
            obj->model = models[asset];

            entities.push_back((obj));
        }
        else if (type == std::string("text"))
        {
            entities.push_back(new Text(s));
        }
    }
}

} // namespace Engenie