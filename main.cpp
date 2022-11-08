#include "Engine/Engine.hpp"

#include <iostream>

#define SDL_MAIN_HANDLED

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
    platformer_engine::Engine &engine = platformer_engine::Engine::GetInstance();

    engine.Init(SCREEN_WIDTH, SCREEN_HEIGHT, "Hallo", spic::Color::green());

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
