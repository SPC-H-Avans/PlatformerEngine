#include "Camera.hpp"
#include "Exceptions/InvalidSizeException.hpp"

spic::Camera::Camera(const std::string &name, const std::string &tag, spic::Color backgroundColor,
                     double aspectWidth, double aspectHeight) : GameObject(name, tag, SetValues(aspectWidth, aspectHeight)),
                                                                _backgroundColor(backgroundColor)
{

}

void spic::Camera::Zoom(double aspectWidth, double aspectHeight) {
    if(aspectWidth <= 0){
        throw InvalidSizeException(std::to_string(aspectWidth), "Aspect width must be greater than 0");
    }
    if(aspectHeight <=0){
        throw InvalidSizeException(std::to_string(aspectHeight), "Aspect height must be greater than 0");
    }
    _aspectWidth = aspectWidth;
    _aspectHeight = aspectHeight;
}

std::shared_ptr<spic::Camera> spic::Camera::SetValues(const double aspectWidth, const double aspectHeight) {
    if(aspectWidth <= 0){
        throw InvalidSizeException(std::to_string(aspectWidth), "Aspect width must be greater than 0");
    }
    if(aspectHeight <=0){
        throw InvalidSizeException(std::to_string(aspectHeight), "Aspect height must be greater than 0");
    }
    _aspectWidth = aspectWidth;
    _aspectHeight = aspectHeight;

    auto ptr = std::make_shared<Camera>(*this);
    std::string test = typeid(this).name();

    return ptr;
}
