#ifndef COLLIDER2D_H_
#define COLLIDER2D_H_

#include "Component.hpp"
#include <vector>

// Forward decleration of Collider
class Collision;

namespace spic {

    /**
     * @brief The base class for all colliders.
     * @spicapi
     */
    class Collider : public Component {
    public:
        std::vector<std::shared_ptr<Collision>> GetCollisions();
        std::shared_ptr<Collision> GetCollisionById(int uid);
        void AddCollision(std::shared_ptr<Collision> col);
        void RemoveCollision(int uid);
    private:

        std::vector<std::shared_ptr<Collision>> _collisions;
    };

}

#endif // COLLIDER2D_H_
