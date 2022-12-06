#ifndef RIGIDBODY_H_
#define RIGIDBODY_H_

#include "Component.hpp"
#include "Point.hpp"
#include "Physics/Collision.hpp"
#include <map>
#include <boost/serialization/access.hpp>
#include "Behaviour/ForceDrivenEntityBehaviours.hpp"

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
        RigidBody(float friction);

        template<typename archive> void serialize(archive& ar, const unsigned /*version*/) {
            ar & _bodyType;
            ar & _mass;
            ar & _gravityScale;
            ar & _velocity;
            ar & _friction;
            ar & _maxSpeed;
        }


        /**
         * @brief Apply force to this rigid body.
         * @param forceDirection A point, used as a vector to indicate direction
         *        and magnitude of the force to be applied.
         * @spicapi
         */
        virtual void AddForce(const Point& forceDirection);

        void BodyType (BodyType bodyType) { this->_bodyType = bodyType; }
        auto BodyType() -> enum BodyType { return _bodyType; }

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

        [[nodiscard]] auto GetMaxSpeed() const -> Point;
        [[nodiscard]] auto GetVelocity() const -> Point;
        [[nodiscard]] auto GetHeading() const -> Point;
        void SetHeading(Point new_heading);

        void AddNearbyCollider(Collider &collider);


    protected:
        enum BodyType _bodyType;
        float _mass;
        float _gravityScale;
        Point _velocity;
        Point _maxSpeed;
        Point _heading;
        const float _friction;

        std::map<CollisionPoint, int> _moveRestrictions;
        std::vector<Collider> _nearbyColliders;
    };

} // namespace spic

#endif // RIGIDBODY_H_
