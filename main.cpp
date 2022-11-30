#include "Engine/Engine.hpp"
#include "Builder/SceneBuilder.hpp"
#include <iostream>
#include "Networking/ProtocolPackages.hpp"
#include "BehaviourScript.hpp"
#include "Behaviour/CollisionBehaviour.hpp"
#include "Physics/MarioRigidBody.hpp"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


auto main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) -> int {
    platformer_engine::Engine &engine = platformer_engine::Engine::GetInstance();

    engine.Init(SCREEN_WIDTH, SCREEN_HEIGHT, "PlatFormer Engine Debug", spic::Color::Cyan());

    platformer_engine::SceneBuilder builder("Test Scene");

    std::shared_ptr<Camera> camera = std::make_shared<Camera>("camera1", "camera", spic::Color::Cyan(), SCREEN_WIDTH, SCREEN_HEIGHT);

    auto scene = builder.GetScene();


    GameObjectBuilder gameObjectBuilder{"speler"};

//    platformer_engine::TextureManager::GetInstance().LoadTexture("mario_Jump", "D:/Avans/Jaar 4/SPC Project/assets/Walk.png");
    // Add animating sprite
//    auto sprite = std::make_shared<platformer_engine::AnimatedSprite>("mario_Jump", 1, 1, 24, 24, 3, 100, 1,
//                                                                      platformer_engine::FLIP_NONE,
//                                                                      Color::Transparent(), 1.0);
//    gameObjectBuilder.AddAnimator(sprite);
    auto gameObject = gameObjectBuilder.GetGameObject();

    // todo: Make this using the GameObjectBuilder
    // Add the MarioPhysics rigidbody
    auto marioBody = MarioRigidBody();
    marioBody.BodyType(spic::BodyType::dynamicBody);
    gameObject->AddComponent<RigidBody>(std::make_shared<MarioRigidBody>(marioBody));

    // Add a BoxCollider
    auto collider = BoxCollider();
    collider.Width(24);
    collider.Height(24);
    gameObject->AddComponent<BoxCollider>(std::make_shared<BoxCollider>(collider));

    // Add collision behaviourscript
    gameObject->AddComponent<BehaviourScript>(std::make_shared<platformer_engine::CollisionBehaviour>());

    auto transform = Transform();
    transform.position = Point();
    transform.rotation = 0;
    transform.position.x = 200;
    transform.position.y = 300;
    transform.scale = 1.0;
    gameObject->SetTransform(transform);
    scene.AddObject(gameObject);

    camera->SetTarget(*gameObject);

    scene.AddCamera(camera);

    engine.AddScene(scene);


    engine.HostServer(scene.GetSceneName(), 10, 7779);
    engine.JoinServer("127.0.0.1", 7779);
    NetPkgs::Ping ping;
    engine.GetServerNetworkManager().SendUpdateToClients(&ping, sizeof(NetPkgs::Ping));

//    engine.GetActiveScene().ImportLevel("map1", "D:/Avans/Jaar 4/SPC Project/assets/Mario1/","map1.tmx");

    engine.Start();

    std::cout << "Hello, World!" << std::endl;
    return 0;
}


x