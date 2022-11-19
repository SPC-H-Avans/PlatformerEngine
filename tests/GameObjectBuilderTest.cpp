#include <gtest/gtest.h>
#include "Builder/GameObjectBuilder.hpp"

class GameObjectBuilderTest : public ::testing::Test {

};

TEST_F(GameObjectBuilderTest, DoesReturnGameObject) {
    auto gameObject = GameObjectBuilder("test").GetGameObject();
    ASSERT_TRUE(gameObject != nullptr);
    ASSERT_EQ(gameObject->GetName(), "test");
}


TEST_F(GameObjectBuilderTest, IsAnimatorAdded) {

    GameObjectBuilder gameObjectBuilder = GameObjectBuilder("speler");
    auto animatedSprite = std::make_shared<platformer_engine::AnimatedSprite>("mario_Jump", 1, 1, 24, 24, 3, 100, 1,
                                                                              platformer_engine::FLIP_NONE,
                                                                              Color::Transparent(), 4.0);
    gameObjectBuilder.AddAnimator(animatedSprite);
    auto gameObject = gameObjectBuilder.GetGameObject();
    ASSERT_TRUE(gameObject->GetComponent<Animator>() != nullptr);
}

TEST_F(GameObjectBuilderTest, AreAnimatorsAdded) {

    GameObjectBuilder gameObjectBuilder = GameObjectBuilder("speler");
    auto animatedSprite = std::make_shared<platformer_engine::AnimatedSprite>("mario_Jump", 1, 1, 24, 24, 3, 100, 1,
                                                                              platformer_engine::FLIP_NONE,
                                                                              Color::Transparent(), 4.0);
    auto animatedSprite2 = std::make_shared<platformer_engine::AnimatedSprite>("mario_Jump2", 1, 1, 24, 24, 3, 100, 1,
                                                                               platformer_engine::FLIP_NONE,
                                                                               Color::Transparent(), 4.0);

    auto animators = std::vector<std::shared_ptr<platformer_engine::AnimatedSprite>>();
    animators.push_back(animatedSprite);
    animators.push_back(animatedSprite2);
    gameObjectBuilder.AddAnimator(animators);
    auto gameObject = gameObjectBuilder.GetGameObject();
    auto animatorComponent = gameObject->GetComponent<Animator>();
    ASSERT_TRUE(animatorComponent != nullptr);
    auto animator = std::static_pointer_cast<spic::Animator>(animatorComponent);

    ASSERT_TRUE(animator->GetLoadedAnimations().contains("mario_Jump"));
    ASSERT_TRUE(animator->GetLoadedAnimations().contains("mario_Jump2"));
}

TEST_F(GameObjectBuilderTest, CanAddSprite) {
    GameObjectBuilder gameObjectBuilder = GameObjectBuilder("speler");

    auto spritePtr = std::make_shared<spic::Sprite>("mario_Jump", 1, 1, 24, 24,
                                                    platformer_engine::FLIP_NONE,
                                                    Color::Transparent(), 4.0);
    gameObjectBuilder.AddSprite(spritePtr);
    auto gameObject = gameObjectBuilder.GetGameObject();
    auto spriteComponent = gameObject->GetComponent<Sprite>();

    ASSERT_TRUE(spriteComponent != nullptr);
    auto sprite = std::static_pointer_cast<spic::Sprite>(spriteComponent);
    ASSERT_EQ(sprite->GetSpriteId(), "mario_Jump");
    ASSERT_EQ(sprite->GetSpriteScale(), 4.0);
}