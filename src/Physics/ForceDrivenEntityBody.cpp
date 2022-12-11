#include "Physics/ForceDrivenEntityBody.hpp"
#include "BoxCollider.hpp"
#include "EntityState/EntityWanderState.hpp"
#include "EntityState/EntityPursuitState.hpp"
#include "EntityState/EntityStateMachine.hpp"
#include "GameObject.hpp"

auto ForceDrivenEntityBody::CalcSteeringForce() -> Point {
    //calculate the combined force from each steering behavior in the
    //vehicle’s list
    //Point pursuitForce = _behaviours->Pursuit(_following);

    Point stateForce = _entityStateMachine->CalculateForce(shared_from_this());
//    Point arriveForce = _behaviours->Arrive(_following);
    // Point avoidForce = AvoidObjects();

    Point steeringForce = stateForce;
    if(steeringForce.y < 0 && _mass != 0) {
        if(!CanMoveTo(CollisionPoint::Bottom)) {
            steeringForce.y *= 26;
        } else {
            steeringForce.y *= 0;
        }
    }

    UpdateLookAhead();

    return steeringForce;
}

Point ForceDrivenEntityBody::AvoidObjects() {

    auto steeringForce = Point{0, 0};

    std::shared_ptr<GameObject> currentGameObject { GetGameObject().lock() };
    if(currentGameObject) {

        // Find the nearest object that we are colliding with or are
        // in danger of colliding with
        Collider* nearest = nullptr;
        double nearestDistance = DBL_MAX;
        for (auto& other : _nearbyColliders)
        {
            // Calculate the distance to the other entity
            double distance = (other.GetPosition() - currentGameObject->GetTransform().position).Length();

            // Check if this is the nearest potential collision
            if (distance < nearestDistance)
            {
                nearest = &other;
                nearestDistance = distance;
            }
        }

        // If we found the nearest collision, calculate a steering force
        // to avoid it
        if (nearest != nullptr)
        {
//            auto colliders = currentGameObject->GetComponents<BoxCollider>();
//            for(auto &colObj : colliders) {
//                auto col = std::dynamic_pointer_cast<BoxCollider>(colObj);
//                if(col->GetColliderType() == ColliderType::LookAhead) {
//                    // Calculate the direction to the nearest collision
//
//                }
//            }

            Point collisionDirection = Point::PointNormalize(nearest->GetPosition() - currentGameObject->GetTransform().position);

            auto maxNegativeForce = _maxSpeed.x * _mass * -2.5;

            // Calculate the steering force to avoid the collision
            steeringForce = collisionDirection * maxNegativeForce;
//            break;
        }

    } else {
        currentGameObject.reset();
    }

    // Empty nearby collider vector
    _nearbyColliders.clear();

    // Return the steering force
    return steeringForce;
}

void ForceDrivenEntityBody::UpdateLookAhead() {

    std::shared_ptr<GameObject> gameObject{GetGameObject().lock()};
    if (gameObject) {
        auto colliders = gameObject->GetComponents<BoxCollider>();
        for(auto &colObj : colliders) {
            auto col = std::dynamic_pointer_cast<BoxCollider>(colObj);
            if(col->GetColliderType() == ColliderType::LookAhead) {
                // This collider is a look-ahead collider, it should  be at gameObject location + radius in the heading direction
                auto newPosition = gameObject->GetTransform().position + (_heading * _lookAhead);
                col->SetPosition(newPosition);
            }
        }
    } else { // GameObject was already deleted
        gameObject.reset();
    }
}

void ForceDrivenEntityBody::FollowOn() {
    EntityPursuitState pursuitState;
    _entityStateMachine->SetState(pursuitState);
}

void ForceDrivenEntityBody::WanderOn() {
    EntityWanderState wanderState;
    _entityStateMachine->SetState(wanderState);
}

void ForceDrivenEntityBody::SetFollowing(const std::shared_ptr<GameObject>& gameObject) {
    _following = gameObject;
}

ForceDrivenEntityBody::ForceDrivenEntityBody(float friction) : RigidBody(friction), _lookAhead(25) {
    _gravityScale = 0.01;
    _mass = 15;
    _maxSpeed = Point{2, 4};
    EntityWanderState state;
    _entityStateMachine = std::make_unique<EntityStateMachine>(state);
}

void ForceDrivenEntityBody::SetLookAhead(double lookAhead) {
    _lookAhead = lookAhead;
}

double ForceDrivenEntityBody::GetLookAhead() {
    return _lookAhead;
}

void ForceDrivenEntityBody::AddNearbyCollider(Collider &collider) {
    _nearbyColliders.push_back(collider);
}

auto ForceDrivenEntityBody::GetFollowing() -> std::weak_ptr<GameObject> {
    return _following;
}
