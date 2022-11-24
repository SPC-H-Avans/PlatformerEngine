#ifndef PLATFORMER_ENGINE_NETWORKINGFACADE_HPP
#define PLATFORMER_ENGINE_NETWORKINGFACADE_HPP
#include "enet/enet.h"
#include "Debug.hpp"
#include <memory>
#include "Networking/INetworkManager.hpp"
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


namespace platformer_engine{
    /**
     * @brief Facade for the networking system.
     */
    class NetworkingFacade{
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
        void ConnectClient(const std::string& host_ip, int port);
        /**
         * @brief Stop hosting/being a client
         */
        void DestroyHost();
        /**
         * @brief Handle network events each game tick
         * @param manager Reference to the network manager
         */
        void HandleEvents(NetworkManager& manager);

        /**
         * @brief Send a packet to another peer
         */
        bool SendPacketToPeer(int peerId, const void* data, size_t length, bool reliable = false);

        bool SendPacketToAllPeers(const void* data, size_t length, bool reliable = false);
    private:
        /**
         * @brief Server ENet host
         */
        std::unique_ptr<ENetHost> _server = nullptr;
        /**
         * @brief Client ENet host
         */
        std::unique_ptr<ENetHost> _client = nullptr;
    };
}  // namespace platformer_engine
#endif //PLATFORMER_ENGINE_NETWORKINGFACADE_HPP
