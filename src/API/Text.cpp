#include "Text.hpp"

spic::Text::Text(const std::string &name, const std::string &tag, double width, double height,
                 const std::string text, const std::string font, int size,
                 spic::Alignment alignment, spic::Color color)
                 : UIObject(name, tag, width, height), _text(text), _font(font), _size(size),
                 _alignment(alignment), _color(color) {
    auto selfptr = std::make_shared<Text>(*this);
    _self = selfptr;
    selfptr->_self = selfptr;
    _instances[this->_name] = selfptr;
}
