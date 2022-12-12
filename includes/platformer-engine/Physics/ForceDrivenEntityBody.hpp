#ifndef PLATFORMER_ENGINE_FORCEDRIVENENTITYBODY_HPP
#define PLATFORMER_ENGINE_FORCEDRIVENENTITYBODY_HPP

#include "RigidBody.hpp"
#include "EntityState/EntityStateMachine.hpp"

class ForceDrivenEntityBody : public RigidBody, public std::enable_shared_from_this<ForceDrivenEntityBody> {

public:
    /**
     * @brief Constructor that takes a physicsTemplate to set the Physics variables
     * @param physicsTemplate template for the physics values
     */
    explicit ForceDrivenEntityBody(const PhysicsTemplate &physicsTemplate);

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
    auto CalcSteeringForce() -> Point;

private:
    std::unique_ptr<EntityStateMachine> _entityStateMachine;
    std::weak_ptr<GameObject> _following;
    double _followRange = 0;
};


#endif //PLATFORMER_ENGINE_FORCEDRIVENENTITYBODY_HPP
