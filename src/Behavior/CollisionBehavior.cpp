#include "CollisionBehavior.hpp"
#include "Input.hpp"
#include "GameObject.hpp"
#include "RigidBody.hpp"

namespace platformer_engine {

    void CollisionBehavior::OnStart() {
        spic::Input::GetMouseButton(spic::Input::MouseButton::RIGHT);
        BehaviourScript::OnStart();
    }

    void CollisionBehavior::OnUpdate() {
        BehaviourScript::OnUpdate();
    }

    void CollisionBehavior::OnTriggerEnter2D(const Collision collision) {
        auto collider = collision.GetCollider();
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

        //todo: In the gameobject this behavior belongs to; set a 'canMoveRight' and 'CanMoveLeft' values
//        BehaviourScript::OnTriggerEnter2D(collision);
    }

    void CollisionBehavior::OnTriggerExit2D(const Collision collision) {
        auto point = collision.Contact();

        auto gameObjWeak = GetGameObject();
        std::shared_ptr<spic::GameObject> gameObj { gameObjWeak.lock() };
        if (gameObj) {
            auto body = std::static_pointer_cast<RigidBody>(gameObj->GetComponent<RigidBody>());
            if(body != nullptr) {
                body->AllowMoveTo(point);
            }
        } else { // gameObjWeak is already deleted
            gameObjWeak.reset();
        }
    }

    void CollisionBehavior::OnTriggerStay2D(const Collision collision) {
//        BehaviourScript::OnTriggerStay2D(collision);
    }
} // platformer_engine