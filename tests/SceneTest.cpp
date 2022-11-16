#include <gtest/gtest.h>
#include "Builder/SceneBuilder.hpp"
#include "Builder/GameObjectBuilder.hpp"
#include <list>

/**
 * @brief Tests if the SceneBuilder.GetScene returns a scene and not a null pointer;
 */
TEST(SceneTest, IsSceneCreated) {
    // 1. Create an empty scene using the SceneBuilder
    auto scene = SceneBuilder().GetScene();

    // 2. Assert that the GetScene pointer didn't return a null pointer
    ASSERT_TRUE(scene != nullptr) << "The empty SceneBuilder's GetScene function didn't return a scene pointer.";
}

/**
 * @brief Tests if the SceneBuilder adds a GameObject correctly;
 */
TEST(SceneTest, IsGameObjectAddedToScene) {
    // 1. Create a GameObject and add it to a new Scene using the SceneBuilder
    auto gO1 = GameObjectBuilder("gameObject1").GetGameObject();
    auto scene = SceneBuilder()
            .AddGameObject(gO1)
            .GetScene();

    // 2. Assert that the scene is not null
    ASSERT_TRUE(scene != nullptr) << "The empty SceneBuilder's GetScene function didn't return a scene pointer.";

    // 3. Compare the added GameObject to the GameObject that was supposed to be added and assert that they are equal
    auto addedGO = scene->GetObjectByName("gameObject1");
    ASSERT_TRUE(addedGO != nullptr) << "The added gameObject was not found by it's name.";
    ASSERT_TRUE(addedGO == gO1) << "The returned pointer was not equal to the added gameobject's pointer";
}

/**
 * @brief Tests if the SceneBuilder adds a list of GameObjects correctly;
 */
TEST(SceneTest, AreGameObjectsAddedToScene) {
    int const amount_of_objects_to_add = 10;
    auto builder = SceneBuilder();
    std::vector<std::shared_ptr<GameObject>> gos;

    // 1. Add a number of GameObjects to a vector (gos)
    for(int i = 0; i < amount_of_objects_to_add; i++) {
        gos.push_back(GameObjectBuilder("gameObject" + std::to_string(i)).GetGameObject());
    }

    // 2. Add all GameObjects from the vector to the SceneBuilder
    builder.AddGameObjects(gos);
    auto scene = builder.GetScene();

    // 3. Assert that the scene pointer is not a nullpointer
    ASSERT_TRUE(scene != nullptr) << "The empty SceneBuilder's GetScene function didn't return a scene pointer.";

    // 4. Loop through all GameObjects in the vector and check if they are indeed present in the scene
    for(int i = 0; i < amount_of_objects_to_add; i++) {
        auto currentGO = gos.at(i);
        auto name = currentGO->GetName();
        auto addedGO = scene->GetObjectByName(name);

        ASSERT_TRUE(addedGO != nullptr) << "The added gameObject {" + name + "} was not found by it's name.";
        ASSERT_TRUE(addedGO == currentGO) << "The returned pointer for {" + name + "} was not equal to the added gameobject's pointer.";
    }
}

/**
 * @brief Tests if GameObjects can be removed by name using the Scene->RemoveObject function;
 */
TEST(SceneTest, IsGameObjectRemoved) {
    std::string name = "gameObject";

    // 1. Create a scene with a gameObject
    auto gO1 = GameObjectBuilder(name).GetGameObject();
    auto scene = SceneBuilder()
            .AddGameObject(gO1)
            .GetScene();

    // 2. Remove that gameObject from the scene
    scene->RemoveObject(name);

    // 3. Assert that the gameObject cannot be found by name
    auto addedGO = scene->GetObjectByName(name);
    ASSERT_TRUE(addedGO == nullptr) << "The GameObject was not removed from the scene.";

}

// 8. Create a camera, add it to the scene and get it by name
TEST(SceneTest, IsCameraAddedToScene) {

}

// 11. Create a camera, get it by name and set it as the active camera


