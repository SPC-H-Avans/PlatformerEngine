#ifndef PLATFORMER_ENGINE_CLIENT_HPP
#define PLATFORMER_ENGINE_CLIENT_HPP

#include <string>

namespace platformer_engine {
    class Client{
    public:
        Client(const std::string& ip, int port, int clientId, bool isPartyLeader = false);

        [[nodiscard]] auto GetIp() const -> std::string { return _ip; }
        [[nodiscard]] auto GetPort() const -> int { return _port; }
        [[nodiscard]] auto GetClientId() const -> int { return _clientId; }
        [[nodiscard]] auto IsPartyLeader() const -> bool { return _isPartyLeader; }
        void SetPartyLeader(bool isPartyLeader) { _isPartyLeader = isPartyLeader; }
    private:
        std::string _ip;
        int _port;
        int _clientId;
        bool _isPartyLeader;
    };
}  // namespace platformer_engine
#endif //PLATFORMER_ENGINE_CLIENT_HPP
