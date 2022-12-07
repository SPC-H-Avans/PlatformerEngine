#include "Physics/ForceDrivenEntityBody.hpp"
#include "BoxCollider.hpp"

void ForceDrivenEntityBody::Update(double time_elapsed) {
    //calculate the combined force from each steering behavior in the
    //vehicle’s list
    Point pursuitForce = _behaviours->Pursuit(_following);
    Point avoidForce = AvoidObjects();

    Point steeringForce = pursuitForce + avoidForce;
    if(steeringForce.y < 0 && _mass != 0) {
        steeringForce.y *= 15;
    }

    UpdateLookAhead();

    AddForce(steeringForce);
}

Point ForceDrivenEntityBody::AvoidObjects() {

    Point steeringForce = Point{0, 0};

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

        // If we found a nearest collision, calculate a steering force
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

void ForceDrivenEntityBody::Follow(const std::shared_ptr<GameObject>& gameObject) {
    _following = gameObject;
}

ForceDrivenEntityBody::ForceDrivenEntityBody(float friction) : RigidBody(friction), _lookAhead(25) {
    _gravityScale = 0.055;
    _mass = 8;
    _maxSpeed = Point{2, 7};
    _behaviours = std::make_unique<platformer_engine::ForceDrivenEntityBehaviours>(GetGameObject());
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
