#include "Button.hpp"

spic::Button::Button(const std::string &name, const Sprite& sprite, const std::string imgPath, double width, double height, bool disabled)
                        : UIObject(name, width, height), _sprite(sprite) {
    auto selfptr = std::make_shared<Button>(*this);
    _self = selfptr;
    selfptr->_self = selfptr;
    _instances[this->_name] = selfptr;

    _active = !disabled;
    // Load text into memory
    platformer_engine::TextureManager::GetInstance().LoadTexture(name, imgPath);
}

void spic::Button::Render() {
    // TODO: spritesheet support
    platformer_engine::TextureManager::GetInstance().DrawUIButton(
            _name,
            static_cast<int>(GetTransform().position.x), static_cast<int>(GetTransform().position.y),
            static_cast<int>(GetWidth()), static_cast<int>(GetHeight()));
}

void spic::Button::Click() {
    onClick();
}

spic::Button::Button() : UIObject("nullButton", 0, 0) {

}

BOOST_CLASS_EXPORT(spic::Button);
