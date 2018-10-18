#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <glad/glad.h>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <nlohmann/json.hpp>

#include "engine.hpp"

using Json = nlohmann::json;

int main(int argc, char *argv[])
{
    gladLoadGL();
    sf::Window window(sf::VideoMode(800, 600), "Engenie v0.0");

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseMoved)
            {
                std::cout << "new mouse x: " << event.mouseMove.x << std::endl;
                std::cout << "new mouse y: " << event.mouseMove.y << std::endl;
            }
        }
    }
    // glEnable(GL_CULL_FACE);
    // sf::SoundBuffer buffer;
    // Json foo = Json::object();
    // if (buffer.loadFromFile("C:\\gitlab\\engenie\\switch1.ogg"))
    // {
    //     sf::Sound sound(buffer);
    //     for (int i = 0; i < 100; i++)
    //     {
    //         sound.play();
    //         std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    //     }
    // }
    return 0;
}