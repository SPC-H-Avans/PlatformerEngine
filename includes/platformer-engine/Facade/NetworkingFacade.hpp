#ifndef PLATFORMER_ENGINE_NETWORKINGFACADE_HPP
#define PLATFORMER_ENGINE_NETWORKINGFACADE_HPP
#include "enet/enet.h"
#include "Debug.hpp"
#include <memory>
#include "Networking/INetworkManager.hpp"
constexpr int DEFAULT_PORT = 7777;
constexpr int DEFAULT_PLAYER_LIMIT = 5;

namespace platformer_engine{
    class NetworkingFacade{
    public:
        NetworkingFacade();
        ~NetworkingFacade();
        void StartServer(int port = DEFAULT_PORT, int playerLimit = DEFAULT_PLAYER_LIMIT);
        void ConnectClient(std::string host_ip, int port);
        void DestroyHost();
        void HandleEvents(NetworkManager& manager);
    private:
        std::unique_ptr<ENetHost> _server = nullptr;
        std::unique_ptr<ENetHost> _client = nullptr;
        int _clientId = 0;
    };
}  // namespace platformer_engine
#endif //PLATFORMER_ENGINE_NETWORKINGFACADE_HPP
