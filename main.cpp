#include "Engine/Engine.hpp"
#include "Builder/SceneBuilder.hpp"

#include <iostream>
#include "Sprite.hpp"
#include "Builder/GameObjectBuilder.hpp"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


auto main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) -> int {
    platformer_engine::Engine &engine = platformer_engine::Engine::GetInstance();

    engine.Init(SCREEN_WIDTH, SCREEN_HEIGHT, "PlatFormer Engine Debug", spic::Color::Cyan());
    engine.Start();

    std::cout << "Hello, World!" << std::endl;
    return 0;
}


