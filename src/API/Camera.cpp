#include "Camera.hpp"

spic::Camera::Camera(const std::string &name, const std::string &tag, spic::Color backgroundColor,
                     double aspectWidth, double aspectHeight) : GameObject(name, tag),
                        _backgroundColor(backgroundColor), _aspectHeight(aspectHeight), _aspectWidth(aspectWidth)
{
    auto selfptr = std::make_shared<Camera>(*this);
    _self = selfptr;
    _instances[this->_name] = selfptr;
}