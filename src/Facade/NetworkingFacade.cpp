#include "Facade/NetworkingFacade.hpp"
#include "Exceptions/NetworkingCouldNotBeInitialized.hpp"
#include "Exceptions/FailedToStartServerException.hpp"
#include "Exceptions/CouldNotConnectToServerException.hpp"
#include "Networking/Client.hpp"
#include "Networking/ClientNetworkManager.hpp"
#include "Exceptions/InvalidPlayerSlotsException.hpp"
#include "Exceptions/InvalidPortException.hpp"
#include <memory>
#include <iostream>
#include <thread>

platformer_engine::NetworkingFacade::NetworkingFacade() {
    if (enet_initialize() != 0) {
        throw spic::NetworkingCouldNotBeInitialized();
    }
    ENetEvent event;

}

platformer_engine::NetworkingFacade::~NetworkingFacade() {
    _connectionStatus = ConnectionStatus::Disconnected;
    enet_deinitialize();
}

void platformer_engine::NetworkingFacade::DestroyHost() {
    if (_server != nullptr) {
        enet_host_destroy(_server.get());
        _server = nullptr;
    }
    if (_client != nullptr) {
        enet_host_destroy(_client.get());
        _client = nullptr;
    }
}

void platformer_engine::NetworkingFacade::StartServer(int port, int playerLimit) {
    if (playerLimit < MIN_PLAYER_SLOTS || playerLimit > MAX_PLAYER_SLOTS) {
        throw spic::InvalidPlayerSlotsException(playerLimit, MIN_PLAYER_SLOTS, MAX_PLAYER_SLOTS);
    }
    if (port < MIN_PORT || port > MAX_PORT) {
        throw spic::InvalidPortException(port, MIN_PORT, MAX_PORT);
    }
    if (_server != nullptr) {
        throw spic::FailedToStartServerException(port);
    }
    ENetAddress address;

    address.host = ENET_HOST_ANY;
    address.port = port;
    _server = std::unique_ptr<ENetHost>(enet_host_create(&address, playerLimit, DEFAULT_CHANNEL_COUNT, 0, 0));
    if (_server == nullptr) {
        throw spic::FailedToStartServerException(port);
    }
    spic::Debug::Log(
            "Server is now running at: " + std::to_string(address.host) + ":" + std::to_string(port) + ", with " +
            std::to_string(playerLimit) + " slots!");

    _myPeerId = DEFAULT_SERVER_PEER_ID;
}

void platformer_engine::NetworkingFacade::ConnectClient(const std::string &host_ip, int port, NetworkManager &manager) {
    std::thread{[this, &host_ip, port, &manager]() {
        if (port < MIN_PORT || port > MAX_PORT) {
            throw spic::InvalidPortException(port, MIN_PORT, MAX_PORT);
        }
        _client = std::unique_ptr<ENetHost>(
                enet_host_create(nullptr, CLIENT_OUTGOING_CONNECTION, DEFAULT_CHANNEL_COUNT, 0, 0));
        if (_client == nullptr) {
            throw spic::CouldNotConnectToServerException();
        }

        ENetAddress address;
        std::unique_ptr<ENetPeer> peer;

        enet_address_set_host(&address, host_ip.c_str());
        address.port = port;

        peer = std::unique_ptr<ENetPeer>(enet_host_connect(_client.get(), &address, DEFAULT_CHANNEL_COUNT, 0));

        if (peer == nullptr) {
            throw spic::CouldNotConnectToServerException();
        }
        _connectionStatus = ConnectionStatus::Connecting;
        ENetEvent event;
        if (enet_host_service(_client.get(), &event, CONNECTION_TIMEOUT) > 0 && event.type == ENET_EVENT_TYPE_CONNECT) {
            spic::Debug::Log(
                    "Connection succeeded on host: " + host_ip + " with port: " + std::to_string(port) + ", I am " +
                    std::to_string(peer->connectID));

            _myPeerId = static_cast<int>(peer->connectID);
            _connectionStatus = ConnectionStatus::Connected;

            while (_connectionStatus == ConnectionStatus::Connected) {
                HandleEvents(manager);
                // std::this_thread::sleep_for(std::chrono::milliseconds((1000 / CLIENT_POLLING_RATE_PER_SECOND)));
            }
        } else {
            enet_peer_reset(peer.get());
            spic::Debug::LogWarning("Connection failed on host: " + host_ip + " with port: " + std::to_string(port));
            _connectionStatus = ConnectionStatus::Disconnected;
        }
    }}.detach();
}

