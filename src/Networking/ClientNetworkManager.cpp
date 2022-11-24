#include "Networking/ClientNetworkManager.hpp"
#include "Exceptions/NotImplementedException.hpp"
#include "Debug.hpp"

platformer_engine::ClientNetworkManager::ClientNetworkManager() {}

void platformer_engine::ClientNetworkManager::ConnectToServer(const std::string& ip, int port) {
    _networkingFacade.ConnectClient(ip, port);
}

void platformer_engine::ClientNetworkManager::DisconnectFromServer() {
    throw spic::NotImplementedException();
}

void platformer_engine::ClientNetworkManager::TravelToLevel(const std::string &levelName) {
    throw spic::NotImplementedException();
}

void platformer_engine::ClientNetworkManager::SendNetworkPackage(const void* data, size_t dataLength, bool reliable) {
    throw spic::NotImplementedException();
}

void platformer_engine::ClientNetworkManager::OnConnect(int clientId) {
    throw spic::NotImplementedException();
}

void platformer_engine::ClientNetworkManager::OnReceive(int clientId, const uint8_t * data, size_t dataLength) {
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
        default:
            spic::Debug::LogWarning("Unknown message from server: " + std::to_string(messageType));
            break;
    }
    throw spic::NotImplementedException();
}

void platformer_engine::ClientNetworkManager::OnDisconnect(int clientId) {
    throw spic::NotImplementedException();
}
