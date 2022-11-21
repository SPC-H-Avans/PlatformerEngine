#include <gtest/gtest.h>
#include "Builder/SceneBuilder.hpp"
#include "Builder/GameObjectBuilder.hpp"
#include "Exceptions/GameObjectAlreadyInSceneException.hpp"

/**
 * @brief SceneBuilder Tests
 */
class SceneBuilderTest : public ::testing::Test {

};

/**
 * @brief Check if the SceneBuilder can build a scene
 */
TEST_F(SceneBuilderTest, IsSceneCreated) {
    platformer_engine::SceneBuilder sceneBuilder;
    auto scene = sceneBuilder.GetScene();
    ASSERT_TRUE(scene != nullptr);
}

/**
 * @brief Check if a Game Object can be added to a scene
 */
TEST_F(SceneBuilderTest, ShouldAddGameObject) {
    auto gameObject = GameObjectBuilder("Test").GetGameObject();
    auto scene = platformer_engine::SceneBuilder().AddGameObject(gameObject).GetScene();

    ASSERT_TRUE(scene != nullptr);
    ASSERT_TRUE(scene->GetObjectByName(gameObject->GetName()) != nullptr);
}

/**
 * @brief Check if adding the same Game Object twice is restricted
 */
TEST_F(SceneBuilderTest, CannotAddSameObjectTwice) {
    auto sceneBuilder = platformer_engine::SceneBuilder();
    auto gameObject = GameObjectBuilder("Test").GetGameObject();
    sceneBuilder.AddGameObject(gameObject);

    ASSERT_THROW(sceneBuilder.AddGameObject(gameObject), GameObjectAlreadyInSceneException);
}

/**
 * @brief Check if multiple Game Objects can be added to the scnee with one call
 */
TEST_F(SceneBuilderTest, ShouldAddMultipleObjectsAtOnce) {
    auto sceneBuilder = platformer_engine::SceneBuilder();
    auto gameObject = GameObjectBuilder("Test").GetGameObject();
    auto gameObject2 = GameObjectBuilder("Test2").GetGameObject();
    auto gameObject3 = GameObjectBuilder("Test3").GetGameObject();

    auto gameObjects = std::vector<std::shared_ptr<GameObject>>();
    gameObjects.push_back(gameObject);
    gameObjects.push_back(gameObject2);
    gameObjects.push_back(gameObject3);

    sceneBuilder.AddGameObjects(gameObjects);
    auto scene = sceneBuilder.GetScene();

    ASSERT_TRUE(scene != nullptr);
    ASSERT_TRUE(scene->GetObjectByName(gameObject->GetName()) != nullptr);
    ASSERT_TRUE(scene->GetObjectByName(gameObject2->GetName()) != nullptr);
    ASSERT_TRUE(scene->GetObjectByName(gameObject3->GetName()) != nullptr);
}

/**
 * @brief Test for the Scene Builder, to check if a camera can be added
 */
TEST_F(SceneBuilderTest, ShouldAddCamera) {
    auto camera = std::make_shared<Camera>("Camera 1", "Camera", Color::Transparent(), 1, 1);
    auto camera2 = std::make_shared<Camera>("Camera 2", "Camera", Color::Transparent(), 1, 1);
    auto scene = platformer_engine::SceneBuilder().AddCamera(camera).GetScene();
    scene->AddCamera(camera2);
    scene->SetActiveCameraByName("Camera 1");

    ASSERT_TRUE(scene != nullptr);
    ASSERT_TRUE(scene->GetActiveCamera() != nullptr);
    ASSERT_TRUE(scene->GetActiveCamera()->GetName() == "Camera 1");

    scene->SetActiveCameraByName("Camera 2");
    ASSERT_TRUE(scene->GetActiveCamera()->GetName() == "Camera 2");
}