void platformer_engine::NetworkingFacade::HandleEvents(NetworkManager &manager) {
    //check if manager is CLientNetworkManager or ServerNetworkManager
    ENetHost *host = nullptr;
    if (typeid(manager) == typeid(ClientNetworkManager)) {
        host = _client.get();
    } else {
        host = _server.get();
    }

    ENetEvent event;
    while (enet_host_service(host, &event, EVENT_FETCH_TIMEOUT) > 0) {
        switch (event.type) {
            case ENET_EVENT_TYPE_CONNECT:
                spic::Debug::Log("A new client connected from: " + std::to_string(event.peer->address.host) + ":" +
                                 std::to_string(event.peer->address.port) + ", with ID: " +
                                 std::to_string(event.peer->connectID));

                _addressPeerIdMap[std::to_string(event.peer->address.host) + ":" +
                                  std::to_string(event.peer->address.port)] = (int)event.peer->connectID;
                manager.OnConnect((int)event.peer->connectID);
                break;

            case ENET_EVENT_TYPE_RECEIVE:
                spic::Debug::Log(
                        "A packet of length " + std::to_string(event.packet->dataLength) + " was received from " +
                        std::to_string(event.peer->connectID) + " on channel " + std::to_string(event.channelID));
                manager.OnReceive(event.peer->connectID, event.packet->data, event.packet->dataLength);
                /* Clean up the packet now that we're done using it. */
                enet_packet_destroy(event.packet);
                break;

            case ENET_EVENT_TYPE_DISCONNECT:
                spic::Debug::Log(std::to_string(GetPeerIdByAddressAndPort(std::to_string(event.peer->address.host), event.peer->address.port)) + " disconnected");

                manager.OnDisconnect(GetPeerIdByAddressAndPort(std::to_string(event.peer->address.host), event.peer->address.port));

                RemovePeerIdFromAddressMap(std::to_string(event.peer->address.host), event.peer->address.port);
                break;

            case ENET_EVENT_TYPE_NONE:
                break;
        }
    }
}

auto platformer_engine::NetworkingFacade::SendPacketToPeer(int peerId, const void *data, size_t length,
                                                           bool reliable) -> bool {
    if (data == nullptr || length <= 0) {
        return false;
    }

    ENetHost *host = nullptr;
    if (_client != nullptr) {
        host = _client.get();
    } else {
        host = _server.get();
    }

    for (int i = 0; i < host->connectedPeers; i++) {
        ENetPeer *peers = host->peers;
        if (peers[i].connectID == peerId) {
            ENetPacket *packet = enet_packet_create(data, length, reliable ? ENET_PACKET_FLAG_RELIABLE : 0x0);
            if (packet == nullptr) {
                return false;
            }

            if (enet_peer_send(&peers[i], reliable ? RELIABLE_CHANNEL : UNRELIABLE_CHANNEL, packet) < 0) {
                return false;
            }
            spic::Debug::Log("Packet sent");
            return true;
        }
    }
    return false;
}

auto platformer_engine::NetworkingFacade::SendPacketToAllPeers(const void *data, size_t length, bool reliable) -> bool {
    if (data == nullptr || length <= 0) {
        return false;
    }

    ENetHost *host = nullptr;
    if (_client != nullptr) {
        host = _client.get();
    } else {
        host = _server.get();
    }

    ENetPacket *packet = enet_packet_create(data, length, reliable ? ENET_PACKET_FLAG_RELIABLE : 0x0);
    if (packet == nullptr) {
        return false;
    }

    enet_host_broadcast(host, reliable ? RELIABLE_CHANNEL : UNRELIABLE_CHANNEL, packet);
    return true;
}

void platformer_engine::NetworkingFacade::DisconnectClientFromServer() {
    if (_client != nullptr) {
        for (auto i = 0; i < _client->peerCount; i++) {
            ENetEvent event;
            enet_peer_disconnect(_client->peers, 0);

            bool disconnected = false;
            while (enet_host_service(_client.get(), &event, 3000) > 0 && !disconnected) {
                switch (event.type) {
                    case ENET_EVENT_TYPE_RECEIVE:
                        enet_packet_destroy(event.packet);
                        break;
                    case ENET_EVENT_TYPE_DISCONNECT:
                        spic::Debug::Log("Client disconnected from server.");
                        disconnected = true;
                        break;
                }
            }

            if (!disconnected)
                enet_peer_reset(_client->peers);

            _client->peers++;
        }
        _connectionStatus = ConnectionStatus::Disconnected;
        _client = nullptr;
    }
}

auto platformer_engine::NetworkingFacade::GetPeerIdByAddressAndPort(const std::string &address, int port) -> int {
    return _addressPeerIdMap[address + ":" + std::to_string(port)];
}

void platformer_engine::NetworkingFacade::RemovePeerIdFromAddressMap(const std::string &address, int port) {
    auto key = address + ":" + std::to_string(port);
    _addressPeerIdMap.erase(key);
}
