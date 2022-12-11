#ifndef PLATFORMER_ENGINE_FORCEDRIVENENTITYBODY_HPP
#define PLATFORMER_ENGINE_FORCEDRIVENENTITYBODY_HPP

#include "RigidBody.hpp"
#include "EntityState/EntityStateMachine.hpp"

class ForceDrivenEntityBody : public RigidBody, public std::enable_shared_from_this<ForceDrivenEntityBody> {

public:
    explicit ForceDrivenEntityBody(const PhysicsTemplate &physicsTemplate);
    void FollowOn();
    void WanderOn();

    auto GetFollowRange() -> double;
    auto GetFollowing() -> std::weak_ptr<GameObject>;
    void SetFollowing(const std::shared_ptr<GameObject>& gameObject, double range);

    auto CalcSteeringForce() -> Point;

private:
    std::unique_ptr<EntityStateMachine> _entityStateMachine;
    std::weak_ptr<GameObject> _following;
    double _followRange = 0;
};


#endif //PLATFORMER_ENGINE_FORCEDRIVENENTITYBODY_HPP
