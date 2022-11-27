#include "Networking/ClientNetworkManager.hpp"
#include "Exceptions/NotImplementedException.hpp"
void platformer_engine::ClientNetworkManager::ConnectToServer(const std::string& ip, int port) {
    throw spic::NotImplementedException();
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
