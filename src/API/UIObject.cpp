#include "UIObject.hpp"

spic::UIObject::UIObject(const std::string &name, double width, double height)
                            : GameObject(name), _width(width), _height(height) {
}
