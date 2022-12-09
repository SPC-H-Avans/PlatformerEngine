#ifndef PLATFORMER_ENGINE_CLIENTNETWORKMANAGER_HPP
#define PLATFORMER_ENGINE_CLIENTNETWORKMANAGER_HPP

#pragma once

#include "GameObject.hpp"
#include "ProtocolPackages.hpp"
#include "Networking/INetworkManager.hpp"
#include "Facade/NetworkingFacade.hpp"
#include <map>
#include <cstring>

class Engine;

namespace platformer_engine {
    /**
     * @brief The ClientNetworkManager class, handles the client side of the network.
     */
    class ClientNetworkManager : public NetworkManager {
    public:
        /**
         * @brief Client Network Manager constructor
         */
        ClientNetworkManager();

        /**
         * @brief List of game objects from client side.
         */
        std::vector<std::shared_ptr<spic::GameObject>> GameObjects;

        /**
         * @brief Get local player id
         * @return int player id
         */
        [[nodiscard]] inline auto GetLocalPlayerId() const -> int { return _localPlayerId; }

        /**
         * @brief Is player a leader
         * @return bool is party leader
         */
        [[nodiscard]] inline auto IsPartyleader() const -> bool { return _isPartyleader; }

        /**
         * @brief Get the connection status of the client
         * @return ConnectionStatus status of the connection
         */
        inline auto GetConnectionStatus() -> ConnectionStatus { return _connectionStatus; }

        /**
         * @brief Connect to a server with ip and port
         * @param ip Ip of the server
         * @param port Port of the server
         */
        void ConnectToServer(const std::string &ip, int port);

        /**
         * @brief Disconnect from the current server
         */
        void DisconnectFromServer();

        /**
         * @brief Travel to a new level
         * @param levelName Name of the level
         */
        void TravelToLevel(const std::string &levelName);

        /**
         * @brief Send a package to the server
         * @param data Data with type NetworkPackage
         * @param dataLength Length of the data
         * @param reliable If a reliable package should be send
         */
        void SendNetworkPackage(const void *data, size_t dataLength, bool reliable = false);

        // NetworkManager methods
        /**
         * @brief On connect event
         * @param clientId Client id of the connected client
         */
        void OnConnect(int clientId) override;

        /**
         * @brief On receive data event
         * @param clientId clientID of sender (The server in this case)
         * @param data Data with type NetworkPackage
         * @param dataLength Length of the data
         */
        void OnReceive(int clientId, const uint8_t *data, size_t dataLength) override;

        /**
         * @brief On disconnect event
         * @param clientId clientID who disconnected
         */
        void OnDisconnect(int clientId) override;

        void RegisterEventHandler(int eventID, std::function<void(int clientId, const uint8_t *data,
                                                                  size_t dataLength)> functionToCall) override;

#pragma region DefaultClientEvents

        /**
         * @brief Update the transform of a Game Object (Only if this client owns the object)
         * @param transform New transform
         * @param gameObjectId Game Object ID of the object to update
         */
        void UpdateNetworkedGameObjectTransform(const spic::Transform &transform,
                                                const std::string &gameObjectId);

        void InitializeMyClient(spic::GameObject &playerChar);

        void UpdateActiveAnimation(const std::string& gameObjectId, const std::string& animationId);

#pragma endregion DefaultClientEvents

        /**
             * @brief Parse the scene sent by the server
             * @param data Data
             * @param length length of data
             */
        void CreateScene(const void *data, size_t length);

    private:
        int _localPlayerId = 0;
        bool _isPartyleader;
        std::map<int, std::function<void(int clientId, const uint8_t *data, size_t dataLength)>> _eventMap;
        ConnectionStatus _connectionStatus = ConnectionStatus::Disconnected;
        NetworkingFacade _networkingFacade;

#pragma region HandleIncomingPackets

        /**
         * @brief Remove a local client from game and remove his game object
         * @param data Data
         * @param dataLength Length of game object
         */
        void RemoveLocalClientFromGame(const void *data, size_t dataLength);

        /**
         * @brief Create a new game object
         * @param data Data
         * @param length Length of data
         */
        void CreateGameObject(const void *data, size_t length);

        /**
         * @brief Destroy a game object
         * @param data Data
         * @param length Length of data
         */
        void DestroyGameObject(const void *data, size_t length);

        /**
         * @brief Update transform of a game object
         * @param data Data
         * @param length Length of data
         */
        void UpdateGameObjectTransform(const void *data, size_t length);

        void LoadedTextures(const void *data, size_t length);

        void UpdateAnimationFromServer(const void *data, size_t length);

#pragma endregion HandleIncomingPackets
    };
}  // namespace platformer_engine
#endif //PLATFORMER_ENGINE_CLIENTNETWORKMANAGER_HPP
