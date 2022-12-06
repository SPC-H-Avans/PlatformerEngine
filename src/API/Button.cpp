#include "Button.hpp"

spic::Button::Button(const std::string &name, const Sprite& sprite, double width, double height, bool disabled)
                        : UIObject(name, width, height), _sprite(sprite) {
    auto selfptr = std::make_shared<Button>(*this);
    _self = selfptr;
    selfptr->_self = selfptr;
    _instances[this->_name] = selfptr;

    _active = !disabled;
}

void spic::Button::Render() {
    _sprite.Render(_transform);
}

void spic::Button::Click() {
    onClick();
}
