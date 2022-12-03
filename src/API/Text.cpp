#include "Text.hpp"

spic::Text::Text(const std::string &name, double width, double height,
                 const std::string text, const std::string font, int size,
                 spic::Alignment alignment, spic::Color color)
                 : UIObject(name, width, height), _text(text), _font(font), _size(size),
                 _alignment(alignment), _color(color) {
    auto selfptr = std::make_shared<Text>(*this);
    _self = selfptr;
    selfptr->_self = selfptr;
    _instances[this->_name] = selfptr;
}

void spic::Text::Render() {
    // TODO: remove _text and _font and replace with _textId
    platformer_engine::TextureManager::GetInstance().DrawUIText(_font, _transform.position.x, _transform.position.x, _width, _height);
}
