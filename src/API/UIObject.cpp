#include "UIObject.hpp"

spic::UIObject::UIObject(const std::string &name, double width, double height)
                            : GameObject(name), _width(width), _height(height) {
    auto selfptr = std::make_shared<UIObject>(*this);
    _self = selfptr;
    selfptr->_self = selfptr;
    _instances[this->_name] = selfptr;
}
