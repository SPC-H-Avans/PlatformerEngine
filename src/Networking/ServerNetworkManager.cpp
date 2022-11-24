
#include "Networking/ServerNetworkManager.hpp"
#include "Exceptions/NotImplementedException.hpp"
void platformer_engine::ServerNetworkManager::SendUpdateToClients(const uint8_t* data, size_t dataLength, bool reliable) {
    throw spic::NotImplementedException();
}

void platformer_engine::ServerNetworkManager::InitializeClient(const Client& client) {
    throw spic::NotImplementedException();
}

void platformer_engine::ServerNetworkManager::ChooseNewPartyLeader() {
    throw spic::NotImplementedException();
}

platformer_engine::ServerNetworkManager::ServerNetworkManager(const std::string& sceneId,  int port) {

}
