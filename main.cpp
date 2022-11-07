#include "library.h"
#include "Engine/Engine.h"

#include <iostream>

int main() {
    PlatformerEngine::Engine &engine = PlatformerEngine::Engine::getInstance();

    engine.Init(100, 100, "Hallo", spic::Color::green());

    while (engine.isRunning) {

    }

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
