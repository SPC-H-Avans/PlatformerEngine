#ifndef PLATFORMER_ENGINE_SERVERNETWORKMANAGER_HPP
#define PLATFORMER_ENGINE_SERVERNETWORKMANAGER_HPP

#include <vector>
#include "Networking/Client.hpp"
#include "GameObject.hpp"
#include "ProtocolPackages.hpp"

namespace platformer_engine {
    class ServerNetworkManager{
    public:
        std::vector<Client> Clients;
        std::vector<std::shared_ptr<spic::GameObject>> GameObjects;
        auto GetLevelName() -> std::string { return _levelName;}
        inline void SetLevelName(const std::string& levelName){ _levelName = levelName;}

        void SendUpdateToClients(const uint8_t* data, size_t dataLength);
        void InitializeClient(const Client& client);
        void ChooseNewPartyLeader();
    private:
        std::string _levelName;
    };
}  // namespace platformer_engine
#endif //PLATFORMER_ENGINE_SERVERNETWORKMANAGER_HPP
