#include "Camera.hpp"
#include "Exceptions/InvalidSizeException.hpp"

spic::Camera::Camera(const std::string &name, const std::string &tag, spic::Color backgroundColor,
                     double aspectWidth, double aspectHeight) : GameObject(SetValues(aspectWidth, aspectHeight, name), tag),
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

std::string spic::Camera::SetValues(const double aspectWidth, const double aspectHeight, const std::string name) {
    if(aspectWidth <= 0){
        throw InvalidSizeException(std::to_string(aspectWidth), "Aspect width must be greater than 0");
    }
    if(aspectHeight <=0){
        throw InvalidSizeException(std::to_string(aspectHeight), "Aspect height must be greater than 0");
    }
    _aspectWidth = aspectWidth;
    _aspectHeight = aspectHeight;

    return name;
}
