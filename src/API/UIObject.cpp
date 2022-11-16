#include "UIObject.hpp"

spic::UIObject::UIObject(const std::string &name, const std::string &tag, double width, double height)
                            : GameObject(name, tag), width(width), height(height) {
    auto selfptr = std::make_shared<UIObject>(*this);
    _self = selfptr;
    selfptr->_self = selfptr;
    _instances[this->_name] = selfptr;
}