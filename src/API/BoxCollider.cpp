#include "BoxCollider.hpp"

BOOST_CLASS_EXPORT(spic::BoxCollider);

void spic::BoxCollider::Width(double newWidth) {
    _width = newWidth;
}

void spic::BoxCollider::UpdateScale(double oldScale, double newScale) {
    _height = (_height / oldScale) * newScale;
    _width = (_width / oldScale) * newScale;
}
