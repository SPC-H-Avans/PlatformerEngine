#include "Collider.hpp"
#include "Physics/Collision.hpp"
#include "Exceptions/CollisionByIdNotFoundException.hpp"
#include "GameObject.hpp"

const std::vector<std::weak_ptr<Collision>> &spic::Collider::GetCollisions() const {
    return _collisions;
}

Collision &spic::Collider::GetCollisionById(int uid) {
    for (auto &col: _collisions) {
        if (col.lock()->GetId() == uid) {
            return *col.lock();
        }
    }
    std::string gameObjectName = "Unknown";
    auto gob{GetGameObject().lock()};
    if (gob) {
        gob->GetName();
    }
    throw CollisionByIdNotFoundException(uid, gameObjectName);
}

void spic::Collider::AddCollision(const Collision col) {
    _collisions.push_back(std::make_shared<Collision>(col));
}

void spic::Collider::RemoveCollision(int uid) {
    auto col = GetCollisionById(uid);
    auto new_end = std::remove_if(_collisions.begin(), _collisions.end(),
                                  [uid](const std::weak_ptr<Collision> &col) { return col.lock()->GetId() == uid; });
    _collisions.erase(new_end, _collisions.end());
}

std::vector<Collision> Collider::GetCollisionsWith(const Collider &col) {
    auto result = std::vector<Collision>();
    for (const auto &collision1: _collisions) {
        for (const auto &collision2: col.GetCollisions()) {
            if (collision1.lock()->GetId() == collision2.lock()->GetId()) {
                result.push_back(*collision1.lock());
            }
        }
    }
    return result;
}

BOOST_CLASS_EXPORT(spic::Collider);