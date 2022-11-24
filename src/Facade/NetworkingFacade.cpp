#include "Facade/NetworkingFacade.hpp"
#include "Exceptions/NetworkingCouldNotBeInitialized.hpp"
#include "Exceptions/FailedToStartServerException.hpp"
#include "Exceptions/CouldNotConnectToServerException.hpp"
#include "Networking/Client.hpp"

platformer_engine::NetworkingFacade::NetworkingFacade() {
    if(enet_initialize() != 0){
        throw spic::NetworkingCouldNotBeInitialized();
    }
    ENetEvent event;

}

platformer_engine::NetworkingFacade::~NetworkingFacade() {
    DestroyHost();
    enet_deinitialize();
}

void platformer_engine::NetworkingFacade::DestroyHost(){
    enet_host_destroy(_server.get());
}

void platformer_engine::NetworkingFacade::StartServer(int port, int playerLimit) {
    if(_server != nullptr){
        throw spic::FailedToStartServerException();
    }

    ENetAddress address;

    address.host = ENET_HOST_ANY;
    address.port = port;
    _server = std::unique_ptr<ENetHost>(enet_host_create(&address, playerLimit, 1, 0, 0));
    if(_server == nullptr){
        throw spic::FailedToStartServerException();
    }
    spic::Debug::Log("Server is now running at port: " + std::to_string(port) + ", with " + std::to_string(playerLimit) + " slots!");
}

void platformer_engine::NetworkingFacade::ConnectClient(std::string host_ip, int port) {
    _client = std::unique_ptr<ENetHost>(enet_host_create(NULL, 1, 1, 0, 0));
    if(_client == nullptr) {
        throw spic::CouldNotConnectToServerException();
    }

    ENetAddress address;
    std::unique_ptr<ENetPeer> peer;

    enet_address_set_host(&address, host_ip.c_str());
    address.port = port;

    peer = std::unique_ptr<ENetPeer>(enet_host_connect(_client.get(), &address, 1, 0));

    if(peer == nullptr) {
        throw spic::CouldNotConnectToServerException();
    }

    ENetEvent event;
    if(enet_host_service(_client.get(), &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT) {
        spic::Debug::Log("Connection succeeded on host: " + host_ip + " with port: " + std::to_string(port));
    } else {
        enet_peer_reset(peer.get());
        spic::Debug::LogWarning("Connection failed on host: " + host_ip + " with port: " + std::to_string(port));
    }
}

void platformer_engine::NetworkingFacade::HandleEvents(NetworkManager& manager){
    ENetEvent event;
    while (enet_host_service(_server.get(), &event, 0) > 0) {
        switch (event.type) {
            case ENET_EVENT_TYPE_CONNECT:
                spic::Debug::Log("A new client connected from: " + std::to_string(event.peer->address.host) + ":" +  std::to_string(event.peer->address.port) + ", with ID: " +  std::to_string(event.peer->connectID));
                manager.OnConnect(event.peer->connectID);
                break;

            case ENET_EVENT_TYPE_RECEIVE:
                spic::Debug::Log("A packet of length " + std::to_string(event.packet->dataLength) + " was received from " + std::to_string(event.peer->connectID) + " on channel " + std::to_string(event.channelID));
                manager.OnReceive(event.peer->connectID, event.packet->data, event.packet->dataLength);
                /* Clean up the packet now that we're done using it. */
                enet_packet_destroy (event.packet);
                break;

            case ENET_EVENT_TYPE_DISCONNECT:
                spic::Debug::Log(std::to_string(event.peer->connectID) + " disconnected");
                manager.OnDisconnect(event.peer->connectID);
                break;

            case ENET_EVENT_TYPE_NONE:
                break;
        }
    }
}