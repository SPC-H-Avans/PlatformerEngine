
#include "Networking/ServerNetworkManager.hpp"
#include "Exceptions/NotImplementedException.hpp"
void platformer_engine::ServerNetworkManager::sendUpdateToClients(const uint8_t *data, size_t dataLength) {
    throw spic::NotImplementedException();
}

void platformer_engine::ServerNetworkManager::initializeClient(const Client& client) {
    throw spic::NotImplementedException();
}

void platformer_engine::ServerNetworkManager::chooseNewPartyLeader() {
    throw spic::NotImplementedException();
}
