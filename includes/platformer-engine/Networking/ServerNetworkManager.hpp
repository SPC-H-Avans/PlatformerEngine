#ifndef PLATFORMER_ENGINE_SERVERNETWORKMANAGER_HPP
#define PLATFORMER_ENGINE_SERVERNETWORKMANAGER_HPP

#include <vector>
#include "Networking/Client.hpp"
#include "GameObject.hpp"
#include "ProtocolPackages.hpp"
#include "Facade/NetworkingFacade.hpp"

namespace platformer_engine {
    /**
     * @brief The ServerNetworkManager class, handles all the networking for the server.
     */
    class ServerNetworkManager: public NetworkManager{
    public:
        ServerNetworkManager(const std::string& sceneId, int playerLimit, int port);
        /**
         * @brief List of connected clients
         */
        std::vector<Client> Clients;
        /**
         * @brief List of networked game objects
         */
        std::vector<std::shared_ptr<spic::GameObject>> GameObjects;
        /**
         * @brief Get current level name
         * @return std::string level name
         */
        auto GetLevelName() -> std::string { return _levelName;}
        /**
         * @brief Set current level name
         * @param levelName level name to set
         */
        inline void SetLevelName(const std::string& levelName){ _levelName = levelName;}
        /**
         * @brief Send update to all clients
         * @param data Data from type MessageHeader
         * @param dataLength length of the data
         * @param reliable If the packet needs to be sent as a reliable packet
         */
        void SendUpdateToClients(const uint8_t* data, size_t dataLength, bool reliable = false);
        /**
         * @brief Perform all actions needed to intialize a new client
         * @param client Reference to client
         */
        void InitializeClient(const Client& client);
        /**
         * @brief Randomly choose new party leader
         */
        void ChooseNewPartyLeader();

        /**
         * @brief Listen to new events;
         */
        void Events();

        // NetworkManager methods
        /**
         * @brief On connect event
         * @param clientId connected client id
         */
        void OnConnect(int clientId) override;
        /**
         * @brief On receive event, handles all incoming packages
         * @param clientId clientID who is the sender
         * @param data Data sent by client
         * @param dataLength Length of the data
         */
        void OnReceive(int clientId, const uint8_t * data, size_t dataLength) override;
        /**
         * @brief On disconnect event
         * @param clientId Disconnected client id
         */
        void OnDisconnect(int clientId) override;
    private:
        std::string _levelName;
        NetworkingFacade _networkingFacade;
    };
}  // namespace platformer_engine
#endif //PLATFORMER_ENGINE_SERVERNETWORKMANAGER_HPP
