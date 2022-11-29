#ifndef PLATFORMER_ENGINE_PROTOCOLPACKAGES_H
#define PLATFORMER_ENGINE_PROTOCOLPACKAGES_H

#include <cstdint>
#include <boost/asio/basic_streambuf.hpp>
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

#pragma region GameObjects

    struct CreateGameObject : MessageHeader {
        size_t _gameObjectDataLength;
        char _data[256];

        CreateGameObject(const char* data, size_t gameObjectDataLength)
                : MessageHeader(NET_CREATE_GAMEOBJECT), _gameObjectDataLength(gameObjectDataLength) {
            for(int i =0; i < 256; i++)
                if(i < gameObjectDataLength)
                    _data[i] = data[i];
                else
                    _data[i] = 0;
        }
    };

    struct DestroyGameObject: MessageHeader {
        std::string _gameObjectName;

        DestroyGameObject(const std::string& gameObjectName) : MessageHeader(NET_DESTROY_GAMEOBJECT), _gameObjectName(gameObjectName) {}
    };

    struct UpdateGameObjectTransform : MessageHeader {
        spic::Transform _transform;
        std::string _gameObjectName;
        UpdateGameObjectTransform(const std::string& gameObjectName, const spic::Transform& transform) : MessageHeader(NET_UPDATE_GAMEOBJECT_TRANSFORM), _gameObjectName(gameObjectName), _transform(transform) {}
    };

#pragma endregion GameObjects

}  // namespace NetPkgs
#endif //PLATFORMER_ENGINE_PROTOCOLPACKAGES_H
