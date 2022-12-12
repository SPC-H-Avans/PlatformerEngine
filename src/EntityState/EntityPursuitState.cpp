#include "EntityState/EntityPursuitState.hpp"
#include "Physics/ForceDrivenEntityBody.hpp"
#include <memory>
#include "GameObject.hpp"

auto EntityPursuitState::CalculateForce(std::shared_ptr<RigidBody> &rigidBody) -> Point {

    auto entityBody = std::dynamic_pointer_cast<ForceDrivenEntityBody>(rigidBody);
    if(!entityBody) {
        return {0,0};
    }

    std::shared_ptr<GameObject> gameObject{entityBody->GetGameObject().lock()};
    std::shared_ptr<GameObject> evader{entityBody->GetFollowing().lock()};
    if (gameObject && evader) {
        auto evaderBody = std::dynamic_pointer_cast<RigidBody>(evader->GetComponent<RigidBody>());
        if(evaderBody != nullptr) {
            //if the evader is ahead and facing the agent then we can just seek
            //for the evader's current position.
            Point ToEvader = evader->GetTransform().position - gameObject->GetTransform().position;
            double RelativeHeading = entityBody->GetHeading().Dot(evaderBody->GetHeading());
            if ((ToEvader.Dot(entityBody->GetHeading()) > 0) &&
                (RelativeHeading < -0.95)) //acos(0.95)=18 degs
            {
                return Seek(gameObject, evader->GetTransform().position);
            }
            //Not considered ahead so we predict where the evader will be.
            //the look-ahead time is proportional to the distance between the evader
            //and the pursuer; and is inversely proportional to the sum of the
            //agents' velocities
            double LookAheadTime = ToEvader.Length() /
                                   (entityBody->GetMaxSpeed().x + evaderBody->GetVelocity().Length());
            //now seek to the predicted future position of the evader
            return Seek(gameObject, evader->GetTransform().position + evaderBody->GetVelocity() * LookAheadTime);
        }
    }
    gameObject.reset();
    return {0, 0};
}

auto EntityPursuitState::Seek(const std::shared_ptr<GameObject>& gameObject, Point targetPos) -> Point {
    auto transform = gameObject->GetTransform();
    auto body = std::dynamic_pointer_cast<RigidBody>(gameObject->GetComponent<RigidBody>());
    Point DesiredVelocity = spic::Point::PointNormalize(targetPos - transform.position)
                                * body->GetMaxSpeed();
    return (DesiredVelocity - body->GetVelocity());
}

auto EntityPursuitState::Clone() const -> std::unique_ptr<EntityState> {
    return std::make_unique<EntityPursuitState>(*this);
}
