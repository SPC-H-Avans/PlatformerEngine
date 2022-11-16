#include "Engine/Engine.hpp"
#include "Builder/GameObjectBuilder.hpp"
#include "BehaviourScript.hpp"
#include "RigidBody.hpp"

#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


auto main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) -> int {
    platformer_engine::Engine &engine = platformer_engine::Engine::GetInstance();
    
    engine.Init(SCREEN_WIDTH, SCREEN_HEIGHT, "Hallo", spic::Color::Green());

    std::cout << "Hello, World!" << std::endl;
    return 0;
}


