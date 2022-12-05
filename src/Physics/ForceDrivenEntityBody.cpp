#include "Physics/ForceDrivenEntityBody.hpp"

void ForceDrivenEntityBody::Update(double time_elapsed) {
    //calculate the combined force from each steering behavior in the
    //vehicle’s list
    Point SteeringForce = _behaviours->Pursuit(_following);

//    //Acceleration = Force/Mass
//    Point acceleration = SteeringForce / _mass;
//
//    //update velocity
//    auto velocityIncrement = acceleration * time_elapsed;
//    _velocity += velocityIncrement;
//
//    //make sure vehicle does not exceed maximum velocity
//    _velocity.Truncate(_maxSpeed.x);

    AddForce(SteeringForce);

//    //update the position
//    auto positionIncrement = _velocity * time_elapsed;
//
//    std::shared_ptr<GameObject> gameObject{GetGameObject().lock()};
//    if (gameObject) {
//        auto transform = gameObject->GetTransform();
//        transform.position += positionIncrement;
//        gameObject->SetTransform(transform);
//    } else { // GameObject was already deleted
//        gameObject.reset();
//    }
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
