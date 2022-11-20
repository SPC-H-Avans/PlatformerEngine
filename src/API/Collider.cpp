#include "Collider.hpp"
#include "Physics/Collision.hpp"

std::vector<std::shared_ptr<Collision>> spic::Collider::GetCollisions() {
    return _collisions;
}

std::shared_ptr<Collision> spic::Collider::GetCollisionById(int uid) {
    for(auto col : _collisions) {
        if(col->GetId() == uid) {
            return col;
        }
    }
}

void spic::Collider::AddCollision(const std::shared_ptr<Collision> col) {
    _collisions.push_back(col);
}

void spic::Collider::RemoveCollision(int id) {

}
