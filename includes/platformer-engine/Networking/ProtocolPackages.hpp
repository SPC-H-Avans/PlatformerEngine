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
        char _data[MAX_CREATE_GAME_OBJECT_SIZE];

        CreateGameObject(const char* data, size_t gameObjectDataLength)
                : MessageHeader(NET_CREATE_GAMEOBJECT), _gameObjectDataLength(gameObjectDataLength) {
            for(int i = 0; i < MAX_CREATE_GAME_OBJECT_SIZE; i++) {
                if (i < gameObjectDataLength) {
                    _data[i] = data[i];
                } else {
                    _data[i] = 0;
                }
            }
        }
    };

    struct DestroyGameObject: MessageHeader {
        char _data[MAX_GAME_OBJECT_NAME_SIZE];

        DestroyGameObject(const char* gameObjectId) : MessageHeader(NET_DESTROY_GAMEOBJECT) {
            assert(gameObjectId);

            strncpy(_data, gameObjectId, MAX_GAME_OBJECT_NAME_SIZE);
            _data[MAX_GAME_OBJECT_NAME_SIZE - 1] = '\0';
        }
    };

    struct UpdateGameObjectTransform : MessageHeader {
        char _gameObjectId[MAX_GAME_OBJECT_NAME_SIZE];
        char _data[MAX_UPDATE_TRANSFORM_SIZE];
        UpdateGameObjectTransform(const char* gameObjectId, const char* data, size_t dataLength) : MessageHeader(NET_UPDATE_GAMEOBJECT_TRANSFORM) {
            for(int i = 0; i < MAX_UPDATE_TRANSFORM_SIZE; i++) {
                if (i < dataLength) {
                    _data[i] = data[i];
                } else {
                    _data[i] = 0;
                }
            }
            strncpy(_gameObjectId, gameObjectId, MAX_GAME_OBJECT_NAME_SIZE);
            _data[MAX_GAME_OBJECT_NAME_SIZE - 1] = '\0';
        }
    };

#pragma endregion GameObjects

}  // namespace NetPkgs
#endif //PLATFORMER_ENGINE_PROTOCOLPACKAGES_H
