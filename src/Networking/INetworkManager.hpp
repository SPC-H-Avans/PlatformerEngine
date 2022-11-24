#ifndef PLATFORMER_ENGINE_INETWORKMANAGER_HPP
#define PLATFORMER_ENGINE_INETWORKMANAGER_HPP

#include <cstdint>

namespace platformer_engine{
    class NetworkManager{
    public:
        virtual void OnConnect(int clientId) = 0;
        virtual void OnReceive(int clientId, const uint8_t * data, size_t dataLength) = 0;
        virtual void OnDisconnect(int clientId) = 0;
    };
}
#endif //PLATFORMER_ENGINE_INETWORKMANAGER_HPP
