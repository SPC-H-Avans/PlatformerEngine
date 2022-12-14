#include <sstream>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/asio/buffers_iterator.hpp>
#include <thread>
#include "Networking/ClientNetworkManager.hpp"
#include "Exceptions/NotImplementedException.hpp"
#include "Debug.hpp"
#include "Engine/Engine.hpp"
#include "Utility/NetworkingBuffer.hpp"
#include "Networking/PackedObjects/PackedLoadedTextureInfo.hpp"

platformer_engine::ClientNetworkManager::ClientNetworkManager() {
    std::function<void(int clientId, const uint8_t *data, size_t dataLength)> removeLocalClientFromGame = [this](
            int clientId, const uint8_t *data, size_t dataLength) {
        RemoveLocalClientFromGame(data, dataLength);
    };
    _eventMap[NET_KICK_CLIENT] = removeLocalClientFromGame;

    std::function<void(int clientId, const uint8_t *data, size_t dataLength)> receivePing = [this](int clientId,
                                                                                                   const uint8_t *data,
                                                                                                   size_t dataLength) {
        spic::Debug::Log("Ping received from server!");
    };
    _eventMap[NET_REQUEST_PING] = receivePing;

    std::function<void(int clientId, const uint8_t *data, size_t dataLength)> kickClient = [this](int clientId,
                                                                                                  const uint8_t *data,
                                                                                                  size_t dataLength) {
        RemoveLocalClientFromGame(data, dataLength);
    };
    _eventMap[NET_KICK_CLIENT] = kickClient;

    std::function<void(int clientId, const uint8_t *data, size_t dataLength)> createGameObject = [this](int clientId,
                                                                                                        const uint8_t *data,
                                                                                                        size_t dataLength) {
        CreateGameObject(data, dataLength);
    };
    _eventMap[NET_CREATE_GAMEOBJECT] = createGameObject;

    std::function<void(int clientId, const uint8_t *data, size_t dataLength)> destroyGameObject = [this](int clientId,
                                                                                                         const uint8_t *data,
                                                                                                         size_t dataLength) {
        DestroyGameObject(data, dataLength);
    };
    _eventMap[NET_DESTROY_GAMEOBJECT] = destroyGameObject;

    std::function<void(int clientId, const uint8_t *data, size_t dataLength)> updateGameObjectTransform = [this](
            int clientId, const uint8_t *data, size_t dataLength) {
        UpdateGameObjectTransform(data, dataLength);
    };
    _eventMap[NET_UPDATE_GAMEOBJECT_TRANSFORM] = updateGameObjectTransform;

    std::function<void(int clientId, const uint8_t *data, size_t dataLength)> createScene = [this](int clientId,
                                                                                                   const uint8_t *data,
                                                                                                   size_t dataLength) {
        CreateScene(data, dataLength);
    };
    _eventMap[NET_CREATE_SCENE] = createScene;

    std::function<void(int clientId, const uint8_t *data, size_t dataLength)> loadedTextures = [this](int clientId,
                                                                                                      const uint8_t *data,
                                                                                                      size_t dataLength) {
        LoadedTextures(data, dataLength);
    };
    _eventMap[NET_LOADED_TEXTURES] = loadedTextures;

    std::function<void(int clientId, const uint8_t *data, size_t dataLength)> updateAnimation = [this](int clientId,
                                                                                                       const uint8_t *data,
                                                                                                       size_t dataLength) {
        UpdateAnimationFromServer(data, dataLength);
    };
    _eventMap[NET_UPDATE_ACTIVE_ANIMATION] = updateAnimation;
}

void platformer_engine::ClientNetworkManager::ConnectToServer(const std::string &ip, int port) {
    _networkingFacade.ConnectClient(ip, port, *this);
}

void platformer_engine::ClientNetworkManager::DisconnectFromServer() {
    _networkingFacade.DisconnectClientFromServer();
}

void platformer_engine::ClientNetworkManager::TravelToLevel(const std::string &levelName) {
    throw spic::NotImplementedException();
}

void platformer_engine::ClientNetworkManager::SendNetworkPackage(const void *data, size_t dataLength, bool reliable) {
    _networkingFacade.SendPacketToAllPeers(data, dataLength, reliable);
}

void platformer_engine::ClientNetworkManager::OnConnect(int clientId) {
    _localPlayerId = clientId;
    bool isPartyLeader = false; //TODO revise? b
    _connectionStatus = ConnectionStatus::WaitingForMap;
    if (_eventMap.contains(NET_ON_CONNECT)) {
        _eventMap[NET_ON_CONNECT](clientId, nullptr, 0);
    }
}

