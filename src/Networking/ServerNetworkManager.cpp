
#include "Networking/ServerNetworkManager.hpp"
#include "Exceptions/NotImplementedException.hpp"
#include "Utility/NetworkingBuffer.hpp"
#include "Engine/Engine.hpp"
#include "Builder/GameObjectBuilder.hpp"
#include "Networking/PackedObjects/PackedLoadedTextureInfo.hpp"
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/asio.hpp>

platformer_engine::ServerNetworkManager::ServerNetworkManager(spic::Scene &scene, int playerLimit, int port) : _scene(
        scene), _playerLimit(playerLimit) {
    _networkingFacade.StartServer(port, playerLimit);
    for (auto &item: _scene.GetAllObjects()) {
        item->SetOwnerId(_networkingFacade.GetMyPeerId());
    }

    const std::function<void(int clientId, const uint8_t *data, size_t dataLength)> receivePing = [this](int clientId,
                                                                                                         const uint8_t *data,
                                                                                                         size_t dataLength) {
        spic::Debug::Log("Ping received from server!");
    };
    _eventMap[NET_REQUEST_PING] = receivePing;


    const std::function<void(int clientId, const uint8_t *data,
                             size_t dataLength)> handleGameObjectTransformEventFromClient = [this](int clientId,
                                                                                                   const uint8_t *data,
                                                                                                   size_t dataLength) {
        HandleGameObjectTransformEventFromClient(clientId, data, dataLength);
    };
    _eventMap[NET_UPDATE_GAMEOBJECT_TRANSFORM] = handleGameObjectTransformEventFromClient;

    const std::function<void(int clientId, const uint8_t *data,
                             size_t dataLength)> handleCreateCharacterFromClient = [this](int clientId,
                                                                                          const uint8_t *data,
                                                                                          size_t dataLength) {
        HandleCreateCharacterFromClient(clientId, data, dataLength);
    };
    _eventMap[NET_SEND_CHARACTER_TO_SERVER] = handleCreateCharacterFromClient;

    const std::function<void(int clientId, const uint8_t *data,
                             size_t dataLength)> handleUpdateAnimationFromClient = [this](int clientId,
                                                                                          const uint8_t *data,
                                                                                          size_t dataLength) {
        HandleUpdateAnimationFromClient(clientId, data, dataLength);
    };
    _eventMap[NET_UPDATE_ACTIVE_ANIMATION] = handleUpdateAnimationFromClient;

}

void platformer_engine::ServerNetworkManager::SendUpdateToClients(const void *data, size_t dataLength, bool reliable) {
    _networkingFacade.SendPacketToAllPeers(data, dataLength, reliable);
}

void
platformer_engine::ServerNetworkManager::SendUpdateToClientsExcept(const std::vector<int> &clientIds, const void *data,
                                                                   size_t dataLength,
                                                                   bool reliable) {
    _networkingFacade.SendPacketToAllPeersExcept(clientIds, data, dataLength, reliable);
}

void platformer_engine::ServerNetworkManager::SendUpdateToClient(int clientId, const void *data, size_t dataLength,
                                                                 bool reliable) {
    _networkingFacade.SendPacketToPeer(clientId, data, dataLength, reliable);
}

const int TIME_OUT = 500;

void platformer_engine::ServerNetworkManager::InitializeClient(const Client &client) {
    CreateNetworkedSceneForClient(client.GetClientId(), Engine::GetInstance().GetActiveScene());
    std::this_thread::sleep_for(std::chrono::milliseconds(TIME_OUT));
    SendLoadedTexturesToClient(client.GetClientId());
}

void platformer_engine::ServerNetworkManager::SendLoadedTexturesToClient(int clientId) {
    boost::asio::streambuf buf;
    PackedLoadedTextureInfo packedLoadedTextureInfo;
    packedLoadedTextureInfo.LoadTextures();
    platformer_engine::NetworkingBuffer::ObjectToAsioBuffer<PackedLoadedTextureInfo>(
            packedLoadedTextureInfo, buf);

    const auto *charPtr = buffer_cast<const char *>(buf.data());

    auto pkg = NetPkgs::LoadedTextures(charPtr, buf.size());
    SendUpdateToClient(clientId, &pkg, sizeof(pkg), true);
}

void platformer_engine::ServerNetworkManager::OnConnect(int clientId) {
    Client client{clientId};
    Clients.push_back(client);
    spic::Debug::Log(
            "Currently hosting a game for " + std::to_string(Clients.size()) + "/" + std::to_string(_playerLimit) +
            " clients!");
    InitializeClient(client);
    if (_eventMap.contains(NET_ON_CONNECT)) {
        _eventMap[NET_ON_CONNECT](clientId, nullptr, 0);
    }
}

void platformer_engine::ServerNetworkManager::OnReceive(int clientId, const uint8_t *data, size_t dataLength) {
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
                std::to_string(messageType) + " is not a registered event in the server network manager!");
    }
}

