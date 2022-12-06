#ifndef COLLIDER2D_H_
#define COLLIDER2D_H_

#include <vector>
#include "Component.hpp"
#include "Point.hpp"

// Forward decleration of Collider
class Collision;

namespace spic {

    enum ColliderType {
        Body,
        LookAhead
    };

    /**
     * @brief The base class for all colliders.
     * @spicapi
     */
    class Collider : public Component {
    public:
        [[nodiscard]] auto GetCollisions() const -> const std::vector<Collision>&;
        auto GetCollisionsWith(const Collider& col) -> std::vector<Collision>;
        auto GetCollisionById(int uid) -> Collision&;
        void AddCollision(Collision col);
        void RemoveCollision(int uid);
        void SetPosition(Point position);
        [[nodiscard]] auto GetPosition() const -> Point;


        [[nodiscard]] auto GetColliderType() const -> ColliderType;
        void SetColliderType(ColliderType colliderType);
    private:
        std::vector<Collision> _collisions;
        Point _position;
        ColliderType _colliderType;

    };

}

#endif // COLLIDER2D_H_
