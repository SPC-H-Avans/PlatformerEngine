#include <gtest/gtest.h>
#include "Builder/GameObjectBuilder.hpp"
#include "Engine/Engine.hpp"
#include "Builder/SceneBuilder.hpp"

/**
 * @brief GameObjectBuilder Tests
 */
class GameObjectBuilderTest : public ::testing::Test {

    void SetUp() override {
        platformer_engine::Engine &engine = platformer_engine::Engine::GetInstance();
        engine.Init(1000, 1000, "Mario Game", spic::Color::Cyan(), false);
        platformer_engine::SceneBuilder builder = platformer_engine::SceneBuilder("levelGameObjectBuilderTest");
        engine.AddScene(builder.GetScene());
        engine.QueueActiveScene("levelGameObjectBuilderTest");
    }
};

/**
 * @brief Tests if the GameObjectBuilder can build a GameObject
 */
TEST_F(GameObjectBuilderTest, DoesReturnGameObject) {
    auto gameObject = GameObjectBuilder("test").GetGameObject();
    ASSERT_TRUE(gameObject != nullptr) << "GameObjectBuilder should return a GameObject";
    ASSERT_EQ(gameObject->GetName(), "test") << "GameObjectBuilder should return a GameObject with the given name";
}

/**
 * @brief Tests if the GameObjectBuilder can build a GameObject with an Animator
 */
TEST_F(GameObjectBuilderTest, IsAnimatorAdded) {

    GameObjectBuilder gameObjectBuilder = GameObjectBuilder("speler");
    auto animatedSprite = platformer_engine::AnimatedSprite("mario_Jump", 24, 24, 3, 1, 1, 100, 1,
                                                                              platformer_engine::FLIP_NONE,
                                                                              Color::Transparent(), 4.0);
    gameObjectBuilder.AddAnimator(animatedSprite);
    auto gameObject = gameObjectBuilder.GetGameObject();
    ASSERT_TRUE(gameObject->GetComponent<Animator>() != nullptr)
                                << "GameObjectBuilder should add an Animator to the GameObject";
}

/**
 * @brief Tests if the GameObjectBuilder can build a GameObject with multiple Animators
 */
TEST_F(GameObjectBuilderTest, AreAnimatorsAdded) {

    GameObjectBuilder gameObjectBuilder = GameObjectBuilder("speler");
    auto animatedSprite = platformer_engine::AnimatedSprite("mario_Jump", 24, 24, 3, 1, 1, 100, 1,
                                                                              platformer_engine::FLIP_NONE,
                                                                              Color::Transparent(), 4.0);
    auto animatedSprite2 = platformer_engine::AnimatedSprite("mario_Jump2", 24, 24, 3, 1, 1, 100, 1,
                                                                               platformer_engine::FLIP_NONE,
                                                                               Color::Transparent(), 4.0);

    auto animators = std::vector<platformer_engine::AnimatedSprite>();
    animators.push_back(animatedSprite);
    animators.push_back(animatedSprite2);
    gameObjectBuilder.AddAnimator(animators);
    auto gameObject = gameObjectBuilder.GetGameObject();
    auto animatorComponent = gameObject->GetComponent<Animator>();
    ASSERT_TRUE(animatorComponent != nullptr) << "GameObjectBuilder should add an Animator to the GameObject";
    auto animator = std::static_pointer_cast<spic::Animator>(animatorComponent);

    ASSERT_TRUE(animator->GetLoadedAnimations().contains("mario_Jump"))
                                << "Animator should have loaded an animation with ID: mario_Jump";
    ASSERT_TRUE(animator->GetLoadedAnimations().contains("mario_Jump2"))
                                << "Animator should have loaded an animation with ID: mario_Jump2";
}

/**
 * @brief Tests if the GameObjectBuilder can build a GameObject with a Sprite
 */
TEST_F(GameObjectBuilderTest, CanAddSprite) {
    GameObjectBuilder gameObjectBuilder = GameObjectBuilder("speler");

    auto spritePtr = spic::Sprite("mario_Jump", 24, 24, 1, 1,
                                                    platformer_engine::FLIP_NONE,
                                                    Color::Transparent(), 4.0);
    gameObjectBuilder.AddSprite(spritePtr);
    auto gameObject = gameObjectBuilder.GetGameObject();
    auto spriteComponent = gameObject->GetComponent<Sprite>();

    ASSERT_TRUE(spriteComponent != nullptr) << "GameObjectBuilder should add a Sprite to the GameObject";
    auto sprite = std::static_pointer_cast<spic::Sprite>(spriteComponent);
    ASSERT_EQ(sprite->GetSpriteId(), "mario_Jump") << "Sprite ID should be mario_Jump";
    ASSERT_EQ(sprite->GetSpriteScale(), 4.0) << "Sprite scale should be 4.0";
    ASSERT_NO_THROW(sprite->Render(gameObject->GetTransform()));
}