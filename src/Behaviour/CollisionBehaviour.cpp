#include "Behaviour/CollisionBehaviour.hpp"
#include "Input.hpp"
#include "GameObject.hpp"
#include "RigidBody.hpp"

namespace platformer_engine {

    void CollisionBehaviour::OnStart() {
    }

    void CollisionBehaviour::OnUpdate() {
    }

    void CollisionBehaviour::OnTriggerEnter2D(const Collision collision) {
        _activeCollisions.push_back(collision);
        auto point = collision.Contact();

        auto gameObjWeak = GetGameObject();
        std::shared_ptr<spic::GameObject> gameObj { gameObjWeak.lock() };
        if (gameObj) {
            auto body = std::static_pointer_cast<RigidBody>(gameObj->GetComponent<RigidBody>());
            if(body != nullptr) {
                body->DenyMoveTo(point);
            }
        } else { // gameObjWeak is already deleted
            gameObjWeak.reset();
        }
    }

    void CollisionBehaviour::OnTriggerExit2D(const Collision collision) {

        // Remove the collision from _activeCollisions
        for(auto &col : _activeCollisions) {
            int currentId = col.GetId();
            if(currentId == collision.GetId()) {
                auto new_end = std::remove_if(_activeCollisions.begin(), _activeCollisions.end(),
                                              [currentId](const Collision & col) { return col.GetId() == currentId; });
                _activeCollisions.erase(new_end, _activeCollisions.end());
            }
        }

        auto point = collision.Contact();
        auto gameObjWeak = GetGameObject();
        std::shared_ptr<spic::GameObject> gameObj { gameObjWeak.lock() };
        if (gameObj) {
            auto body = std::static_pointer_cast<RigidBody>(gameObj->GetComponent<RigidBody>());
            if(body != nullptr && CanMoveTo(point)) {
                body->AllowMoveTo(point);
            }
        } else { // gameObjWeak is already deleted
            gameObjWeak.reset();
        }
    }

    void CollisionBehaviour::OnTriggerStay2D(const Collision collision) {
        for(auto &col : _activeCollisions) {
            col.Contact(collision.Contact()); // Update the contact point (for if an object could move through another)
        }
    }

    bool CollisionBehaviour::CanMoveTo(CollisionPoint point) {
        for(auto &col : _activeCollisions) {
            if(col.Contact() == point) {
                return false;
            }
        }
        return true;
    }
}  // namespace platformer_engine