void platformer_engine::ServerNetworkManager::OnDisconnect(int clientId) {
    //Remove client from list
    std::erase_if(Clients, [clientId](const Client &client) { return client.GetClientId() == clientId; });
    spic::Debug::Log(
            "Currently hosting a game for " + std::to_string(Clients.size()) + "/" + std::to_string(_playerLimit) +
            " clients!");
    NetPkgs::KickClient kickClient(clientId);
    Engine::GetInstance().GetActiveScene().RemoveObject(
            std::string(NET_PLAYER_PREFIX) + std::to_string(clientId));

    _networkingFacade.SendPacketToAllPeers(&kickClient, sizeof(kickClient));
    if (_eventMap.contains(NET_ON_DISCONNECT)) {
        _eventMap[NET_ON_DISCONNECT](clientId, nullptr, 0);
    }
}

void platformer_engine::ServerNetworkManager::Events() {
    _networkingFacade.HandleEvents(*this);
}

#pragma region DefaultServerEvents

void platformer_engine::ServerNetworkManager::CreateNetworkedSceneForClient(int clientId, const spic::Scene &scene) {
    boost::asio::streambuf buf;
    platformer_engine::NetworkingBuffer::ObjectToAsioBuffer<spic::Scene>(scene, buf);

    const auto *charPtr = buffer_cast<const char *>(buf.data());

    auto pkg = NetPkgs::CreateScene(charPtr, buf.size());
    SendUpdateToClient(clientId, &pkg, sizeof(pkg), true);
}

void platformer_engine::ServerNetworkManager::CreateNetworkedScene(const spic::Scene &scene) {
    boost::asio::streambuf buf;
    platformer_engine::NetworkingBuffer::ObjectToAsioBuffer<spic::Scene>(scene, buf);

    const auto *charPtr = buffer_cast<const char *>(buf.data());

    auto pkg = NetPkgs::CreateScene(charPtr, buf.size());
    SendUpdateToClients(&pkg, sizeof(pkg), true);
}

void platformer_engine::ServerNetworkManager::CreateNetworkedGameObject(const spic::GameObject &gameObjectToCreate) {
    boost::asio::streambuf buf;
    platformer_engine::NetworkingBuffer::ObjectToAsioBuffer<spic::GameObject>(gameObjectToCreate, buf);

    const auto *charPtr = buffer_cast<const char *>(buf.data());

    auto pkg = NetPkgs::CreateGameObject(charPtr, buf.size());
    SendUpdateToClients(&pkg, sizeof(pkg), true);
}

void platformer_engine::ServerNetworkManager::UpdateNetworkedGameObjectTransform(const spic::Transform &transform,
                                                                                 const std::string &gameObjectId) {
    boost::asio::streambuf buf;
    platformer_engine::NetworkingBuffer::ObjectToAsioBuffer<spic::Transform>(transform, buf);

    const auto *charPtr = buffer_cast<const char *>(buf.data());

    auto pkg = NetPkgs::UpdateGameObjectTransform(gameObjectId.c_str(), charPtr, buf.size());
    SendUpdateToClients(&pkg, sizeof(pkg), false);
}

void platformer_engine::ServerNetworkManager::DestroyNetworkedGameObject(const std::string &gameObjectId) {
    auto pkg = NetPkgs::DestroyGameObject(gameObjectId.c_str());
    SendUpdateToClients(&pkg, sizeof(pkg), true);
}

void platformer_engine::ServerNetworkManager::CreateNetworkedPlayerCharacter(int clientId,
                                                                             const GameObject &gameObjectToCreate) {
    boost::asio::streambuf buf;
    platformer_engine::NetworkingBuffer::ObjectToAsioBuffer<spic::GameObject>(gameObjectToCreate, buf);

    const auto *charPtr = buffer_cast<const char *>(buf.data());

    auto pkg = NetPkgs::CreateGameObject(charPtr, buf.size());
    std::vector<int> clientIdsToExcept;
    //clientIdsToExcept.push_back(Engine::GetInstance().GetClientNetworkManager().GetLocalPlayerId());
    clientIdsToExcept.push_back(clientId);
    SendUpdateToClientsExcept(
            clientIdsToExcept, &pkg,
            sizeof(pkg), true);
}

void platformer_engine::ServerNetworkManager::UpdateAnimation(int clientId, const std::string &gameObjectId,
                                                              const std::string &animationId) {
    auto pkg = NetPkgs::UpdateActiveAnimation(gameObjectId.c_str(), animationId.c_str());
    std::vector<int> clientIdsToExcept;
    clientIdsToExcept.push_back(clientId);
    SendUpdateToClientsExcept(
            clientIdsToExcept, &pkg,
            sizeof(pkg), true);
}

#pragma endregion DefaultServerEvents

#pragma region HandlePacketsFromClient

