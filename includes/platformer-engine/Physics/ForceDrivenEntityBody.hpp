#ifndef PLATFORMER_ENGINE_FORCEDRIVENENTITYBODY_HPP
#define PLATFORMER_ENGINE_FORCEDRIVENENTITYBODY_HPP

#include "RigidBody.hpp"
#include "Behaviour/ForceDrivenEntityBehaviours.hpp"

class ForceDrivenEntityBody : public RigidBody {

public:
    ForceDrivenEntityBody(float friction);
    void Update(double time_elapsed);
    void Follow(const std::shared_ptr<GameObject>& gameObject);

    void SetGameObject(std::weak_ptr<GameObject> gObj) override {
        Component::SetGameObject(gObj);
        _behaviours->SetGameObject(gObj);
    }

    void SetLookAhead(double lookAhead);
    auto GetLookAhead() -> double;

    void AddNearbyCollider(Collider &collider);

private:
    //the steering behavior class
    std::unique_ptr<platformer_engine::ForceDrivenEntityBehaviours> _behaviours;
    std::weak_ptr<GameObject> _following;
    double _lookAhead = 0;
    std::vector<Collider> _nearbyColliders;

    Point AvoidObjects();

    void UpdateLookAhead();

};


#endif //PLATFORMER_ENGINE_FORCEDRIVENENTITYBODY_HPP
