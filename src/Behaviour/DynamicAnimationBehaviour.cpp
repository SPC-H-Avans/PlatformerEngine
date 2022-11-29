#include "Behaviour/DynamicAnimationBehaviour.hpp"
#include "GameObject.hpp"
#include "RigidBody.hpp"
#include "BoxCollider.hpp"
#include "Physics/MarioRigidBody.hpp"
#include "Input.hpp"

namespace platformer_engine {

    DynamicAnimationBehaviour::DynamicAnimationBehaviour(std::shared_ptr<platformer_engine::AnimatedSprite> idleSprite,
                                                         std::shared_ptr<platformer_engine::AnimatedSprite> walkSprite,
                                                         std::shared_ptr<platformer_engine::AnimatedSprite> jumpSprite)
                                                         : _idleSprite(idleSprite), _walkSprite(walkSprite), _jumpSprite(jumpSprite)
                                                         { }

    void DynamicAnimationBehaviour::OnUpdate() {
        auto mario = GetGameObject().lock();
        auto marioRigidBody = std::dynamic_pointer_cast<MarioRigidBody>(mario->GetComponent<RigidBody>());
        auto marioSprite = std::dynamic_pointer_cast<AnimatedSprite>(mario->GetComponent<AnimatedSprite>());
        if (marioRigidBody != nullptr && marioSprite != nullptr) {
            if (marioRigidBody->YVelocity() > 0) {
                marioSprite = _jumpSprite;
            } else if (marioRigidBody->XVelocity() != 0) {
                marioSprite = _walkSprite;
            } else {
                marioSprite = _idleSprite;
            }
        }
    }
}  // namespace platformer_engine