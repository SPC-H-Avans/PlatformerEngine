#include "Physics/Collision.hpp"

#include <utility>

auto Collision::Contact() const -> CollisionPoint { return _contact; }

void Collision::Contact(const CollisionPoint point) { _contact = point; }

auto Collision::GetId() const -> int {
    return _id;
}

Collision::Collision(std::shared_ptr<Collider> self, std::shared_ptr<Collider> other, CollisionPoint direction,
                     int uid) : _self(std::move(self)), _other(std::move(other)), _contact(direction), _id(uid) {

}

Collision::Collision(std::shared_ptr<Collider> self, std::shared_ptr<Collider> other, int uid)
        : _self(std::move(self)), _other(std::move(other)), _id(uid) {

}

void Collision::SetOtherCollider(const std::shared_ptr<Collider> &other) { this->_other = other; }

void Collision::SetSelfCollider(const std::shared_ptr<Collider> &self) { this->_self = self; }

auto Collision::GetOtherCollider() -> std::shared_ptr<Collider> { return _other; }

auto Collision::GetSelfCollider() const -> std::shared_ptr<Collider> { return _self; }



