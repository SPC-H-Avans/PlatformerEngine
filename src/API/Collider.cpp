#include "Collider.hpp"
#include "Physics/Collision.hpp"
#include "Exceptions/CollisionByIdNotFoundException.hpp"
#include "GameObject.hpp"

const std::vector<Collision> &spic::Collider::GetCollisions() const {
    return _collisions;
}

Collision& spic::Collider::GetCollisionById(int uid) {
    for(auto& col : _collisions) {
        if(col.GetId() == uid) {
            return col;
        }
    }
    std::string gameObjectName = "Unknown";
    auto gob { GetGameObject().lock() };
    if (gob) {
        gob->GetName();
    }
    throw CollisionByIdNotFoundException(uid, gameObjectName);
}

void spic::Collider::AddCollision(const Collision col) {
    _collisions.push_back(col);
}

void spic::Collider::RemoveCollision(int uid) {
    auto col = GetCollisionById(uid);
    auto new_end = std::remove_if(_collisions.begin(), _collisions.end(),
                                  [uid](const Collision & col) { return col.GetId() == uid; });
    _collisions.erase(new_end, _collisions.end());
}

std::vector<Collision> Collider::GetCollisionsWith(const Collider& col) {
    auto result = std::vector<Collision>();
    for(const auto& collision1 : _collisions) {
        for(const auto& collision2 : col.GetCollisions()) {
            if(collision1.GetId() == collision2.GetId()) {
                result.push_back(collision1);
            }
        }
    }
    return result;
}

void Collider::SetLocation(Point location) {
    _location = location;
}

auto Collider::GetLocation() const -> Point {
    return _location;
}
