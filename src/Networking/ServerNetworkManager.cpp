
#include "Networking/ServerNetworkManager.hpp"
#include "Exceptions/NotImplementedException.hpp"
#include "Utility/NetworkingBuffer.hpp"
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/asio.hpp>

platformer_engine::ServerNetworkManager::ServerNetworkManager(spic::Scene &scene, int playerLimit, int port) : _scene(
        scene), _playerLimit(playerLimit) {
    _networkingFacade.StartServer(port, playerLimit);
    for (auto &item: _scene.GetAllObjects()) {
        item->SetOwnerId(_networkingFacade.GetMyPeerId());

    }
}

void platformer_engine::ServerNetworkManager::SendUpdateToClients(const void *data, size_t dataLength, bool reliable) {
    _networkingFacade.SendPacketToAllPeers(data, dataLength, reliable);
}

void platformer_engine::ServerNetworkManager::InitializeClient(const Client &client) {
    throw spic::NotImplementedException();
}

void platformer_engine::ServerNetworkManager::ChooseNewPartyLeader() {
    throw spic::NotImplementedException();
}

void platformer_engine::ServerNetworkManager::OnConnect(int clientId) {
    Client client{clientId};
    Clients.push_back(client);
    spic::Debug::Log("Currently hosting a game for " + std::to_string(Clients.size()) + "/" + std::to_string(_playerLimit) + " clients!");
    //InitializeClient(client); TODO
    auto gameobject = spic::GameObject("Huts", "Hatsa");
    spic::Transform trans;
    trans.position.x = 100;
    gameobject.SetTransform(trans);
    trans = gameobject.GetTransform();

    auto toSend = spic::GameObject::FindWithTag("Hatsa");

    CreateNetworkedGameObject(*toSend.get());
    UpdateNetworkedGameObjectTransform(trans, "Huts");
    DestroyNetworkedGameObject("Huts");
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
    switch (messageType) {
        case NET_REQUEST_PING:
            spic::Debug::Log("Ping received from client!");
        default:
            spic::Debug::LogWarning("Unknown message from server: " + std::to_string(messageType));
            break;
    }
    throw spic::NotImplementedException();
}

void platformer_engine::ServerNetworkManager::OnDisconnect(int clientId) {
    //Remove client from list
    std::erase_if(Clients, [clientId](const Client &client) { return client.GetClientId() == clientId; });
    spic::Debug::Log("Currently hosting a game for " + std::to_string(Clients.size()) + "/" + std::to_string(_playerLimit) + " clients!");
    NetPkgs::KickClient kickClient(clientId);
    _networkingFacade.SendPacketToAllPeers(&kickClient, sizeof(kickClient));
}

void platformer_engine::ServerNetworkManager::Events() {
    boost::asio::streambuf buf;
    _networkingFacade.HandleEvents(*this);
}

void platformer_engine::ServerNetworkManager::CreateNetworkedGameObject(const spic::GameObject &gameObjectToCreate) {
    boost::asio::streambuf buf;
    platformer_engine::NetworkingBuffer::ObjectToAsioBuffer<spic::GameObject>(gameObjectToCreate, buf);

    auto charPtr = buffer_cast<const char*>(buf.data());

    auto pkg = NetPkgs::CreateGameObject(charPtr, buf.size());
    SendUpdateToClients(&pkg, sizeof(pkg), true);
}

void platformer_engine::ServerNetworkManager::UpdateNetworkedGameObjectTransform(const spic::Transform &transform,
                                                                        const std::string &gameObjectId) {
    boost::asio::streambuf buf;
    platformer_engine::NetworkingBuffer::ObjectToAsioBuffer<spic::Transform>(transform, buf);

    auto charPtr = buffer_cast<const char*>(buf.data());

    auto pkg = NetPkgs::UpdateGameObjectTransform(gameObjectId.c_str(), charPtr, buf.size());
    SendUpdateToClients(&pkg, sizeof(pkg), true);
}

void platformer_engine::ServerNetworkManager::DestroyNetworkedGameObject(const std::string& gameObjectId){
    auto pkg = NetPkgs::DestroyGameObject(gameObjectId.c_str());
    SendUpdateToClients(&pkg, sizeof(pkg), true);
}