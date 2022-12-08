#ifndef COLLIDER2D_H_
#define COLLIDER2D_H_

#include <vector>
#include "Component.hpp"

// Forward decleration of Collider
class Collision;

namespace spic {

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
        auto GetObstructsMovement() -> bool { return _obstructsMovement; }
        void SetObstructsMovement(bool obstructsMovement) { _obstructsMovement = obstructsMovement; }
    private:
        std::vector<Collision> _collisions;
        bool _obstructsMovement = true;
    };

}

#endif // COLLIDER2D_H_
