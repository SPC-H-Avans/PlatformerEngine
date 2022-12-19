#ifndef PLATFORMER_ENGINE_SERVERNETWORKMANAGER_HPP
#define PLATFORMER_ENGINE_SERVERNETWORKMANAGER_HPP

#include <vector>
#include "Networking/Client.hpp"
#include "GameObject.hpp"
#include "ProtocolPackages.hpp"
#include "Facade/NetworkingFacade.hpp"
#include "Scene.hpp"

namespace platformer_engine {
    /**
     * @brief The ServerNetworkManager class, handles all the networking for the server.
     */
    class ServerNetworkManager : public NetworkManager {
    public:
        ServerNetworkManager(spic::Scene &scene, int playerLimit, int port);

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
        auto GetScene() -> spic::Scene & { return _scene; }

        /**
         * @brief Set current level name
         * @param levelName level name to set
         */
        inline void SetActiveScene(spic::Scene &scene) { _scene = scene; }

        /**
         * @brief Send update to all clients
         * @param data Data from type MessageHeader
         * @param dataLength length of the data
         * @param reliable If the packet needs to be sent as a reliable packet
         */
        void SendUpdateToClients(const void *data, size_t dataLength, bool reliable = false);

        void SendUpdateToClientsExcept(const std::vector<int> &clientIds, const void *data, size_t dataLength,
                                       bool reliable = false);

        /**
         * @brief Send update to a specific client
         * @param clientId client ID of receiver
         * @param data Data from type MessageHeader
         * @param dataLength length of the data
         * @param reliable If the packet needs to be sent as a reliable packet
         */
        void SendUpdateToClient(int clientId, const void *data, size_t dataLength, bool reliable = false);

        /**
         * @brief Perform all actions needed to intialize a new client
         * @param client Reference to client
         */
        void InitializeClient(const Client &client);

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
        void OnReceive(int clientId, const uint8_t *data, size_t dataLength) override;

        /**
         * @brief On disconnect event
         * @param clientId Disconnected client id
         */
        void OnDisconnect(int clientId) override;

        void RegisterEventHandler(int eventID, std::function<void(int clientId, const uint8_t *data,
                                                                  size_t dataLength)> functionToCall) override;


#pragma region DefaultServerEvents

        /**
         * @brief Create a new network Game Object and send it to all clients
         * @param gameObjectToCreate Game Object to create
         */
        void CreateNetworkedGameObject(const spic::GameObject &gameObjectToCreate);

        /**
         * @brief Update the transform of a networked Game Object
         * @param transform New transform
         * @param gameObjectId Game Object ID to update
         */
        void UpdateNetworkedGameObjectTransform(const spic::Transform &transform, const std::string &gameObjectId);

        /**
         * @brief Destroy a networked Game Object
         * @param gameObjectId Game Object ID to destroy
         */
        void DestroyNetworkedGameObject(const std::string &gameObjectId);

        /**
         * @brief Create a new network scene and send it to all clients
         * @param scene scene to create
         */
        void CreateNetworkedScene(int clientId, const spic::Scene &scene);

        void SendLoadedTexturesToClient(int clientId);

        void CreateNetworkedPlayerCharacter(int clientId, const spic::GameObject &gameObjectToCreate);

        void UpdateAnimation(int clientId, const std::string& gameObjectId, const std::string& animationId);

#pragma endregion DefaultServerEvents

    private:
        spic::Scene &_scene;
        NetworkingFacade _networkingFacade;
        std::map<int, std::function<void(int clientId, const uint8_t *data, size_t dataLength)>> _eventMap;
        int _playerLimit;

#pragma region HandlePacketsFromClient

        void HandleGameObjectTransformEventFromClient(int clientId, const void *data, size_t length);

        void HandleCreateCharacterFromClient(int clientId, const void *data, size_t length);

        void HandleUpdateAnimationFromClient(int clientId, const void *data, size_t length);

#pragma endregion HandlePacketsFromClient
    };
}  // namespace platformer_engine
#endif //PLATFORMER_ENGINE_SERVERNETWORKMANAGER_HPP
