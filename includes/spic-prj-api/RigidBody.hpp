#ifndef RIGIDBODY_H_
#define RIGIDBODY_H_

#include "Component.hpp"
#include "Point.hpp"
#include "Physics/Collision.hpp"
#include <map>
#include <boost/serialization/access.hpp>
#include <boost/serialization/export.hpp>

namespace spic {

    /**
     * @brief Enumeration for different rigid body types
     */
    enum class BodyType {
        staticBody,
        kinematicBody,
        dynamicBody
    };

    /**
     * @brief A component representing a rigid body.
     */
    class RigidBody : public Component {
    public:
        template<typename archive>
        void serialize(archive &ar, const unsigned /*version*/) {
            ar & boost::serialization::base_object<Component, RigidBody>(*this);
            boost::serialization::void_cast_register<RigidBody, Component>();
            ar & _bodyType;
            ar & _mass;
            ar & _gravityScale;
            ar & _velocity;
            ar & _friction;
            ar & _maxSpeed;
        }

        RigidBody();

        RigidBody(float friction);

        /**
         * @brief Apply force to this rigid body.
         * @param forceDirection A point, used as a vector to indicate direction
         *        and magnitude of the force to be applied.
         * @spicapi
         */
        virtual void AddForce(const Point &forceDirection, double speedMultiplier = 1.0);

        void BodyType(BodyType bodyType) { this->_bodyType = bodyType; }

        enum BodyType BodyType() const { return _bodyType; }

        /**
        * @brief Checks if the rigidbody can move to a certain point
        */
        auto CanMoveTo(CollisionPoint point) -> bool;

        /**
        * @brief Allows a move to a direction. If the move was denied twice before, it has to be allowed twice to be
         * fully allowed.
        */
        void AllowMoveTo(CollisionPoint point);

        /**
        * @brief Denies a move to a direction. If the move was denied twice, it has to be allowed twice to be
        * fully allowed again.
        */
        void DenyMoveTo(CollisionPoint point);

        /**
        * @brief Get the maximum speed vector from this rigidbody
        */
        [[nodiscard]] auto GetMaxSpeed() const -> Point;

        /**
        * @brief Get the velocity vector from this rigidbody
        */
        [[nodiscard]] auto GetVelocity() const -> Point;


    protected:
        float _mass;
        float _gravityScale;
        enum BodyType _bodyType;
        Point _velocity;
        Point _maxSpeed;
        float _friction;

        std::map<CollisionPoint, int> _moveRestrictions;
    };

} // namespace spic

BOOST_SERIALIZATION_ASSUME_ABSTRACT(spic::RigidBody);
BOOST_CLASS_EXPORT_KEY(spic::RigidBody);

#endif // RIGIDBODY_H_
