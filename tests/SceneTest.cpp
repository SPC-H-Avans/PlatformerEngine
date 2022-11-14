#include <gtest/gtest.h>
#include "Builder/SceneBuilder.hpp"
#include "Builder/GameObjectBuilder.hpp"
#include <list>

class SceneTest : public ::testing::Test {
protected:
    void SetUp() override {
//        q1_.Enqueue(1);
//        q2_.Enqueue(2);
//        q2_.Enqueue(3);
    }

    // void TearDown() override {}

//    Queue<int> q0_;
//    Queue<int> q1_;
//    Queue<int> q2_;
};

// Tests to make:
// 1. Create a scene
TEST_F(SceneTest, IsSceneCreated) {
    auto scene = SceneBuilder().GetScene();
    ASSERT_TRUE(scene != nullptr) << "The empty SceneBuilder's GetScene function didn't return a scene pointer.";
}

// 2. Add a GameObject -> Check if it was added
TEST_F(SceneTest, IsGameObjectAddedToScene) {
    auto gO1 = GameObjectBuilder("gameObject1").GetGameObject();
    auto scene = SceneBuilder()
            .AddGameObject(gO1)
            .GetScene();
    ASSERT_TRUE(scene != nullptr) << "The empty SceneBuilder's GetScene function didn't return a scene pointer.";
    auto addedGO = scene->GetObjectByName("gameObject1");
    ASSERT_TRUE(addedGO != nullptr) << "The added gameObject was not found by it's name.";
    ASSERT_TRUE(addedGO == gO1) << "The returned pointer was not equal to the added gameobject's pointer";
}

// 3. Add multiple GameObjects -> Check if they were added and can be found by name
TEST_F(SceneTest, AreGameObjectsAddedToScene) {
    int const amount_of_objects_to_add = 10;

    auto builder = SceneBuilder();
    std::vector<std::shared_ptr<GameObject>> gos;

    for(int i = 0; i < amount_of_objects_to_add; i++) {
        gos.push_back(GameObjectBuilder("gameObject" + std::to_string(i)).GetGameObject());
    }

    builder.AddGameObjects(gos);

    auto scene = builder.GetScene();

    ASSERT_TRUE(scene != nullptr) << "The empty SceneBuilder's GetScene function didn't return a scene pointer.";

    for(int i = 0; i < amount_of_objects_to_add; i++) {
        auto currentGO = gos.at(i);
        auto name = currentGO->GetName();
        auto addedGO = scene->GetObjectByName(name);

        ASSERT_TRUE(addedGO != nullptr) << "The added gameObject {" + name + "} was not found by it's name.";
        ASSERT_TRUE(addedGO == currentGO) << "The returned pointer for {" + name + "} was not equal to the added gameobject's pointer.";
    }
}

// 5. Add a camera -> Check if the camera has been created
// 6. Create a camera
//  -> Aspect width of 0 or lower should throw InvalidSizeException
//  -> Aspect height of 0 or lower should throw InvalidSizeException
// 7. Zoom a camera
//  -> Aspect width of 0 or lower should throw InvalidSizeException
//  -> Aspect height of 0 or lower should throw InvalidSizeException
// 8. Create a camera and add it to the scene
// 9. Remove a gameobject -> Check if it was removed
// 10. Create a camera and get it by name
// 11. Create a camera, get it by name and set it as the active camera


