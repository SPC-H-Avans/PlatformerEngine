#include "Camera.hpp"
#include "Exceptions/InvalidSizeException.hpp"


spic::Camera::Camera(const std::string &name, const std::string &tag, spic::Color backgroundColor,
                     double aspectWidth, double aspectHeight) : GameObject(name, tag),
                                                                _backgroundColor(backgroundColor) {
    if (aspectWidth <= 0) {
        throw InvalidSizeException(std::to_string(aspectWidth), "Aspect width must be greater than 0");
    }
    if (aspectHeight <= 0) {
        throw InvalidSizeException(std::to_string(aspectHeight), "Aspect height must be greater than 0");
    }
    _aspectWidth = aspectWidth;
    _aspectHeight = aspectHeight;

    auto selfptr = std::make_shared<Camera>(*this);
    _self = selfptr;
    selfptr->_self = selfptr;
    _instances[this->_name] = selfptr;
}

void spic::Camera::Zoom(double aspectWidth, double aspectHeight) {
    if (aspectWidth <= 0) {
        throw InvalidSizeException(std::to_string(aspectWidth), "Aspect width must be greater than 0");
    }
    if (aspectHeight <= 0) {
        throw InvalidSizeException(std::to_string(aspectHeight), "Aspect height must be greater than 0");
    }
    std::static_pointer_cast<Camera>(_self.lock())->_aspectWidth = aspectWidth;
    std::static_pointer_cast<Camera>(_self.lock())->_aspectHeight = aspectHeight;
}

auto spic::Camera::GetAspectWidth() -> double {
    return std::static_pointer_cast<Camera>(_self.lock())->_aspectWidth;
}

auto spic::Camera::GetAspectHeight() -> double {
    auto cam = std::static_pointer_cast<Camera>(_self.lock());
    return cam->_aspectHeight;
}

spic::Camera::Camera(const std::string &name) : GameObject(name), _backgroundColor(Color::Black()), _aspectWidth(0),
                                                _aspectHeight(0) {}

BOOST_CLASS_EXPORT(spic::Camera);