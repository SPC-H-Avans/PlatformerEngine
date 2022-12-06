#ifndef COLLIDER2D_H_
#define COLLIDER2D_H_

#include <vector>
#include "Component.hpp"
#include "Point.hpp"

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
        void SetLocation(Point location);
        [[nodiscard]] auto GetLocation() const -> Point;
    private:
        std::vector<Collision> _collisions;
        Point _location;
    };

}

#endif // COLLIDER2D_H_
