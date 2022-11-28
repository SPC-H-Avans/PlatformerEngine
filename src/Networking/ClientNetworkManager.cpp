#include "Networking/ClientNetworkManager.hpp"
#include "Exceptions/NotImplementedException.hpp"
#include "Debug.hpp"
#include "Engine/Engine.hpp"

platformer_engine::ClientNetworkManager::ClientNetworkManager() {}

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
    _connectionStatus = ConnectionStatus::Connected;
}

void platformer_engine::ClientNetworkManager::OnReceive(int clientId, const uint8_t *data, size_t dataLength) {
    if (!data || dataLength < 3)
        return;
    uint8_t versionMajor = data[0];
    uint8_t versionMinor = data[1];
    uint8_t messageType = data[2];
    if (versionMajor != NET_PROTOCOL_VERSION_MAJOR
        || versionMinor != NET_PROTOCOL_VERSION_MINOR) {
        //Handle bad networking version
        throw spic::NotImplementedException();
    }
    switch (messageType) {
        case NET_REQUEST_PING:
            spic::Debug::Log("Ping received from server!");
            break;
        case NET_KICK_CLIENT:
            RemoveLocalClientFromGame(data, dataLength);
            break;
        case NET_CREATE_GAMEOBJECT:
            CreateGameObject(data, dataLength);
            break;
        case NET_DESTROY_GAMEOBJECT:
            DestroyGameObject(data, dataLength);
            break;
        case NET_UPDATE_GAMEOBJECT_TRANSFORM:
            UpdateGameObjectTransform(data, dataLength);
        default:
            spic::Debug::LogWarning("Unknown message from server: " + std::to_string(messageType));
            break;
    }
    //throw spic::NotImplementedException();
}

void platformer_engine::ClientNetworkManager::OnDisconnect(int clientId) {
    _localPlayerId = 0;
    _isPartyleader = false;
    _connectionStatus = ConnectionStatus::Disconnected;
}

void platformer_engine::ClientNetworkManager::RemoveLocalClientFromGame(const void *data,
                                                                        size_t dataLength) {
    //Check if player exists
    auto pkg = NetPkgs::KickClient(0);
    memcpy(&pkg, data, dataLength);
    auto playerToRemove = pkg.clientId;
    //Perform remove logic
    throw spic::NotImplementedException();
}

void platformer_engine::ClientNetworkManager::CreateGameObject(const void *data, size_t length) {
    auto pkg = NetPkgs::CreateGameObject(spic::GameObject("Null"));
    memcpy(&pkg, data, length);
    auto gameObject = std::make_shared<spic::GameObject>(pkg._gameObjectToCreate);
    Engine::GetInstance().GetActiveScene().AddObject(gameObject);
}

void platformer_engine::ClientNetworkManager::DestroyGameObject(const void *data, size_t length) {
    auto pkg = NetPkgs::DestroyGameObject("");
    memcpy(&pkg, data, length);
    platformer_engine::Engine::GetInstance().GetActiveScene().RemoveObject(pkg._gameObjectName);
}

void platformer_engine::ClientNetworkManager::UpdateGameObjectTransform(const void *data, size_t length) {
    auto pkg = NetPkgs::UpdateGameObjectTransform("", Transform());
    memcpy(&pkg, data, length);
    auto gameObject=  platformer_engine::Engine::GetInstance().GetActiveScene().GetObjectByName(pkg._gameObjectName);
    if(gameObject != nullptr){
        gameObject->SetTransform(pkg._transform);
    }
}
