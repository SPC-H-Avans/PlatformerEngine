#ifndef COLLIDER2D_H_
#define COLLIDER2D_H_

#include <vector>
#include "Component.hpp"
#include <boost/serialization/access.hpp>
#include <boost/serialization/export.hpp>

// Forward decleration of Collider
class Collision;

namespace spic {

    /**
     * @brief The base class for all colliders.
     * @spicapi
     */
    class Collider : public Component {
    public:
        template<class Archive>
        void serialize(Archive &ar, unsigned int version) {
            ar & boost::serialization::base_object<Component, Collider>(*this);
            boost::serialization::void_cast_register<Collider, Component>();
        }

        [[nodiscard]] auto GetCollisions() const -> const std::vector<Collision> &;

        auto GetCollisionsWith(const Collider &col) -> std::vector<Collision>;

        auto GetCollisionById(int uid) -> Collision &;

        void AddCollision(Collision col);

        void RemoveCollision(int uid);

    private:
        std::vector<Collision> _collisions;
    };

}  // namespace spic

#endif // COLLIDER2D_H_
