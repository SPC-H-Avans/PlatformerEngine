#ifndef COLLIDER2D_H_
#define COLLIDER2D_H_

#include <vector>
#include "Component.hpp"
#include <boost/serialization/access.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/weak_ptr.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include "Networking/boost/portable_binary_iarchive.hpp"
#include "Networking/boost/portable_binary_oarchive.hpp"

// Forward declaration of Collider
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

        [[nodiscard]] auto GetCollisions() const -> const std::vector<std::shared_ptr<Collision>> &;

        auto GetCollisionsWith(const Collider &col) -> std::vector<Collision>;

        auto GetCollisionById(int uid) -> Collision &;

        void AddCollision(Collision col);

        void RemoveCollision(int uid);

    private:
        std::vector<std::shared_ptr<Collision>> _collisions;
    };

}  // namespace spic

BOOST_SERIALIZATION_ASSUME_ABSTRACT(spic::Collider);

#endif // COLLIDER2D_H_
