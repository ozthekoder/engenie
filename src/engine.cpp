#include "engine.hpp"

namespace Engenie
{
Engine &Engine::loadConfig(std::string const &path)
{
    std::ifstream fileStream(path);
    auto src = std::string(std::istreambuf_iterator<char>(fileStream), std::istreambuf_iterator<char>());
    Json config = Json::parse(src);
    fileStream.close();

    for (Json::iterator it = config["scenes"].begin(); it != config["scenes"].end(); ++it)
    {
        sceneManager->addScene(sceneManager->loadScene(it.value()));
    }

    return createWindow(config);
}

Engine &Engine::createWindow(Json config)
{
    int width = config["window"]["width"];
    int height = config["window"]["height"];
    Json version = config["OpenGL"]["version"];
    std::string title = config["window"]["title"];
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = version["major"];
    settings.minorVersion = version["minor"];

    window = new sf::Window(sf::VideoMode(width, height), "Engenie v0.0", sf::Style::Default, settings);
    return *this;
}

Engine &Engine::loadOpenGL()
{
    gladLoadGL();
    return *this;
}

Engine &Engine::startEventLoop()
{
    // load resources, initialize the OpenGL states, ...

    // run the main loop
    events = true;
    while (events)
    {
        // handle events
        sf::Event event;
        while (window->pollEvent(event))
        {
            handleEvent(event);
        }

        // draw...

        // end the current frame (internally swaps the front and back buffers)
        window->display();
    }

    return *this;
}

void Engine::handleEvent(sf::Event const &event)
{
    if (event.type == sf::Event::Closed)
    {
        events = false;
    }
    else if (event.type == sf::Event::Resized)
    {
        glViewport(0, 0, event.size.width, event.size.height);
    }
}
} // namespace Engenie