void
platformer_engine::ServerNetworkManager::HandleGameObjectTransformEventFromClient(int clientId, const void *data,
                                                                                  size_t length) {
    auto pkg = NetPkgs::UpdateGameObjectTransform();
    memcpy(&pkg, data, length);
    spic::Transform transform;

    platformer_engine::NetworkingBuffer::ParseIncomingDataToObject<spic::Transform>(pkg._data,
                                                                                    MAX_UPDATE_TRANSFORM_SIZE,
                                                                                    transform);
    std::string gameObjectId = std::string(pkg._gameObjectId);

    auto gameObject = platformer_engine::Engine::GetInstance().GetActiveScene().GetObjectByName(gameObjectId);
    if (gameObject == nullptr) {
        spic::Debug::LogWarning(std::to_string(clientId) + " tried to update a Game Object with id: " + gameObjectId +
                                ", which does not (yet) exists on the server! Ignoring packet");
        return;
    }
    gameObject->FixGameObjectAfterDeserialize();
    if (gameObject->GetOwnerId() != clientId) {
        spic::Debug::LogWarning(
                "Illegal packet received, " + std::to_string(clientId) + " tried to update GameObject " + gameObjectId +
                ", which is owned by: " + std::to_string(gameObject->GetOwnerId()) + ". Ignoring this packet");
        return;
    }
    gameObject->SetTransform(transform);
    UpdateNetworkedGameObjectTransform(transform, gameObjectId);
}

void
platformer_engine::ServerNetworkManager::RegisterEventHandler(int eventID,
                                                              std::function<void(int clientId, const uint8_t *data,
                                                                                 size_t dataLength)> functionToCall) {
    _eventMap[eventID] = functionToCall;
}

void platformer_engine::ServerNetworkManager::HandleCreateCharacterFromClient(int clientId, const void *data,
                                                                              size_t length) {
    auto pkg = NetPkgs::CreatePlayerCharacter();
    memcpy(&pkg, data, length);
    spic::GameObject gameObject;

    platformer_engine::NetworkingBuffer::ParseIncomingDataToObject<spic::GameObject>(pkg._data,
                                                                                     MAX_SEND_CHARACTER_TO_SERVER_SIZE,
                                                                                     gameObject);

    auto gameObjectFromScene = platformer_engine::Engine::GetInstance().GetActiveScene().GetObjectByName(
            gameObject.GetName());
    if (gameObjectFromScene != nullptr) {
        spic::Debug::LogWarning(
                "Illegal packet received, " + std::to_string(clientId) + " tried to create a new character " +
                gameObject.GetName() +
                ", which is owned by: " + std::to_string(clientId) +
                ". But this Game Object is already created! Ignoring this packet");
        return;
    }
    gameObject.FixGameObjectAfterDeserialize();
    platformer_engine::Engine::GetInstance().GetActiveScene().AddObject(gameObject);
    spic::Debug::Log("Created a player character for player: " + std::to_string(clientId) + ", with object ID: " +
                     gameObject.GetName());
    CreateNetworkedPlayerCharacter(clientId, gameObject);
}

void platformer_engine::ServerNetworkManager::HandleUpdateAnimationFromClient(int clientId, const void *data,
                                                                              size_t length) {
    auto pkg = NetPkgs::UpdateActiveAnimation();
    memcpy(&pkg, data, length);

    auto gameObjectFromScene = platformer_engine::Engine::GetInstance().GetActiveScene().GetObjectByName(
            std::string(pkg._gameObjectId));

    if (gameObjectFromScene == nullptr) {
        spic::Debug::LogWarning(
                "Illegal packet received, " + std::to_string(clientId) + " tried to update the current animation of: " +
                std::string(pkg._gameObjectId) + " which does not exist on the server! Ignoring this packet");
        return;
    }
    if (gameObjectFromScene->GetOwnerId() != clientId) {
        spic::Debug::LogWarning(
                "Illegal packet received, " + std::to_string(clientId) + " tried to update the current animation of " +
                gameObjectFromScene->GetName() +
                ", which is owned by: " + std::to_string(gameObjectFromScene->GetOwnerId()) +
                ". This should not be able to happen, check your logic! Ignoring this packet.");
        return;
    }
    auto playerAnimator = std::dynamic_pointer_cast<Animator>(gameObjectFromScene->GetComponent<Animator>());
    if (playerAnimator == nullptr) {
        spic::Debug::LogWarning(
                "Illegal packet received, " + std::to_string(clientId) + " tried to update the current animation of " +
                gameObjectFromScene->GetName() +
                ", which does not have an animator! Ignoring this packet");
        return;
    }
    playerAnimator->SetActiveAnimation(std::string(pkg._animationId));
    UpdateAnimation(clientId, std::string(pkg._gameObjectId), std::string(pkg._animationId));
}

#pragma endregion HandlePacketsFromClient
