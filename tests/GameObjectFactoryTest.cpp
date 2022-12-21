#include <gtest/gtest.h>
#include "Director/GameObjectFactory.hpp"
#include "Resources/TestCollisionBehaviour.hpp"
#include "Behaviour/BehaviourSystem.hpp"

/**
 * @brief GameObjectFactoryTest Tests
 */
class GameObjectFactoryTest : public ::testing::Test {

};

/**
 * @brief Creates a tile using the GameObjectFactory
 */
TEST_F(GameObjectFactoryTest, CanCreateTile) {

    auto tile = GameObjectFactory::CreateTile("tile", Sprite(),Transform{{0,0},0,0}, 10, 10);
    auto tileGameObject = GameObject::Find(tile.GetName());

    ASSERT_TRUE(tileGameObject != nullptr);
    GameObject::Destroy(tileGameObject);
}

/**
 * @brief Creates a background object using the GameObjectFactory
 */
TEST_F(GameObjectFactoryTest, CanCreateBackgroundObject) {

    auto background = GameObjectFactory::CreateBackgroundObject("background", Sprite(),Transform{{0,0},0,0});
    auto backgroundGameObject = GameObject::Find(background.GetName());

    ASSERT_TRUE(backgroundGameObject != nullptr);
    GameObject::Destroy(backgroundGameObject);
}

/**
 * @brief Creates a scripted tile using the GameObjectFactory and test that the behaviourscript update is called
 */
TEST_F(GameObjectFactoryTest, CanCreateScriptedTile) {

    bool obstructsMovement = true;
    auto collisionBehaviour = std::make_shared<TestCollisionBehaviour>(TestCollisionBehaviour());
    std::vector<std::shared_ptr<BehaviourScript>> behaviourScripts {
        collisionBehaviour
    };
    auto tile = GameObjectFactory::CreateScriptedTile("scriptedTile", Sprite(),Transform{{0,0},0,0}, 10, 10, obstructsMovement, behaviourScripts);
    auto tileGameObject = GameObject::Find(tile.GetName());

    ASSERT_TRUE(tileGameObject != nullptr);

    auto behaviourSystem = BehaviourSystem();
    behaviourSystem.Update(1.0);
    auto testCollisionBehaviour = std::dynamic_pointer_cast<TestCollisionBehaviour>(collisionBehaviour);
    ASSERT_EQ(testCollisionBehaviour->GetUpdateTriggers(), 1);

    GameObject::Destroy(tileGameObject);
}

/**
 * @brief Creates a Text object using the GameObjectFactory
 */
TEST_F(GameObjectFactoryTest, CanCreateText) {

    auto text = GameObjectFactory::CreateText({{0,0},0,0}, "text0", "TestText",
    "", 1, 1, 1, Color::Black());
    auto textGameObject = GameObject::Find(text.GetName());

    ASSERT_TRUE(textGameObject != nullptr);
    GameObject::Destroy(textGameObject);
}

/**
 * @brief Creates a Button object using the GameObjectFactory
 */
TEST_F(GameObjectFactoryTest, CanCreateButton) {

    auto button = GameObjectFactory::CreateButton({{0,0},0,0}, "button0", Sprite(),"", 1, 1, {});
    auto buttonGameObject = GameObject::Find(button.GetName());

    ASSERT_TRUE(buttonGameObject != nullptr);
    GameObject::Destroy(buttonGameObject);
}