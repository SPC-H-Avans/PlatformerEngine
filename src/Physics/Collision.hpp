
#ifndef PLATFORMER_ENGINE_COLLISION_HPP
#define PLATFORMER_ENGINE_COLLISION_HPP

#include <memory>
#include "Collider.hpp"
#include "Point.hpp"

typedef enum CollisionPoint {
    Left,
    Right,
    Top,
    Bottom,
    Inside,
    Around
};

using namespace spic;

class Collision {
public:
    Collision(Collider& other, CollisionPoint direction);
    explicit Collision(Collider& other);

    void Collider(const Collider& other);
    auto Collider() const -> spic::Collider&;
    void Contact(const CollisionPoint point);
    auto Contact() const -> CollisionPoint&;
private:
    spic::Collider& _other;
    std::unique_ptr<CollisionPoint> _contact;
};


#endif //PLATFORMER_ENGINE_COLLISION_HPP
