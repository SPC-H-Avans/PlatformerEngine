#include "Behaviour/MarioInputBehaviour.hpp"
#include "GameObject.hpp"
#include "RigidBody.hpp"
#include "BoxCollider.hpp"
#include "Physics/MarioRigidBody.hpp"
#include "Input.hpp"

namespace platformer_engine {

    void MarioInputBehaviour::OnUpdate() {
        auto mario = GetGameObject().lock();
        auto marioRigidBody = std::dynamic_pointer_cast<MarioRigidBody>(mario->GetComponent<RigidBody>());
        if (marioRigidBody != nullptr) {
            auto point = Point();

            if (spic::Input::GetKey(spic::Input::KeyCode::LEFT_ARROW)) {
                point.x--;
            }
            if (spic::Input::GetKey(spic::Input::KeyCode::RIGHT_ARROW)) {
                point.x++;
            }
            if (spic::Input::GetKey(spic::Input::KeyCode::UP_ARROW)) {
                point.y++;
            }

            marioRigidBody->AddForce(point);
        }
    }
}  // namespace platformer_engine