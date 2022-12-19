#include "Text.hpp"

spic::Text::Text(const std::string& name, double width, double height,
                 const std::string& text, const std::string& fontPath,
                 int fontSize, spic::Color color,
                 spic::Alignment alignment)
        : UIObject(name, width, height), _text(text), _font(fontPath), _size(fontSize),
          _color(color), _alignment(alignment) {
    auto selfptr = std::make_shared<Text>(*this);
    _self = selfptr;
    selfptr->_self = selfptr;
    _instances[this->_name] = selfptr;

    // Load text into memory
    platformer_engine::TextureManager::GetInstance().CreateOrUpdateUIText(name, fontPath, text, fontSize, color);
}

void spic::Text::Render() {
    platformer_engine::TextureManager::GetInstance().DrawUIText(
            _name,
            static_cast<int>(GetTransform().position.x), static_cast<int>(GetTransform().position.y),
            static_cast<int>(GetWidth()), static_cast<int>(GetHeight()));
}

spic::Text::Text() : UIObject("nullUI", 0, 0), _color(Color::Transparent()) {

}

BOOST_CLASS_EXPORT(spic::Text);
