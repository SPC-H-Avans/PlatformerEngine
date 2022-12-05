#include "Behaviour/ForceDrivenEntityBehaviours.hpp"

#include <utility>
#include "Point.hpp"
#include "RigidBody.hpp"

using spic::Point;
using platformer_engine::ForceDrivenEntityBehaviours;

auto ForceDrivenEntityBehaviours::Seek(Point targetPos) -> Point {
    std::shared_ptr<GameObject> gameObject{_gameObject.lock()};
    if (gameObject) {
        auto transform = gameObject->GetTransform();
        auto body = std::dynamic_pointer_cast<RigidBody>(gameObject->GetComponent<RigidBody>());
        Point DesiredVelocity = spic::Point::PointNormalize(targetPos - transform.position)
                                * body->GetMaxSpeed();
        return (DesiredVelocity - body->GetVelocity());
    }
    // GameObject was already deleted
    gameObject.reset();
    return {};
}

auto ForceDrivenEntityBehaviours::Flee(Point &targetPos) -> Point {

//    //only flee if the target is within 'panic distance'. Work in distance
//    //squared space.
//    const double PanicDistanceSq = 100.0 * 100.0;
//    if (Vec2DDistanceSq(m_pVehicle->Pos(), target) > PanicDistanceSq)
//    {
//        return Vector2D(0,0);
//    }

    std::shared_ptr<GameObject> gameObject{_gameObject.lock()};
    if (gameObject) {
        auto transform = gameObject->GetTransform();
        auto body = std::dynamic_pointer_cast<RigidBody>(gameObject->GetComponent<RigidBody>());
        auto DesiredVelocity = spic::Point::PointNormalize(transform.position - targetPos)
                               * body->GetMaxSpeed();
        return (DesiredVelocity - body->GetVelocity());
        return (DesiredVelocity - body->GetVelocity());
    }
    // GameObject was already deleted
    gameObject.reset();
    return {};
}

auto ForceDrivenEntityBehaviours::Arrive(Point &TargetPos,
                                          Deceleration deceleration) -> Point {
    std::shared_ptr<GameObject> gameObject{_gameObject.lock()};
    if (gameObject) {
        Point ToTarget = TargetPos - gameObject->GetTransform().position;
        auto body = std::dynamic_pointer_cast<RigidBody>(gameObject->GetComponent<RigidBody>());

        //calculate the distance to the target position
        double dist = ToTarget.Length();
        if (dist > 0 && body != nullptr) {
            //because Deceleration is enumerated as an int, this value is required
            //to provide fine tweaking of the deceleration.
            const double DecelerationTweaker = 0.3;
            //calculate the speed required to reach the target given the desired
            //deceleration
            double speed = dist / (static_cast<double>(deceleration) * DecelerationTweaker);
            //make sure the velocity does not exceed the max
            speed = std::min(speed, body->GetMaxSpeed().x);
            //from here proceed just like Seek except we don't need to normalize
            //the ToTarget vector because we have already gone to the trouble
            //of calculating its length: dist.
            auto DesiredVelocity = ToTarget * speed / dist;
            return (DesiredVelocity - body->GetVelocity());
        }
    } else {
        gameObject.reset();
    }
    return Point{0, 0};
}

auto platformer_engine::ForceDrivenEntityBehaviours::Pursuit(const std::weak_ptr<GameObject>& evaderWeakPtr) -> Point {
    std::shared_ptr<GameObject> gameObject{_gameObject.lock()};
    std::shared_ptr<GameObject> evader{evaderWeakPtr.lock()};
    if (gameObject && evader) {
        auto body = std::dynamic_pointer_cast<RigidBody>(gameObject->GetComponent<RigidBody>());
        auto evaderBody = std::dynamic_pointer_cast<RigidBody>(evader->GetComponent<RigidBody>());
        if(body != nullptr) {
            //if the evader is ahead and facing the agent then we can just seek
            //for the evader's current position.
            Point ToEvader = evader->GetTransform().position - gameObject->GetTransform().position;
            double RelativeHeading = body->GetHeading().Dot(evaderBody->GetHeading());
            if ((ToEvader.Dot(body->GetHeading()) > 0) &&
                (RelativeHeading < -0.95)) //acos(0.95)=18 degs
            {
                return Seek(evader->GetTransform().position);
            }
            //Not considered ahead so we predict where the evader will be.
            //the look-ahead time is proportional to the distance between the evader
            //and the pursuer; and is inversely proportional to the sum of the
            //agents' velocities
            double LookAheadTime = ToEvader.Length() /
                                   (body->GetMaxSpeed().x + evaderBody->GetVelocity().Length());
            //now seek to the predicted future position of the evader
            return Seek(evader->GetTransform().position + evaderBody->GetVelocity() * LookAheadTime);
        }
    }
    gameObject.reset();
    return {0, 0};
}

Point ForceDrivenEntityBehaviours::Calculate() {
//    Point SteeringForce;
//    SteeringForce += Pursuit();
////    SteeringForce += ObstacleAvoidance() * dObstacleAvoidanceAmount;
////    SteeringForce += Separation() * dSeparationAmount;
//    return SteeringForce.Truncate(20.0);

    return {};
}

Point ForceDrivenEntityBehaviours::ForwardComponent() {
    return {};
}

Point ForceDrivenEntityBehaviours::SideComponent() {
    return {};
}

void ForceDrivenEntityBehaviours::SetPath() {

}

void ForceDrivenEntityBehaviours::SetTarget(Point point) {

}

void ForceDrivenEntityBehaviours::SetTargetAgent1(std::shared_ptr<GameObject> targetAgent) {

}

void ForceDrivenEntityBehaviours::SetTargetAgent2(std::shared_ptr<GameObject> targetAgent) {

}

void ForceDrivenEntityBehaviours::SeekOn() {

}

void ForceDrivenEntityBehaviours::FleeOn() {

}

void ForceDrivenEntityBehaviours::ArriveOn() {

}

void ForceDrivenEntityBehaviours::SeekOff() {

}

void ForceDrivenEntityBehaviours::FleeOff() {

}

void ForceDrivenEntityBehaviours::ArriveOff() {

}

platformer_engine::ForceDrivenEntityBehaviours::ForceDrivenEntityBehaviours(std::weak_ptr<GameObject> gameObject)
        : _gameObject(std::move(gameObject)) {

}


