#ifndef PLATFORMER_ENGINE_FORCEDRIVENENTITYBODY_HPP
#define PLATFORMER_ENGINE_FORCEDRIVENENTITYBODY_HPP

#include "RigidBody.hpp"
#include "EntityState/EntityStateMachine.hpp"

class ForceDrivenEntityBody : public RigidBody, public std::enable_shared_from_this<ForceDrivenEntityBody> {

public:
    explicit ForceDrivenEntityBody(float friction);
    void FollowOn();
    void WanderOn();

    void SetGameObject(std::weak_ptr<GameObject> gObj) override {
        Component::SetGameObject(gObj);
    }

    void SetLookAhead(double lookAhead);
    auto GetLookAhead() -> double;
    auto GetFollowRange() -> double;
    auto GetFollowing() -> std::weak_ptr<GameObject>;
    void SetFollowing(const std::shared_ptr<GameObject>& gameObject, double range);

    void AddNearbyCollider(Collider &collider);
    auto CalcSteeringForce() -> Point;

private:
    std::unique_ptr<EntityStateMachine> _entityStateMachine;
    std::weak_ptr<GameObject> _following;
    double _lookAhead = 0;
    double _range = 0;
    std::vector<Collider> _nearbyColliders;

    Point AvoidObjects();

    void UpdateLookAhead();
};


#endif //PLATFORMER_ENGINE_FORCEDRIVENENTITYBODY_HPP
