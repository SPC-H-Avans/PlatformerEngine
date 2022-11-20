#include "Physics/Collision.hpp"

Collision::Collision(Collider &other, CollisionPoint direction, int id)
        : _other(other), _contact(std::make_unique<CollisionPoint>(direction)) {}

Collision::Collision(Collider &other, int id)
        : _other(other), _contact(std::make_unique<CollisionPoint>(CollisionPoint::Uncertain)), _id(id) {}

auto Collision::GetCollider() const -> Collider& { return _other; }

void Collision::SetCollider(const Collider &other) { this->_other = other; }

auto Collision::Contact() const -> CollisionPoint& { return *_contact; }

void Collision::Contact(const CollisionPoint point) { _contact = std::make_unique<CollisionPoint>(point); }

int Collision::GetId() const {
    return _id;
}



