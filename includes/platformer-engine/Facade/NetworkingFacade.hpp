#ifndef PLATFORMER_ENGINE_NETWORKINGFACADE_HPP
#define PLATFORMER_ENGINE_NETWORKINGFACADE_HPP

#include "enet/enet.h"
#include "Debug.hpp"
#include <memory>
#include <map>
#include "Networking/INetworkManager.hpp"
#include "Networking/ConnectionStatus.hpp"

constexpr int DEFAULT_PORT = 7777;
constexpr int DEFAULT_PLAYER_LIMIT = 5;
constexpr int CONNECTION_TIMEOUT = 5000;
constexpr int EVENT_FETCH_TIMEOUT = 0; //Keep at 0 otherwise this becomes blocking
constexpr int DEFAULT_CHANNEL_COUNT = 2;
constexpr int CLIENT_OUTGOING_CONNECTION = 1;

constexpr int MAX_PORT = 65535;
constexpr int MIN_PORT = 1;
constexpr int MIN_PLAYER_SLOTS = 1;
constexpr int MAX_PLAYER_SLOTS = 1000;

constexpr int UNRELIABLE_CHANNEL = 0;
constexpr int RELIABLE_CHANNEL = 1;

constexpr int CLIENT_POLLING_RATE_PER_SECOND = 60;

constexpr int DEFAULT_SERVER_PEER_ID = 0;


namespace platformer_engine {
    /**
     * @brief Facade for the networking system.
     */
    class NetworkingFacade {
    public:
        /**
         * @brief Construct a new Networking Facade object.
         */
        NetworkingFacade();

        /**
         * @brief Destroy the Networking Facade object.
         */
        ~NetworkingFacade();

        /**
         * @brief Start a server
         * @param port Port to use
         * @param playerLimit Max amount of players on server
         */
        void StartServer(int port = DEFAULT_PORT, int playerLimit = DEFAULT_PLAYER_LIMIT);

        /**
         * @brief Start a client and connect to a server
         * @param host_ip IP to connect to
         * @param port Port to connect to
         */
        void ConnectClient(const std::string &host_ip, int port, NetworkManager &manager);

        /**
         * @brief Disconnects a client from its current server
         */
        void DisconnectClientFromServer();

        /**
         * @brief Stop hosting/being a client
         */
        void DestroyHost();

        /**
         * @brief Handle network events each game tick
         * @param manager Reference to the network manager
         */
        void HandleEvents(NetworkManager &manager);

        /**
         * @brief Send a packet to a peer
         * @param peerId Peer ID where to send it to
         * @param data Packet to send
         * @param length Length of the packet
         * @param reliable Reliable or not
         * @return
         */
        auto SendPacketToPeer(int peerId, const void *data, size_t length, bool reliable = false) -> bool;

        /**
         * @brief Send a packet to all peers
         * @param data Packet to send
         * @param length Length of the packet
         * @param reliable Reliable or not
         * @return
         */
        auto SendPacketToAllPeers(const void *data, size_t length, bool reliable = false) -> bool;

        auto SendPacketToAllPeersExcept(std::vector<int> clientIds, const void *data, size_t length,
                                        bool reliable = false) -> bool;

        /**
         * @brief Get current peer ID (0 if server)
         * @return int Peer ID
         */
        [[nodiscard]] inline auto GetMyPeerId() const -> int { return _myPeerId; }

    private:
        /**
         * @brief Server ENet host
         */
        std::unique_ptr<ENetHost> _server = nullptr;
        /**
         * @brief Client ENet host
         */
        std::unique_ptr<ENetHost> _client = nullptr;

        ConnectionStatus _connectionStatus = ConnectionStatus::Disconnected;

        int _myPeerId = DEFAULT_SERVER_PEER_ID;

        std::map<std::string, int> _addressPeerIdMap;

        /**
         * @brief Get peer ID from adress:port map
         * @param address Peer address
         * @param port Peer port
         * @return Peer iD
         */
        int GetPeerIdByAddressAndPort(const std::string &address, int port);

        /**
         * @brief Remove peer from adress:port map
         * @param address Address peer
         * @param port Port of peer
         */
        void RemovePeerIdFromAddressMap(const std::string &address, int port);
    };
}  // namespace platformer_engine
#endif //PLATFORMER_ENGINE_NETWORKINGFACADE_HPP
