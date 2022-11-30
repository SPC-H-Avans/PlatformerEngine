#include "Behaviour/DynamicAnimationBehaviour.hpp"
#include "GameObject.hpp"
#include "RigidBody.hpp"
#include "BoxCollider.hpp"
#include "Physics/PlayerRigidBody.hpp"
#include "Animator.hpp"

namespace platformer_engine {

    DynamicAnimationBehaviour::DynamicAnimationBehaviour(std::shared_ptr<platformer_engine::AnimatedSprite> idleSprite,
                                                         std::shared_ptr<platformer_engine::AnimatedSprite> walkSprite,
                                                         std::shared_ptr<platformer_engine::AnimatedSprite> jumpSprite)
            : _idleSprite(idleSprite), _walkSprite(walkSprite), _jumpSprite(jumpSprite)
    { }

    void DynamicAnimationBehaviour::OnUpdate() {
        auto player = GetGameObject().lock();
        auto playerRigidBody = std::dynamic_pointer_cast<PlayerRigidBody>(player->GetComponent<RigidBody>());
        auto playerAnimator = std::dynamic_pointer_cast<Animator>(player->GetComponent<Animator>());
        if (playerRigidBody != nullptr && playerAnimator != nullptr) {
            if (playerRigidBody->YVelocity() != 0) {
                playerAnimator->SetActiveAnimation(_jumpSprite->GetSpriteId());
            } else if (playerRigidBody->XVelocity() > 0.1 || playerRigidBody->XVelocity() < -0.1) {
                playerAnimator->SetActiveAnimation(_walkSprite->GetSpriteId());
            } else {
                playerAnimator->SetActiveAnimation(_idleSprite->GetSpriteId());
            }
        }
    }
}  // namespace platformer_engine