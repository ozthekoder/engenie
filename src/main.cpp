#include <stdlib.h>
#include "engine.hpp"
#include <glsl_ast.h>
using namespace Engenie;

int main(int argc, char *argv[])
{
    std::string configPath = PROJECT_SOURCE_DIR "/config/config.json";
    Engine engine;

    try
    {
        engine
            .loadOpenGL()
            .loadConfig(configPath)
            .startEventLoop();
    }
    catch (const char *msg)
    {
        std::cerr << msg << std::endl;
        std::string handle;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}