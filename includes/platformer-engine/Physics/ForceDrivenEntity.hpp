#ifndef PLATFORMER_ENGINE_FORCEDRIVENENTITY_HPP
#define PLATFORMER_ENGINE_FORCEDRIVENENTITY_HPP

#include "Component.hpp"
#include "Templates/PhysicsTemplate.hpp"
#include "EntityState/EntityStateMachine.hpp"

namespace platformer_engine {
    using spic::Component;
    using spic::GameObject;

    class ForceDrivenEntity : public spic::Component {
    public:
        template<class Archive>
        void serialize(Archive &ar, unsigned int version) {
            ar & boost::serialization::base_object<Component, ForceDrivenEntity>(*this);
            boost::serialization::void_cast_register<ForceDrivenEntity, Component>();
        }
        /**
         * @brief Constructor that sets all default values
         */
        explicit ForceDrivenEntity();

        /**
         * @brief Turns on the follow mode by changing the state to 'pursuit' in the State Machine
         */
        void FollowOn();

        /**
         * @brief Turns on the wander mode by changing the state to 'wander' in the State Machine
         */
        void WanderOn();

        /**
         * @brief Get the range in which the object should start following the target object
         * @return The range as a double
         */
        auto GetFollowRange() -> double;

        /**
         * @brief Getter for the object that is being followed by this object
         * @return A weak pointer to the target GameObject
         */
        auto GetFollowing() -> std::weak_ptr<GameObject>;

        /**
         * @brief Set the target GameObject that should be followed and the range in which it should start following
         * @param gameObject An std::shared_ptr to the target GameObject that should be followed
         * @param range The range in which the object should start following as a double
         */
        void SetFollowing(const std::shared_ptr<GameObject>& gameObject, double range);

        /**
         * @brief Calculate all the forces this ForceDrivenEntity has within it's scope
         * @return The combined forces in a 2D Vector point
         */
        auto CalcSteeringForce() -> spic::Point;

    private:
        std::unique_ptr<EntityStateMachine> _entityStateMachine;
        std::weak_ptr<GameObject> _following;
        double _followRange = 0;
    };
}

#endif //PLATFORMER_ENGINE_FORCEDRIVENENTITY_HPP
