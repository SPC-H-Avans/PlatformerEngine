#ifndef PLATFORMER_ENGINE_FORCEDRIVENENTITYBODY_HPP
#define PLATFORMER_ENGINE_FORCEDRIVENENTITYBODY_HPP

#include "RigidBody.hpp"
#include "Behaviour/ForceDrivenEntityBehaviours.hpp"
#include "EntityState/EntityStateMachine.hpp"

class ForceDrivenEntityBody : public RigidBody, std::enable_shared_from_this<ForceDrivenEntityBody> {

public:
    ForceDrivenEntityBody(float friction);
    void FollowOn();
    void WanderOn();

    void SetGameObject(std::weak_ptr<GameObject> gObj) override {
        Component::SetGameObject(gObj);
        _behaviours->SetGameObject(gObj);
    }

    void SetLookAhead(double lookAhead);
    auto GetLookAhead() -> double;
    auto GetFollowing() -> std::weak_ptr<GameObject>;
    void SetFollowing(const std::shared_ptr<GameObject>& gameObject);

    void AddNearbyCollider(Collider &collider);
    auto CalcSteeringForce() -> Point;

private:
    //the steering behavior class
    std::unique_ptr<platformer_engine::ForceDrivenEntityBehaviours> _behaviours;
    std::unique_ptr<EntityStateMachine> _entityStateMachine;
    std::weak_ptr<GameObject> _following;
    double _lookAhead = 0;
    std::vector<Collider> _nearbyColliders;

    Point AvoidObjects();

    void UpdateLookAhead();
};


#endif //PLATFORMER_ENGINE_FORCEDRIVENENTITYBODY_HPP
