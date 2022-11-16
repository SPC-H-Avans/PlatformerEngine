#include "Camera.hpp"
#include "Exceptions/InvalidSizeException.hpp"


spic::Camera::Camera(const std::string &name, const std::string &tag, spic::Color backgroundColor,
                     double aspectWidth, double aspectHeight) : GameObject(name, tag),
                        _backgroundColor(backgroundColor), _aspectHeight(aspectHeight), _aspectWidth(aspectWidth)
{
    auto selfptr = std::make_shared<Camera>(*this);
    self = selfptr;
    instances[this->name] = selfptr;
}

void spic::Camera::Zoom(double aspectWidth, double aspectHeight) {
    if(aspectWidth <= 0){
        throw InvalidSizeException(std::to_string(aspectWidth), "Aspect width must be greater than 0");
    }
    if(aspectHeight <=0){
        throw InvalidSizeException(std::to_string(aspectHeight), "Aspect height must be greater than 0");
    }
    std::static_pointer_cast<Camera>(self.lock())->_aspectWidth = aspectWidth;
    std::static_pointer_cast<Camera>(self.lock())->_aspectHeight = aspectHeight;
}
