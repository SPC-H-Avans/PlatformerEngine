#ifndef PLATFORMER_ENGINE_CLIENTNETWORKMANAGER_HPP
#define PLATFORMER_ENGINE_CLIENTNETWORKMANAGER_HPP
#include "GameObject.hpp"
#include "Networking/ConnectionStatus.hpp"
#include "ProtocolPackages.hpp"
#include "Networking/INetworkManager.hpp"
namespace platformer_engine {
    /**
     * @brief The ClientNetworkManager class, handles the client side of the network.
     */
    class ClientNetworkManager: public NetworkManager{
    public:
        /**
         * @brief List of game objects from client side.
         */
        std::vector<std::shared_ptr<spic::GameObject>> GameObjects;
        /**
         * @brief Get local player id
         * @return int player id
         */
        [[nodiscard]] inline auto GetLocalPlayerId() const -> int {return _localPlayerId; }
        /**
         * @brief Is player a leader
         * @return bool is party leader
         */
        [[nodiscard]] inline auto IsPartyleader() const -> bool {return _isPartyleader; }
        /**
         * @brief Get the connection status of the client
         * @return ConnectionStatus status of the connection
         */
        inline auto GetConnectionStatus() -> ConnectionStatus {return _connectionStatus; }
        /**
         * @brief Connect to a server with ip and port
         * @param ip Ip of the server
         * @param port Port of the server
         */
        void ConnectToServer(const std::string& ip, int port);
        /**
         * @brief Disconnect from the current server
         */
        void DisconnectFromServer();
        /**
         * @brief Travel to a new level
         * @param levelName Name of the level
         */
        void TravelToLevel(const std::string& levelName);
        /**
         * @brief Send a package to the server
         * @param data Data with type NetworkPackage
         * @param dataLength Length of the data
         * @param reliable If a reliable package should be send
         */
        void SendNetworkPackage(const void* data, size_t dataLength, bool reliable = false);

        // NetworkManager methods
        void OnConnect(int clientId);
        void OnReceive(int clientId, const uint8_t * data, size_t dataLength);
        void OnDisconnect(int clientId);

    private:
        int _localPlayerId;
        bool _isPartyleader;
        ConnectionStatus _connectionStatus = ConnectionStatus::Disconnected;
    };
}
#endif //PLATFORMER_ENGINE_CLIENTNETWORKMANAGER_HPP
