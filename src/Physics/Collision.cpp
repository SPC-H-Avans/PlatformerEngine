
#include "Physics/Collision.hpp"

Collision::Collision(spic::Collider &other, CollisionPoint direction) : _other(other), _contact(std::make_unique<CollisionPoint>(direction)) {}
Collision::Collision(spic::Collider &other) : _other(other), _contact(std::make_unique<CollisionPoint>(CollisionPoint::Uncertain)) {}

auto Collision::GetCollider() const -> spic::Collider& { return _other; }

void Collision::SetCollider(const spic::Collider &other) { this->_other = other; }

auto Collision::Contact() const -> CollisionPoint& { return *_contact; }

void Collision::Contact(const CollisionPoint point) { _contact = std::make_unique<CollisionPoint>(point); }

