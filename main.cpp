#include "library.h"
#include "Engine/Engine.hpp"

#include <iostream>

#define SDL_MAIN_HANDLED


int main(int argc, char *argv[]) {
    PlatformerEngine::Engine &engine = PlatformerEngine::Engine::GetInstance();

    engine.Init(800, 800, "Hallo", spic::Color::green());

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
