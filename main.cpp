#include "Engine/Engine.hpp"
#include "Builder/SceneBuilder.hpp"

#include <iostream>
#include "Sprite.hpp"
#include "Builder/GameObjectBuilder.hpp"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


auto main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) -> int {
    platformer_engine::Engine &engine = platformer_engine::Engine::GetInstance();

    engine.Init(SCREEN_WIDTH, SCREEN_HEIGHT, "PlatFormer Engine Debug", spic::Color::Green());

    platformer_engine::TextureManager::GetInstance().LoadTexture("mario_Jump", "C:\\Users\\jhpar\\Documents\\GitHub\\MarioGame\\resources\\Sprites\\Bowser\\Idle.png");
    GameObjectBuilder gameObjectBuilder {"speler"};
    auto animatedSprite = std::make_shared<platformer_engine::AnimatedSprite>("mario_Jump", 1, 1, 24, 24, 1, 1, 10, platformer_engine::FLIP_NONE, Color::Transparent(), 4.0);
    gameObjectBuilder.AddAnimator(animatedSprite);
    auto gameObject = gameObjectBuilder.GetGameObject();
    auto transform = Transform();
    transform.position = Point();
    transform.rotation = 0;
    transform.position.x = 100;
    transform.position.y = 100;
    gameObject->SetTransform(transform);
    
    engine.Start();

    std::cout << "Hello, World!" << std::endl;
    return 0;
}


