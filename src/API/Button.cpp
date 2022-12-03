#include "Button.hpp"

spic::Button::Button(const std::string &name, double width, double height)
                        : UIObject(name, width, height) {
    auto selfptr = std::make_shared<Button>(*this);
    _self = selfptr;
    selfptr->_self = selfptr;
    _instances[this->_name] = selfptr;
}
