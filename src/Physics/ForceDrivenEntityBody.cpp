#include "Physics/ForceDrivenEntityBody.hpp"
#include "BoxCollider.hpp"
#include "EntityState/EntityWanderState.hpp"
#include "EntityState/EntityPursuitState.hpp"
#include "EntityState/EntityStateMachine.hpp"
#include "GameObject.hpp"

auto ForceDrivenEntityBody::CalcSteeringForce() -> Point {
    Point stateForce = _entityStateMachine->CalculateForce(shared_from_this());

    Point steeringForce = stateForce;
    if(steeringForce.y < 0 && GetMass() != 0) {
        if(!CanMoveTo(CollisionPoint::Bottom)) {
            steeringForce.y *= 26;
        } else {
            steeringForce.y *= 0;
        }
    }

    return steeringForce;
}

void ForceDrivenEntityBody::FollowOn() {
    EntityPursuitState pursuitState;
    _entityStateMachine->SetState(pursuitState);
}

void ForceDrivenEntityBody::WanderOn() {
    EntityWanderState wanderState;
    _entityStateMachine->SetState(wanderState);
}

void ForceDrivenEntityBody::SetFollowing(const std::shared_ptr<GameObject>& gameObject, double range) {
    _following = gameObject;
    _followRange = range;
}

ForceDrivenEntityBody::ForceDrivenEntityBody(const PhysicsTemplate &physicsTemplate) : RigidBody(physicsTemplate) {
    EntityWanderState state;
    _entityStateMachine = std::make_unique<EntityStateMachine>(state);
}

auto ForceDrivenEntityBody::GetFollowing() -> std::weak_ptr<GameObject> {
    return _following;
}

auto ForceDrivenEntityBody::GetFollowRange() -> double {
    return _followRange;
}
