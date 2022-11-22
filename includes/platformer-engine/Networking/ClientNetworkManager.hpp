#ifndef PLATFORMER_ENGINE_CLIENTNETWORKMANAGER_HPP
#define PLATFORMER_ENGINE_CLIENTNETWORKMANAGER_HPP
#include "GameObject.hpp"
#include "Networking/ConnectionStatus.hpp"
#include "ProtocolPackages.hpp"
namespace platformer_engine {
    class ClientNetworkManager{
    public:
        std::vector<std::shared_ptr<spic::GameObject>> GameObjects;
        inline auto GetLocalPlayerId() const -> int {return _localPlayerId; }
        inline auto IsPartyleader() const -> bool {return _isPartyleader; }
        inline auto GetConnectionStatus() -> ConnectionStatus {return _connectionStatus; }
        void ConnectToServer(const std::string& ip, int port);
        void DisconnectFromServer();
        void TravelToLevel(const std::string& levelName);
        void SendNetworkPackage(const void* data, size_t dataLength, bool reliable = false);

    private:
        int _localPlayerId;
        bool _isPartyleader;
        ConnectionStatus _connectionStatus = ConnectionStatus::Disconnected;
    };
}
#endif //PLATFORMER_ENGINE_CLIENTNETWORKMANAGER_HPP
