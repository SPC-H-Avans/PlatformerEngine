#include "Engine/Engine.hpp"
#include "Builder/SceneBuilder.hpp"
#include <iostream>
#include <boost/asio/streambuf.hpp>
#include "Networking/ProtocolPackages.hpp"
#include "BehaviourScript.hpp"
#include "Behaviour/CollisionBehaviour.hpp"
#include "Builder/GameObjectBuilder.hpp"
#include "Sprite.hpp"
#include "Audio/AudioManager.hpp"
#include "Builder/GameObjectBuilder.hpp"
#include "Utility/NetworkingBuffer.hpp"

//BOOST_CLASS_EXPORT(spic::Component);

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


auto main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) -> int {
    platformer_engine::Engine &engine = platformer_engine::Engine::GetInstance();

    engine.Init(SCREEN_WIDTH, SCREEN_HEIGHT, "PlatFormer Engine Debug", spic::Color::Cyan(), false);

    platformer_engine::SceneBuilder builder("Test Scene");

    std::shared_ptr<Camera> camera = std::make_shared<Camera>("camera1", "camera", spic::Color::Cyan(), SCREEN_WIDTH,
                                                              SCREEN_HEIGHT);

    auto scene = builder.GetScene();

    GameObjectBuilder gameObjectBuilder{"speler"};

//    auto playerBody = PlayerRigidBody();
//    gameObjectBuilder.AddRigidBody(playerBody);

    auto testCollider = BoxCollider();
    gameObjectBuilder.AddCollider(testCollider);

    auto gameObject = gameObjectBuilder.GetGameObject();

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
    scene.AddObject(*gameObject);

    camera->SetTarget(*gameObject);

    scene.AddCamera(*camera);

    engine.AddScene(scene);

    engine.HostServer(scene.GetSceneName(), 10, 7779);
    //engine.JoinServer("127.0.0.1", 7779); 

    NetPkgs::Ping ping;
    engine.GetServerNetworkManager().SendUpdateToClients(&ping, sizeof(NetPkgs::Ping));

    //Save and Load data to a local file
    engine.GetDataManager().SaveData<Scene>("Key", scene);
    std::optional<Scene> object = engine.GetDataManager().LoadData<Scene>("Key");


    engine.Start();

    std::cout << "Hello, World!" << std::endl;
    return 0;

}
