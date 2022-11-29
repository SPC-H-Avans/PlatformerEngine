#include "Behaviour/DynamicAnimationBehaviour.hpp"
#include "GameObject.hpp"
#include "RigidBody.hpp"
#include "BoxCollider.hpp"
#include "Physics/MarioRigidBody.hpp"
#include "Animator.hpp"

namespace platformer_engine {

    DynamicAnimationBehaviour::DynamicAnimationBehaviour(std::shared_ptr<platformer_engine::AnimatedSprite> idleSprite,
                                                         std::shared_ptr<platformer_engine::AnimatedSprite> walkSprite,
                                                         std::shared_ptr<platformer_engine::AnimatedSprite> jumpSprite)
            : _idleSprite(idleSprite), _walkSprite(walkSprite), _jumpSprite(jumpSprite)
    { }

    void DynamicAnimationBehaviour::OnUpdate() {
        auto mario = GetGameObject().lock();
        auto marioRigidBody = std::dynamic_pointer_cast<MarioRigidBody>(mario->GetComponent<RigidBody>());
        auto marioAnimator = std::dynamic_pointer_cast<Animator>(mario->GetComponent<Animator>());
        if (marioRigidBody != nullptr && marioAnimator != nullptr) {
            if (marioRigidBody->YVelocity() > 0.1) {
                marioAnimator->SetActiveAnimation(_jumpSprite->GetSpriteId());
            } else if (marioRigidBody->XVelocity() > 0.1 || marioRigidBody->XVelocity() < -0.1) {
                marioAnimator->SetActiveAnimation(_walkSprite->GetSpriteId());
            } else {
                marioAnimator->SetActiveAnimation(_idleSprite->GetSpriteId());
            }
        }
    }
}  // namespace platformer_engine