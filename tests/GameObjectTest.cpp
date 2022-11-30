#include <gtest/gtest.h>
#include "GameObject.hpp"

class GameObjectTest : public ::testing::Test {

};

TEST_F(GameObjectTest, CanCreateGameObjectWithName) {
    auto gameObject = spic::GameObject("Test");
    ASSERT_EQ(gameObject.GetName(), "Test");
}

TEST_F(GameObjectTest, CanFindGameObjectByName) {
    spic::GameObject("Test"); // NOLINT(bugprone-unused-raii)
    auto gameObject = spic::GameObject::Find("Test");
    auto gameObject2 = spic::GameObject::Find("Test2");
    ASSERT_TRUE(gameObject != nullptr);
    ASSERT_TRUE(gameObject2 == nullptr);
}

TEST_F(GameObjectTest, CanFindGameObjectByTag) {
    spic::GameObject("Test", "Tag"); // NOLINT(bugprone-unused-raii)
    auto gameObject = spic::GameObject::FindWithTag("Tag");
    auto gameObject2 = spic::GameObject::FindWithTag("Tag2");
    ASSERT_TRUE(gameObject != nullptr);
    ASSERT_TRUE(gameObject2 == nullptr);
}

TEST_F(GameObjectTest, CanFindGameObjectByType) {
    spic::GameObject("Test"); // NOLINT(bugprone-unused-raii)
    auto gameObject = spic::GameObject::FindObjectOfType<spic::GameObject>();
    ASSERT_TRUE(gameObject != nullptr);
}

TEST_F(GameObjectTest, CanDestroyGameObject) {
    spic::GameObject("Test"); // NOLINT(bugprone-unused-raii)
    auto gameObject = spic::GameObject::Find("Test");
    ASSERT_TRUE(gameObject != nullptr);
    spic::GameObject::Destroy(gameObject);
    gameObject = spic::GameObject::Find("Test");
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
    auto gameObject = spic::GameObject("Test");
    gameObject.Active(false);
    ASSERT_FALSE(gameObject.Active());
    gameObject.Active(true);
    ASSERT_TRUE(gameObject.Active());
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
}