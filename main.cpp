#include "Engine/Engine.hpp"
#include "Builder/SceneBuilder.hpp"
#include <iostream>
#include "Networking/ProtocolPackages.hpp"
#include "Sprite.hpp"
#include "Builder/GameObjectBuilder.hpp"

//BOOST_CLASS_EXPORT(spic::Component);

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


auto main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) -> int {
    platformer_engine::Engine &engine = platformer_engine::Engine::GetInstance();

    engine.Init(SCREEN_WIDTH, SCREEN_HEIGHT, "PlatFormer Engine Debug", spic::Color::Cyan());
    platformer_engine::SceneBuilder builder("Test Scene");
    auto scene = builder.GetScene();
    engine.AddScene(scene);
    engine.HostServer(scene.GetSceneName(), 10, 7779);
    engine.JoinServer("127.0.0.1", 7779);
    auto &clientManager = engine.GetClientNetworkManager();

    std::function<void(int clientId, const uint8_t *data, size_t dataLength)> onConnect = [&clientManager](int clientId, const uint8_t *data, size_t dataLength) {
        GameObjectBuilder gameobjectBuilder("Player" + std::to_string(clientManager.GetLocalPlayerId()));
        gameobjectBuilder.GetGameObject();

        auto gameObject = GameObject::Find("Player" + std::to_string(clientManager.GetLocalPlayerId()));
        if(gameObject == nullptr) return;
        clientManager.InitializeMyClient(*gameObject);
    };

    clientManager.RegisterEventHandler(NET_ON_CONNECT, onConnect);

    NetPkgs::Ping ping;
    engine.GetServerNetworkManager().SendUpdateToClients(&ping, sizeof(NetPkgs::Ping));
    engine.Start();

    std::cout << "Hello, World!" << std::endl;
    return 0;
}