#include "Physics/ForceDrivenEntityBody.hpp"

void ForceDrivenEntityBody::Update(double time_elapsed) {
    //calculate the combined force from each steering behavior in the
    //vehicle’s list
    Point SteeringForce = _behaviours->Calculate();

    //Acceleration = Force/Mass
    Point acceleration = SteeringForce / _mass;

    //update velocity
    auto velocityIncrement = acceleration * time_elapsed;
    _velocity += velocityIncrement;

    //make sure vehicle does not exceed maximum velocity
    _velocity.Truncate(_maxSpeed.x);

    //update the position
    auto positionIncrement = _velocity * time_elapsed;

    std::shared_ptr<GameObject> gameObject{GetGameObject().lock()};
    if (gameObject) {
        auto transform = gameObject->GetTransform();
        transform.position += positionIncrement;
        gameObject->SetTransform(transform);
    } else { // GameObject was already deleted
        gameObject.reset();
    }
}