void platformer_engine::ClientNetworkManager::OnReceive(int clientId, const uint8_t *data, size_t dataLength) {
    if (data == nullptr || dataLength < 3)
        return;
    uint8_t versionMajor = data[0];
    uint8_t versionMinor = data[1];
    uint8_t messageType = data[2];
    if (versionMajor != NET_PROTOCOL_VERSION_MAJOR
        || versionMinor != NET_PROTOCOL_VERSION_MINOR) {
        //Handle bad networking version
        throw spic::NotImplementedException();
    }
    if (_eventMap.contains(messageType)) {
        _eventMap[messageType](clientId, data, dataLength);
    } else {
        spic::Debug::LogWarning(
                std::to_string(messageType) + " is not a registered event in the client network manager!");
    }
}

void
platformer_engine::ClientNetworkManager::RegisterEventHandler(int eventID,
                                                              std::function<void(int clientId, const uint8_t *data,
                                                                                 size_t dataLength)> functionToCall) {
    _eventMap[eventID] = functionToCall;
}

void platformer_engine::ClientNetworkManager::OnDisconnect(int clientId) {
    _localPlayerId = 0;
    _isPartyleader = false;
    _connectionStatus = ConnectionStatus::Disconnected;
    if (_eventMap.contains(NET_ON_DISCONNECT)) {
        _eventMap[NET_ON_DISCONNECT](clientId, nullptr, 0);
    }
}

void platformer_engine::ClientNetworkManager::RemoveLocalClientFromGame(const void *data,
                                                                        size_t dataLength) {
    if (_connectionStatus != ConnectionStatus::Connected) return;
    //Check if player exists
    auto pkg = NetPkgs::KickClient(0);
    std::memcpy(&pkg, data, dataLength);
    auto playerToRemove = pkg.clientId;
    //Perform remove logic
    Engine::GetInstance().GetActiveScene().RemoveObject(
            std::string(NET_PLAYER_PREFIX) + std::to_string(playerToRemove));
}

#pragma region HandlePacketsFromServer

void platformer_engine::ClientNetworkManager::CreateScene(const void *data, size_t length) {
    _connectionStatus = ConnectionStatus::InitializingMap;
    auto pkg = NetPkgs::CreateScene();
    memcpy(&pkg, data, length);
    spic::Scene scene;

    platformer_engine::NetworkingBuffer::ParseIncomingDataToObject<spic::Scene>(pkg._data, MAX_CREATE_SCENE_SIZE,
                                                                                scene);

    scene.ResetScene(); //Loads objects on instances.
    for (const auto &item: scene.GetAllObjects()) {
        item->FixGameObjectAfterDeserialize();
    }
    Engine::GetInstance().AddScene(scene);
    Engine::GetInstance().SetActiveScene(scene.GetSceneName());
    _connectionStatus = ConnectionStatus::Connected;
}

void platformer_engine::ClientNetworkManager::CreateGameObject(const void *data, size_t length) {
    if (_connectionStatus != ConnectionStatus::Connected) return;
    auto pkg = NetPkgs::CreateGameObject();
    memcpy(&pkg, data, length);
    spic::GameObject gameObject;

    platformer_engine::NetworkingBuffer::ParseIncomingDataToObject<spic::GameObject>(pkg._data,
                                                                                     MAX_CREATE_GAME_OBJECT_SIZE,
                                                                                     gameObject);

    gameObject.FixGameObjectAfterDeserialize();
    std::shared_ptr<GameObject> sharedPtr = std::make_shared<GameObject>(gameObject);
    try {
        Engine::GetInstance().GetActiveScene().AddObject(sharedPtr);
    } catch (const std::exception &ex) {
        spic::Debug::LogError("Something went wrong while trying to create a networked game object as client: " +
                              std::string(ex.what()));
    }
}

void platformer_engine::ClientNetworkManager::DestroyGameObject(const void *data, size_t length) {
    if (_connectionStatus != ConnectionStatus::Connected) return;
    auto pkg = NetPkgs::DestroyGameObject();
    memcpy(&pkg, data, length);
    auto gameObjectName = std::string(pkg._data);
    platformer_engine::Engine::GetInstance().GetActiveScene().RemoveObject(gameObjectName);
}

