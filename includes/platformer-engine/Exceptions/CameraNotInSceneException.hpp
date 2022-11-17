
#ifndef PLATFORMER_ENGINE_CAMERANOTINSCENEEXCEPTION_H
#define PLATFORMER_ENGINE_CAMERANOTINSCENEEXCEPTION_H

#include <stdexcept>

namespace spic {
    class CameraNotInSceneException : public std::logic_error
    {
    public:
        CameraNotInSceneException (const std::string& gameObjectName) : std::logic_error{"The Camera with name: " + gameObjectName + " is not in added in this scene!"} {}
    };
}
#endif //PLATFORMER_ENGINE_CAMERANOTINSCENEEXCEPTION_H
