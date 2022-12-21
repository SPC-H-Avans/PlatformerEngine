#include "Physics/ForceDrivenEntity.hpp"
#include "BoxCollider.hpp"
#include "EntityState/EntityWanderState.hpp"
#include "EntityState/EntityPursuitState.hpp"
#include "EntityState/EntityStateMachine.hpp"
#include "GameObject.hpp"

auto platformer_engine::ForceDrivenEntity::CalcSteeringForce() -> Point {
    Point steeringForce{0,0};

    auto gameObject = GetGameObject().lock();
    if(gameObject) {
        auto rigidBody = std::dynamic_pointer_cast<RigidBody>(gameObject->GetComponent<RigidBody>());
        if(rigidBody != nullptr) {
            Point stateForce = _entityStateMachine->CalculateForce(rigidBody);

            steeringForce += stateForce;
            if(steeringForce.y < 0 && rigidBody->GetGravityScale() != 0) {
                if(!rigidBody->CanMoveTo(CollisionPoint::Bottom)) {
                    steeringForce.y *= 26;
                } else {
                    steeringForce.y *= 0;
                }
            }
        }
    } else {
        gameObject.reset();
    }

    return steeringForce;
}

void platformer_engine::ForceDrivenEntity::FollowOn() {
    EntityPursuitState pursuitState;
    _entityStateMachine->SetState(pursuitState);
}

void platformer_engine::ForceDrivenEntity::WanderOn() {
    EntityWanderState wanderState;
    _entityStateMachine->SetState(wanderState);
}

void platformer_engine::ForceDrivenEntity::SetFollowing(const std::shared_ptr<GameObject>& gameObject, double range) {
    _following = gameObject;
    _followRange = range;
}

auto platformer_engine::ForceDrivenEntity::GetFollowing() -> std::weak_ptr<GameObject> {
    return _following;
}

auto platformer_engine::ForceDrivenEntity::GetFollowRange() -> double {
    return _followRange;
}

platformer_engine::ForceDrivenEntity::ForceDrivenEntity() {
    EntityWanderState state;
    _entityStateMachine = std::make_unique<EntityStateMachine>(state);
}

auto platformer_engine::ForceDrivenEntity::GetCurrentState() const -> const EntityState& {
    return _entityStateMachine->GetCurrentState();
}

BOOST_CLASS_EXPORT(platformer_engine::ForceDrivenEntity);