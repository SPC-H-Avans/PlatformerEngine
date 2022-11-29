#ifndef PLATFORMER_ENGINE_DYNAMICANIMATIONBEHAVIOUR_HPP
#define PLATFORMER_ENGINE_DYNAMICANIMATIONBEHAVIOUR_HPP

#include "BehaviourScript.hpp"
#include "Texture/AnimatedSprite.hpp"

namespace platformer_engine {

    class DynamicAnimationBehaviour : public spic::BehaviourScript {
    public:
        DynamicAnimationBehaviour(std::shared_ptr<platformer_engine::AnimatedSprite> idleSprite,
                                  std::shared_ptr<platformer_engine::AnimatedSprite> walkSprite,
                                  std::shared_ptr<platformer_engine::AnimatedSprite> jumpSprite);
        void OnUpdate() override;
    private:
        std::shared_ptr<platformer_engine::AnimatedSprite> _idleSprite;
        std::shared_ptr<platformer_engine::AnimatedSprite> _walkSprite;
        std::shared_ptr<platformer_engine::AnimatedSprite> _jumpSprite;
    };

}  // namespace platformer_engine

#endif //PLATFORMER_ENGINE_DYNAMICANIMATIONBEHAVIOUR_HPP
