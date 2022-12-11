#ifndef BEHAVIOURSCRIPT_H_
#define BEHAVIOURSCRIPT_H_

#include "Component.hpp"
#include "Collider.hpp"
#include "Physics/Collision.hpp"
#include <boost/serialization/access.hpp>
#include <boost/serialization/export.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include "Networking/boost/portable_binary_iarchive.hpp"
#include "Networking/boost/portable_binary_oarchive.hpp"

namespace spic {

    class BehaviourScript : public Component {
    public:
        template<typename archive>
        void serialize(archive &ar, const unsigned /*version*/) {
            ar & boost::serialization::base_object<Component, BehaviourScript>(*this);
            boost::serialization::void_cast_register<BehaviourScript, Component>();
        }

        /**
         * @brief On start of behaviour script
         * @spicapi
         */
        virtual void OnStart() {};

        /**
         * @brief On update of behaviour script
         * @spicapi
         */
        virtual void OnUpdate(double deltaTime) {};

        /**
         * @brief Sent when another object enters a trigger collider
         *        attached to this object (2D physics only).
         * @spicapi
         */
        virtual void OnTriggerEnter2D(const Collision collision) {};

        /**
         * @brief Sent when another object leaves a trigger collider
         *        attached to this object (2D physics only).
         * @spicapi
         */
        virtual void OnTriggerExit2D(const Collision collision) {};

        /**
         * @brief Sent each frame where another object is within a trigger
         *        collider attached to this object (2D physics only).
         * @spicapi
         */
        virtual void OnTriggerStay2D(const Collision collision) {};
    };

}  // namespace spic

#endif // BEHAVIOURSCRIPT_H_
