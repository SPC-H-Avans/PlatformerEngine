#include "Physics/ForceDrivenEntityBody.hpp"

void ForceDrivenEntityBody::Update(double time_elapsed) {
    //calculate the combined force from each steering behavior in the
    //vehicle’s list
    Point steeringForce = _behaviours->Pursuit(_following);
    steeringForce = AvoidObjects() + steeringForce;

    AddForce(steeringForce);
}

Point ForceDrivenEntityBody::AvoidObjects() {

    Point steeringForce = Point{0, 0};

    std::shared_ptr<GameObject> currentGameObject { GetGameObject().lock() };
    if(currentGameObject) {

        // Get the look ahead collider
        std::shared_ptr<Collider> lookAheadCollider = nullptr;

        auto colliders = currentGameObject->GetComponents<Collider>();
        for(auto& colComponent : colliders) {
            auto col = std::dynamic_pointer_cast<Collider>(colComponent);
            if(!col->GetPosition().Equals(currentGameObject->GetTransform().position)) {
                lookAheadCollider = col;
            }
        }

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
            // Calculate the direction to the nearest collision
            Point collisionDirection = Point::PointNormalize(nearest->GetPosition() - currentGameObject->GetTransform().position);

            auto maxNegativeForce = _maxSpeed.x / _mass * -1;

            // Calculate the steering force to avoid the collision
            steeringForce = collisionDirection * maxNegativeForce;
        }

    } else {
        currentGameObject.reset();
    }



    // Return the steering force
    return steeringForce;
}

void ForceDrivenEntityBody::UpdateColliders(Point oldPos) {

    std::shared_ptr<GameObject> gameObject{GetGameObject().lock()};
    if (gameObject) {
        auto colliders = gameObject->GetComponents<Collider>();
        for(auto &colObj : colliders) {
            auto col = std::dynamic_pointer_cast<Collider>(colObj);
            if(col->GetPosition().Equals(oldPos)) {
                // This collider is the main collider, so it should get the same position as the gameObject
                col->SetPosition(gameObject->GetTransform().position);
            } else {
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

ForceDrivenEntityBody::ForceDrivenEntityBody(float friction) : RigidBody(friction) {
    _gravityScale = 0;
    _mass = 10;
    _maxSpeed = Point{2, 2};
    _behaviours = std::make_unique<platformer_engine::ForceDrivenEntityBehaviours>(GetGameObject());

}

void ForceDrivenEntityBody::SetLookAhead(double lookAhead) {
    _lookAhead = lookAhead;
}

double ForceDrivenEntityBody::GetLookAhead() {
    return _lookAhead;
}
