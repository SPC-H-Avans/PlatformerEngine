#include "Text.hpp"

spic::Text::Text(const std::string &name, double width, double height,
                 const std::string text, const std::string fontPath,
                 spic::Color color,
                 int fontSize, spic::Alignment alignment)
                 : UIObject(name, width, height), _text(text), _font(fontPath), _size(fontSize),
                 _color(color), _alignment(alignment) {
    auto selfptr = std::make_shared<Text>(*this);
    _self = selfptr;
    selfptr->_self = selfptr;
    _instances[this->_name] = selfptr;

    // Load text into memory
    platformer_engine::GraphicsFacade::GetInstance().LoadUIText(name, fontPath, text, fontSize, color);
}

void spic::Text::Render() {
    // TODO: remove _text and _font and replace with _textId
    platformer_engine::TextureManager::GetInstance().DrawUIText(_font, _transform.position.x, _transform.position.x, _width, _height);
}
