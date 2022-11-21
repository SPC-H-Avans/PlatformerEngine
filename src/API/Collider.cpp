#include "Collider.hpp"
#include "Physics/Collision.hpp"

const std::vector<Collision> &spic::Collider::GetCollisions() const {
    return _collisions;
}

Collision& spic::Collider::GetCollisionById(int uid) {
    for(auto& col : _collisions) {
        if(col.GetId() == uid) {
            return col;
        }
    }
}

void spic::Collider::AddCollision(const Collision col) {
    _collisions.push_back(col);
}

void spic::Collider::RemoveCollision(int uid) {

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
