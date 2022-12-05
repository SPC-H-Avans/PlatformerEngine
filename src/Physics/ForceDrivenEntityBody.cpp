#include "Physics/ForceDrivenEntityBody.hpp"

void ForceDrivenEntityBody::Update(double time_elapsed) {
    //calculate the combined force from each steering behavior in the
    //vehicle’s list
    Point SteeringForce = _behaviours->Pursuit(_following);



    //Acceleration = Force/Mass
    Point acceleration = SteeringForce / _mass;

    //update velocity
    auto accelerationTime = acceleration * time_elapsed;
    _velocity += accelerationTime;

    //make sure vehicle does not exceed maximum velocity
    _velocity.Truncate(_maxSpeed.x);

    std::shared_ptr<GameObject> gameObject{GetGameObject().lock()};
    if (gameObject) {

        auto transform = gameObject->GetTransform();

        //keep a record of its old position so we can update its cell later
        //in this method
        Point OldPos = transform.position;

        //update the position

        transform.position += _velocity;
        gameObject->SetTransform(transform);

        //update the heading if the vehicle has a non zero velocity
        if (_velocity.LengthSq() > 0.00000001)
        {
            _heading = Point::PointNormalize(_velocity);

            //m_vSide = m_vHeading.Perp();
        }
    } else {
        gameObject.reset();
    }



//    //Acceleration = Force/Mass
//    Point acceleration = SteeringForce / _mass;
//
//    //update velocity
//    auto velocityIncrement = acceleration * time_elapsed;
//    _velocity += velocityIncrement;
//
//    //make sure vehicle does not exceed maximum velocity
//    _velocity.Truncate(_maxSpeed.x);

   // AddForce(SteeringForce);

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
