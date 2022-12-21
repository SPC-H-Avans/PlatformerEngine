#include <gtest/gtest.h>
#include "GameObject.hpp"
#include "Physics/ForceDrivenEntity.hpp"
#include "Component.hpp"

class GameObjectTest : public ::testing::Test {

};

TEST_F(GameObjectTest, CanCreateGameObjectWithName) {
    auto gameObject = spic::GameObject("CanCreateGameObjectWithNameTestObject");
    ASSERT_EQ(gameObject.GetName(), "CanCreateGameObjectWithNameTestObject");
    spic::GameObject::Destroy(spic::GameObject::Find(gameObject.GetName()));
}

TEST_F(GameObjectTest, CanCreateGameObjectWithDuplicateName) {
    auto gameObject = spic::GameObject("CanCreateGameObjectWithDuplicateName");
    auto gameObject2 = spic::GameObject("CanCreateGameObjectWithDuplicateName");
    ASSERT_EQ(gameObject.GetName(), "CanCreateGameObjectWithDuplicateName");
    ASSERT_EQ(gameObject2.GetName(), "CanCreateGameObjectWithDuplicateName- Copy");
    spic::GameObject::Destroy(spic::GameObject::Find(gameObject.GetName()));
    spic::GameObject::Destroy(spic::GameObject::Find(gameObject2.GetName()));
}

TEST_F(GameObjectTest, CanFindGameObjectByName) {
    spic::GameObject("Test_GameObjectTest"); // NOLINT(bugprone-unused-raii)
    auto gameObject = spic::GameObject::Find("Test_GameObjectTest");
    auto gameObject2 = spic::GameObject::Find("Test2_GameObjectTest");
    ASSERT_TRUE(gameObject != nullptr);
    ASSERT_TRUE(gameObject2 == nullptr);
    spic::GameObject::Destroy(gameObject);
}

TEST_F(GameObjectTest, CanFindGameObjectByTag) {
    spic::GameObject("Test", "Tag"); // NOLINT(bugprone-unused-raii)
    auto gameObject = spic::GameObject::FindWithTag("Tag");
    ASSERT_EQ(gameObject->GetTag(), "Tag");
    auto gameObject2 = spic::GameObject::FindWithTag("Tag2");
    ASSERT_TRUE(gameObject != nullptr);
    ASSERT_TRUE(gameObject2 == nullptr);
    spic::GameObject::Destroy(gameObject);
}

TEST_F(GameObjectTest, CanFindGameObjectsByTag) {
    auto gameObject = spic::GameObject("Test", "Tag"); // NOLINT(bugprone-unused-raii)
    auto gameObject2 = spic::GameObject("Test2", "Tag"); // NOLINT(bugprone-unused-raii)
    auto gameObjectsWithTag = spic::GameObject::FindGameObjectsWithTag("Tag");

    auto foundGameObject1 = false;
    auto foundGameObject2 = false;
    for(const auto& obj : gameObjectsWithTag) {
        if(obj->GetName() == gameObject.GetName()) foundGameObject1 = true;
        if(obj->GetName() == gameObject2.GetName()) foundGameObject2 = true;
    }

    ASSERT_TRUE(foundGameObject1);
    ASSERT_TRUE(foundGameObject2);

    spic::GameObject::Destroy(spic::GameObject::Find(gameObject.GetName()));
    spic::GameObject::Destroy(spic::GameObject::Find(gameObject2.GetName()));
}

TEST_F(GameObjectTest, CanFindGameObjectByType) {
    spic::GameObject("Test"); // NOLINT(bugprone-unused-raii)
    auto gameObject = spic::GameObject::FindObjectOfType<spic::GameObject>();
    ASSERT_TRUE(gameObject != nullptr);
    spic::GameObject::Destroy(gameObject);
}

TEST_F(GameObjectTest, CanDestroyGameObject) {
    spic::GameObject("GameObjectTest_CanDestroyGameObject"); // NOLINT(bugprone-unused-raii)
    auto gameObject = spic::GameObject::Find("GameObjectTest_CanDestroyGameObject");
    ASSERT_TRUE(gameObject != nullptr);
    spic::GameObject::Destroy(gameObject);
    gameObject = spic::GameObject::Find("GameObjectTest_CanDestroyGameObject");
    ASSERT_TRUE(gameObject == nullptr);
}

//TEST_F(GameObjectTest, HasParent) {
//    auto gameObject = spic::GameObject("Parent");
//    auto gameObjectChild = std::make_shared<spic::GameObject>("Child");
//
//    gameObject.AddChild(gameObjectChild);
//
//    ASSERT_EQ(gameObject.Children().size(), 1);
//    ASSERT_EQ(gameObjectChild->Parent()->GetName(), "Parent");
//}

TEST_F(GameObjectTest, CanChangeIsActive) {
    auto gameObject = spic::GameObject("GameObjectTest_CanChangeIsActive");
    gameObject.Active(false);
    ASSERT_FALSE(gameObject.Active());
    gameObject.Active(true);
    ASSERT_TRUE(gameObject.Active());
    spic::GameObject::Destroy(spic::GameObject::Find(gameObject.GetName()));
}

TEST_F(GameObjectTest, CanChangeTransform) {
    auto gameObject = spic::GameObject("Test");
    auto transform = spic::Transform();
    auto point = spic::Point();
    transform.scale = 1.2; // NOLINT(cppcoreguidelines-avoid-magic-numbers)
    point.x = 2;
    point.y = -2;
    transform.position = point;
    transform.rotation = 10.2; // NOLINT(cppcoreguidelines-avoid-magic-numbers)
    gameObject.SetTransform(transform);

    ASSERT_EQ(gameObject.GetTransform().rotation, 10.2);
    ASSERT_EQ(gameObject.GetTransform().position.y, -2);
    ASSERT_EQ(gameObject.GetTransform().position.x, 2);
    ASSERT_EQ(gameObject.GetTransform().scale, 1.2);
    spic::GameObject::Destroy(spic::GameObject::Find(gameObject.GetName()));
}

TEST_F(GameObjectTest, CanUpdateGameObjects) {
    auto gameObject = spic::GameObject("CanCompareGameObjects"); // NOLINT(bugprone-unused-raii)
    auto gameObject2 = spic::GameObject("CanCompareGameObjects2"); // NOLINT(bugprone-unused-raii)

    auto newTransform = spic::Transform{{10,5}, 12, 3};
    gameObject.SetTransform(newTransform);
    gameObject2 = gameObject;

    ASSERT_EQ(gameObject.GetName(), gameObject2.GetName());
    ASSERT_TRUE(gameObject2.GetTransform().position.Equals(newTransform.position));

    spic::GameObject::Destroy(spic::GameObject::Find(gameObject.GetName()));
    spic::GameObject::Destroy(spic::GameObject::Find("CanCompareGameObjects2"));
}

TEST_F(GameObjectTest, CanCompareGameObjects) {
    auto gameObject = spic::GameObject("CanCompareGameObjects"); // NOLINT(bugprone-unused-raii)
    auto gameObject2 = spic::GameObject("CanCompareGameObjects2"); // NOLINT(bugprone-unused-raii)
    auto gameObject3 = gameObject;

    ASSERT_TRUE(gameObject != gameObject2);
    ASSERT_TRUE(gameObject == gameObject3);

    spic::GameObject::Destroy(spic::GameObject::Find(gameObject.GetName()));
    spic::GameObject::Destroy(spic::GameObject::Find(gameObject2.GetName()));
}