#ifndef PLATFORMER_ENGINE_INETWORKMANAGER_HPP
#define PLATFORMER_ENGINE_INETWORKMANAGER_HPP

#include <cstdint>
#include <functional>

namespace platformer_engine{
    /**
     * @brief NetworkManager interface
     */
    class NetworkManager{
    public:
        /**
         * @brief OnConnect event, fired when a client connects
         * @param clientId client ID of the connected client
         */
        virtual void OnConnect(int clientId) = 0;
        /**
         * @brief OnReceive event, fired when data is received
         * @param clientId id of the sending client
         * @param data data received
         * @param dataLength length of the data
         */
        virtual void OnReceive(int clientId, const uint8_t * data, size_t dataLength) = 0;
        /**
         * @brief OnDisconnect event, fired when a client disconnects
         * @param clientId disconnected client id
         */
        virtual void OnDisconnect(int clientId) = 0;

        /**
         * @brief Register a new event handler to handle incoming packets yourself
         * @param eventID ID of the event to bind to
         * @param functionToCall function to call
         */
        virtual void RegisterEventHandler(int eventID, std::function<void(int clientId, const uint8_t *data, size_t dataLength)> functionToCall) = 0;
    };
} // namespace platformer_engine
#endif //PLATFORMER_ENGINE_INETWORKMANAGER_HPP
