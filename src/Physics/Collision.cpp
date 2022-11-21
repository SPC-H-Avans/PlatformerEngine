#include "Physics/Collision.hpp"

#include <utility>

Collision::Collision(std::shared_ptr<Collider> other, CollisionPoint direction, const int uid)
        : _other(std::move(other)), _contact(direction), _id(uid) {}

Collision::Collision(std::shared_ptr<Collider> other, const int uid)
        : _other(std::move(other)), _contact(CollisionPoint::Uncertain), _id(uid) {}

auto Collision::GetCollider() const -> std::shared_ptr<Collider> { return _other; }

void Collision::SetCollider(const std::shared_ptr<Collider>& other) { this->_other = other; }

auto Collision::Contact() const -> CollisionPoint { return _contact; }

void Collision::Contact(const CollisionPoint point) { _contact = point; }

auto Collision::GetId() const -> int {
    return _id;
}



