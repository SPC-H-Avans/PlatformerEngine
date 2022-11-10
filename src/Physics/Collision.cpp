
#include "Collision.hpp"

Collision::Collision(spic::Collider &other, CollisionPoint direction) : _other(other), _contact(std::make_unique<CollisionPoint>(direction)) {}
Collision::Collision(spic::Collider &other) : _other(other), _contact(nullptr) {}

spic::Collider& Collision::Collider() const { return _other; }

void Collision::Collider(const spic::Collider &other) { this->_other = other; }

CollisionPoint& Collision::Contact() const { return *_contact; }

void Collision::Contact(const CollisionPoint point) { _contact = std::make_unique<CollisionPoint>(point); }

