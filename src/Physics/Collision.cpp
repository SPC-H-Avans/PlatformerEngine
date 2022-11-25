#include "Physics/Collision.hpp"

#include <utility>

Collision::Collision(std::shared_ptr<Collider> other, std::vector<CollisionPoint> direction, const int uid)
        : _other(std::move(other)), _contacts(std::move(direction)), _id(uid) {}

Collision::Collision(std::shared_ptr<Collider> other, const int uid)
        : _other(std::move(other)), _contacts(CollisionPoint::Uncertain), _id(uid) {}

auto Collision::GetCollider() const -> std::shared_ptr<Collider> { return _other; }

void Collision::SetCollider(const std::shared_ptr<Collider>& other) { this->_other = other; }

auto Collision::Contacts() const -> std::vector<CollisionPoint> { return _contacts; }

void Collision::Contacts(const std::vector<CollisionPoint> &point) { _contacts = point; }

auto Collision::GetId() const -> int {
    return _id;
}