void platformer_engine::ClientNetworkManager::UpdateGameObjectTransform(const void *data, size_t length) {
    if (_connectionStatus != ConnectionStatus::Connected) return;
    auto pkg = NetPkgs::UpdateGameObjectTransform();
    memcpy(&pkg, data, length);
    spic::Transform transform;

    platformer_engine::NetworkingBuffer::ParseIncomingDataToObject<spic::Transform>(pkg._data,
                                                                                    MAX_UPDATE_TRANSFORM_SIZE,
                                                                                    transform);
    std::string gameObjectId = std::string(pkg._gameObjectId);

    auto gameObject = platformer_engine::Engine::GetInstance().GetActiveScene().GetObjectByName(gameObjectId);
    if (gameObject != nullptr) {
        gameObject->SetTransform(transform);
    }
}

void platformer_engine::ClientNetworkManager::LoadedTextures(const void *data, size_t length) {
    auto pkg = NetPkgs::LoadedTextures();
    memcpy(&pkg, data, length);
    PackedLoadedTextureInfo packedLoadedTextures;

    platformer_engine::NetworkingBuffer::ParseIncomingDataToObject<PackedLoadedTextureInfo>(pkg._data,
                                                                                            MAX_LOADED_TEXTURES_SIZE,
                                                                                            packedLoadedTextures);
    auto loadedTextures = packedLoadedTextures.GetLoadedTextureInfos();
    std::thread th1([loadedTextures] {
        for (LoadedTextureInfo item: loadedTextures) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            TextureManager::GetInstance().LoadTexture(item.GetTextureId(), item.GetTexturePath());
        }
    });
    th1.detach();

}

void platformer_engine::ClientNetworkManager::UpdateAnimationFromServer(const void *data, size_t length) {
    if (_connectionStatus != ConnectionStatus::Connected) return;
    auto pkg = NetPkgs::UpdateActiveAnimation();
    memcpy(&pkg, data, length);

    auto gameObject = platformer_engine::Engine::GetInstance().GetActiveScene().GetObjectByName(
            std::string(pkg._gameObjectId));
    if (gameObject == nullptr) {
        spic::Debug::LogWarning(
                "GameObject " + std::string(pkg._gameObjectId) + " does not exist in the client! Ignoring packet!");
        return;
    }
    auto playerAnimator = std::dynamic_pointer_cast<Animator>(gameObject->GetComponent<Animator>());
    if (playerAnimator == nullptr) {
        spic::Debug::LogWarning(
                "GameObject " + std::string(pkg._gameObjectId) +
                " does not have an animator in the client! Ignoring packet!");
        return;
    }
    playerAnimator->SetActiveAnimation(std::string(pkg._animationId));
}

#pragma endregion HandlePacketsFromClient

#pragma region DefaultClientEvents

void platformer_engine::ClientNetworkManager::UpdateNetworkedGameObjectTransform(const Transform &transform,
                                                                                 const std::string &gameObjectId) {
    if (_connectionStatus != ConnectionStatus::Connected) return;
    auto gameObject = spic::GameObject::Find(gameObjectId);

    if (gameObject == nullptr || gameObject->GetOwnerId() != GetLocalPlayerId()) return;

    boost::asio::streambuf buf;
    platformer_engine::NetworkingBuffer::ObjectToAsioBuffer<spic::Transform>(transform, buf);

    const auto *charPtr = buffer_cast<const char *>(buf.data());

    auto pkg = NetPkgs::UpdateGameObjectTransform(gameObjectId.c_str(), charPtr, buf.size());
    SendNetworkPackage(&pkg, sizeof(pkg), false);
}

void platformer_engine::ClientNetworkManager::InitializeMyClient(spic::GameObject &playerChar) {
    if (_connectionStatus != ConnectionStatus::Connected) return;
    playerChar.SetOwnerId(GetLocalPlayerId());
    boost::asio::streambuf buf;
    platformer_engine::NetworkingBuffer::ObjectToAsioBuffer<spic::GameObject>(playerChar, buf);

    const auto *charPtr = buffer_cast<const char *>(buf.data());

    auto pkg = NetPkgs::CreatePlayerCharacter(charPtr, buf.size());
    SendNetworkPackage(&pkg, sizeof(pkg), false);
}

void platformer_engine::ClientNetworkManager::UpdateActiveAnimation(const std::string &gameObjectId,
                                                                    const std::string &animationId) {
    if (_connectionStatus != ConnectionStatus::Connected) return;
    auto pkg = NetPkgs::UpdateActiveAnimation(gameObjectId.c_str(), animationId.c_str());
    SendNetworkPackage(&pkg, sizeof(pkg), false);
}

#pragma endregion DefaultClientEvents
