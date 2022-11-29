#ifndef RIGIDBODY_H_
#define RIGIDBODY_H_

#include "Component.hpp"
#include "Point.hpp"
#include "Physics/Collision.hpp"
#include <map>
#include <boost/serialization/access.hpp>

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

        template<typename archive> void serialize(archive& ar, const unsigned /*version*/) {
            ar & _mass;
            ar & _gravityScale;
            ar & _bodyType;
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

            bool CanMoveTo(CollisionPoint point);
            void AllowMoveTo(CollisionPoint point);
            void DenyMoveTo(CollisionPoint point);

        protected:
            float _mass;
            float _gravityScale;
            enum BodyType _bodyType;

            std::map<CollisionPoint, int> _moveRestrictions;
    };

} // namespace spic

#endif // RIGIDBODY_H_
