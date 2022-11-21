#include "Physics/Collision.hpp"

Collision::Collision(Collider &other, CollisionPoint direction, int uid)
        : _other(other), _contact(std::make_unique<CollisionPoint>(direction)), _id(uid) {}

Collision::Collision(Collider &other, int uid)
        : _other(other), _contact(std::make_unique<CollisionPoint>(CollisionPoint::Uncertain)), _id(uid) {}

auto Collision::GetCollider() const -> Collider& { return _other; }

void Collision::SetCollider(const Collider &other) { this->_other = other; }

auto Collision::Contact() const -> CollisionPoint& { return *_contact; }

void Collision::Contact(const CollisionPoint point) { _contact = std::make_unique<CollisionPoint>(point); }

auto Collision::GetId() const -> int {
    return _id;
}



