#ifndef PLATFORMER_ENGINE_PROTOCOLPACKAGES_H
#define PLATFORMER_ENGINE_PROTOCOLPACKAGES_H

#include <cstdint>
#include "ProtocolDefinitions.hpp"

namespace NetPkgs {
    /**
     * @brief The base class for all protocol packages.
     */
    struct MessageHeader {
        uint8_t protocolMajorVersion;
        uint8_t protocolMinorVersion;
        uint8_t packageType;

        MessageHeader(uint8_t packageType = 0)
                : protocolMajorVersion(NET_PROTOCOL_VERSION_MAJOR), protocolMinorVersion(NET_PROTOCOL_VERSION_MINOR),
                  packageType(packageType) {}
    };

    /**
     * @brief The package that is sent when a client wants to disconnect from the server.
     */
    struct ClientDisconnection : MessageHeader {
        ClientDisconnection() : MessageHeader(NET_REQUEST_LEAVE_SERVER) {}
    };

    struct Ping : MessageHeader {
        Ping() : MessageHeader(NET_REQUEST_PING) {}
    };

    struct KickClient : MessageHeader {
        int clientId;

        KickClient(int clientId) : MessageHeader(NET_KICK_CLIENT), clientId(clientId) {}
    };

}  // namespace platformer_engine
#endif //PLATFORMER_ENGINE_PROTOCOLPACKAGES_H
