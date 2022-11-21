
#ifndef PLATFORMER_ENGINE_CAMERANOTINSCENEEXCEPTION_H
#define PLATFORMER_ENGINE_CAMERANOTINSCENEEXCEPTION_H

#include <stdexcept>
#include <string>

namespace spic {
    class CollisionByIdNotFoundException : public std::logic_error
    {
    public:
        CollisionByIdNotFoundException (const int uid, const std::string &gameObjectName)
        : std::logic_error{"GetCollisionById for uid " + std::to_string(uid) + " in Collider with GameObject {" + gameObjectName + "} was not found."} {}
    };
}
#endif //PLATFORMER_ENGINE_CAMERANOTINSCENEEXCEPTION_H
