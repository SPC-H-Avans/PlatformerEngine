#include "Physics/ForceDrivenEntityBody.hpp"

void ForceDrivenEntityBody::Update(double time_elapsed) {
    //calculate the combined force from each steering behavior in the
    //vehicle’s list
    Point steeringForce = _behaviours->Pursuit(_following);

    AddForce(steeringForce);
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
