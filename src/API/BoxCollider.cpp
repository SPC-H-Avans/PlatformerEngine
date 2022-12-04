#include "BoxCollider.hpp"

BOOST_CLASS_EXPORT(spic::BoxCollider);

void spic::BoxCollider::Width(double newWidth) {
    _width = newWidth;
}
