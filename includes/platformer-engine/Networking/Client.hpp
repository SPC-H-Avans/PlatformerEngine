#ifndef PLATFORMER_ENGINE_CLIENT_HPP
#define PLATFORMER_ENGINE_CLIENT_HPP

#include <string>

namespace platformer_engine {
    /**
     * @brief Client object for the networking system.
     */
    class Client {
    public:
        /**
         * @brief Construct a new Client object.
         * @param ip ip of client.
         * @param port port of client
         * @param clientId client ID
         * @param isPartyLeader If the client is a party leader
         */
        Client(const std::string &ip, int port, int clientId, bool isPartyLeader = false);

        /**
         * @brief Construct a new Client object.
         * @param clientId client ID
         * @param isPartyLeader If the client is a party leader
         */
        Client(int clientId, bool isPartyLeader = false);

        /**
         * @brief Get the Ip of the client
         * @return std::string ip
         */
        [[nodiscard]] auto GetIp() const -> std::string { return _ip; }

        /**
         * @brief Get the Port of the client
         * @return int port of the client
         */
        [[nodiscard]] auto GetPort() const -> int { return _port; }

        /**
         * @brief Get the Client Id of the client
         * @return int client id
         */
        [[nodiscard]] auto GetClientId() const -> int { return _clientId; }

        /**
         * @brief Get if the client is a party leader
         * @return bool if the client is a party leader
         */
        [[nodiscard]] auto IsPartyLeader() const -> bool { return _isPartyLeader; }

        /**
         * @brief Set if the client is a party leader
         * @param isPartyLeader
         */
        void SetPartyLeader(bool isPartyLeader) { _isPartyLeader = isPartyLeader; }

    private:
        std::string _ip;
        int _port;
        int _clientId;
        bool _isPartyLeader;
    };
}  // namespace platformer_engine
#endif //PLATFORMER_ENGINE_CLIENT_HPP
