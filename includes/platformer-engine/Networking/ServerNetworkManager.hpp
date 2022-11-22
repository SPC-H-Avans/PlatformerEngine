#ifndef PLATFORMER_ENGINE_SERVERNETWORKMANAGER_HPP
#define PLATFORMER_ENGINE_SERVERNETWORKMANAGER_HPP

#include <vector>
#include "Networking/Client.hpp"
#include "GameObject.hpp"
#include "ProtocolPackages.hpp"

namespace platformer_engine {
    class ServerNetworkManager{
    public:
        std::vector<Client> clients;
        std::vector<std::shared_ptr<spic::GameObject>> gameObjects;
        std::string getLevelName() { return _levelName;}
        inline void setLevelName(const std::string& levelName){ _levelName = levelName;}

        void sendUpdateToClients(const uint8_t* data, size_t dataLength);
        void initializeClient(const Client& client);
        void chooseNewPartyLeader();
    private:
        std::string _levelName;

    };
}
#endif //PLATFORMER_ENGINE_SERVERNETWORKMANAGER_HPP
