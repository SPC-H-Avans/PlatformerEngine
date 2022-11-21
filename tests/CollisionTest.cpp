#include <gtest/gtest.h>
#include "Builder/GameObjectBuilder.hpp"
#include "BehaviourScript.hpp"
#include "RigidBody.hpp"
#include "BoxCollider.hpp"
#include "Physics/PhysicsSystem.hpp"
#include "Resources/TestCollisionBehaviour.hpp"

class CollisionTests : public ::testing::Test {
protected:
    void SetUp() override {

        GameObject g1 = GameObject("dynamic1"); //Dynamic rigidbody
        GameObject g2 = GameObject("static1");

        //Set X,Y pos of objects
        g1.SetTransform(Transform {Point {3, 3}, 0, 0});
        g2.SetTransform(Transform {Point {0, 0}, 0, 0});

        //Set Rigidbody on both objects;
        RigidBody body;
        body.BodyType(spic::BodyType::dynamicBody);
        g1.AddComponent<RigidBody>(std::make_shared<RigidBody>(body));
        body.BodyType(spic::BodyType::staticBody);
        g2.AddComponent<RigidBody>(std::make_shared<RigidBody>(body));

        g1.AddComponent<BehaviourScript>(std::make_shared<TestCollisionBehaviour>());
        g2.AddComponent<BehaviourScript>(std::make_shared<TestCollisionBehaviour>());


        go1 = GameObject::Find("dynamic1");
        go2 = GameObject::Find("static1");
    }

    void TearDown() override {
        GameObject::Destroy(go1);
        GameObject::Destroy(go2);
    }

    std::shared_ptr<GameObject> go1;
    std::shared_ptr<GameObject> go2;
    PhysicsSystem physics = PhysicsSystem();
    void SetBoxColliders();
};

/**
 * @brief Tests if there are no collision detections when nothing is colliding;
 */
TEST_F(CollisionTests, IsNoCollisionDetected) {

    // 1. Transform both objects to make sure they're not colliding
    go1->SetTransform(Transform {Point {0, 20}, 0, 0});
    go2->SetTransform(Transform {Point {0, 0}, 0, 0});
    SetBoxColliders();

    // 2. Run PhysicsEngine for collisions
    physics.Update();

    auto go1Script = std::static_pointer_cast<TestCollisionBehaviour>(go1->GetComponent<BehaviourScript>());
    auto go2Script = std::static_pointer_cast<TestCollisionBehaviour>(go2->GetComponent<BehaviourScript>());

    // 3. Assert that both Behaviour scripts have no collision triggers
    ASSERT_EQ(go1Script->GetTriggerCount(), 0)
        << "The GameObject 1 had more than 0 triggers, a collision was falsely detected";
    ASSERT_EQ(go2Script->GetTriggerCount(), 0)
        << "The GameObject 2 had more than 0 triggers, a collision was falsely detected";
}

/**
 * @brief Tests if collisions between two objects are correctly detected and the behaviour script is called with the
 * right CollisionPoint on Enter, Stay and Exit;
 */
TEST_F(CollisionTests, IsCollisionBetweenTwoObjectsDetected) {

    // 1. Transform both objects to make sure they're colliding
    go1->SetTransform(Transform {Point {0, 10}, 0, 0});
    go2->SetTransform(Transform {Point {0, 0}, 0, 0});
    SetBoxColliders();

    // 2. Run PhysicsEngine for collisions
    physics.Update();

    auto go1Script = std::static_pointer_cast<TestCollisionBehaviour>(go1->GetComponent<BehaviourScript>());
    auto go2Script = std::static_pointer_cast<TestCollisionBehaviour>(go2->GetComponent<BehaviourScript>());

    // 3. Assert that both Behaviour scripts have one collision trigger
    ASSERT_EQ(go1Script->GetTriggerCount(), 1)
                                << "The GameObject 1 had " +
                                std::to_string(go1Script->GetTriggerCount()) +
                                " triggers, expected 1";
    ASSERT_EQ(go2Script->GetTriggerCount(), 1)
                                << "The GameObject 2 had " +
                                   std::to_string(go1Script->GetTriggerCount()) +
                                   " triggers, expected 1";

    // 4. Assert that the collision points are correct
    auto cp1 = go1Script->GetCollisionPointCountFor(Trigger::Enter, CollisionPoint::Top);
    auto cp2 = go2Script->GetCollisionPointCountFor(Trigger::Enter, CollisionPoint::Bottom);
    ASSERT_EQ(cp1, 1);
    ASSERT_EQ(cp2, 1);

    // 5. Run the physics system again without changing any values
    physics.Update();

    // 6. Assert that the 'Stay' Trigger has been triggered
    auto stayTrigger1 = go1Script->GetCollisionPointCountFor(Trigger::Stay, CollisionPoint::Top);
    auto stayTrigger2 = go2Script->GetCollisionPointCountFor(Trigger::Stay, CollisionPoint::Bottom);
    ASSERT_EQ(stayTrigger1, 1);
    ASSERT_EQ(stayTrigger2, 1);


    // 7. Update GameObject 1's location so they don't overlap anymore
    go1->SetTransform(Transform {Point {0, 20}, 0, 0});

    // 8. Run PhysicsEngine for collisions
    physics.Update();

    // 9. Assert that the Collision left has been triggered
    auto exitTrigger1 = go1Script->GetCollisionPointCountFor(Trigger::Exit, CollisionPoint::Uncertain);
    auto exitTrigger2 = go2Script->GetCollisionPointCountFor(Trigger::Exit, CollisionPoint::Uncertain);
    ASSERT_TRUE(exitTrigger1);
    ASSERT_TRUE(exitTrigger2);

}

/**
 * @brief Tests collisions for all directions (up, down, left and right) and asserts that the right CollisionPoint is
 * passed to the Behaviour Script;
 */
TEST_F(CollisionTests, AreCollisionPointsCorrect) {

    // 1. Transform both objects to collide on top and bottom
    go1->SetTransform(Transform {Point {0, 10}, 0, 0}); // below, so collision on top
    go2->SetTransform(Transform {Point {0, 0}, 0, 0}); // above, so collision on bottom
    SetBoxColliders();

    // 2. Run PhysicsEngine for collisions
    physics.Update();

    auto go1Script = std::static_pointer_cast<TestCollisionBehaviour>(go1->GetComponent<BehaviourScript>());
    auto go2Script = std::static_pointer_cast<TestCollisionBehaviour>(go2->GetComponent<BehaviourScript>());

    auto go1Collision = go1Script->GetCollisionPointCountFor(Trigger::Enter, CollisionPoint::Top);
    auto go2Collision = go2Script->GetCollisionPointCountFor(Trigger::Enter, CollisionPoint::Bottom);

    // 3. Assert that go1 has a collision on top and go2 on bottom
    ASSERT_EQ(go1Collision, 1)
        << "GameObject 1 gave the wrong CollisionPoint, expected Top";
    ASSERT_EQ(go2Collision, 1)
        << "GameObject 2 gave the wrong CollisionPoint, expected Bottom";

    // 4. Update the go1 location so it collides on the right of go2
    go1->SetTransform(Transform {Point {10, 1}, 0, 0}); // right, so collision left
    //SetBoxColliders(); // Set box colliders again, so they can collide again
    // Use a new phyics system so collisions are reset.
    physics = PhysicsSystem();
    physics.Update();

    // 5. Assert that go1 has a collision on the left and go2 on the right
    go1Collision = go1Script->GetCollisionPointCountFor(Trigger::Enter, CollisionPoint::Left);
    go2Collision = go2Script->GetCollisionPointCountFor(Trigger::Enter, CollisionPoint::Right);
    ASSERT_EQ(go1Collision, 1)
        << "GameObject 1 gave the wrong CollisionPoint, expected Left";
    ASSERT_EQ(go2Collision, 1)
        << "GameObject 2 gave the wrong CollisionPoint, expected Right";


}

TEST_F(CollisionTests, IsCollisionBetweenThreeObjectsDetected) {

    // 1. Create a third Collision object to be able to collide with the first two
    GameObject g3 = GameObject("static2");
    RigidBody body;
    body.BodyType(spic::BodyType::staticBody);
    g3.AddComponent<RigidBody>(std::make_shared<RigidBody>(body));
    g3.AddComponent<BehaviourScript>(std::make_shared<TestCollisionBehaviour>());
    BoxCollider collider;
    collider.Width(10);
    collider.Height(10);
    g3.AddComponent<BoxCollider>(std::make_shared<BoxCollider>(collider));

    auto go3 = GameObject::Find("static2");

    // 2. Transform all objects to make sure they're colliding
    go1->SetTransform(Transform {Point {105, 110}, 0, 0}); // below so 2 collisions on top
    go2->SetTransform(Transform {Point {110, 100}, 0, 0}); // right, so collision left and below
    go3->SetTransform(Transform {Point {100, 100}, 0, 0}); // left, so collision right and below
    SetBoxColliders();

    //3. Run the physics engine
    physics.Update();

    //4. Assert that all collisions are correctly detected
    auto go1Script = std::static_pointer_cast<TestCollisionBehaviour>(go1->GetComponent<BehaviourScript>());
    auto go2Script = std::static_pointer_cast<TestCollisionBehaviour>(go2->GetComponent<BehaviourScript>());
    auto go3Script = std::static_pointer_cast<TestCollisionBehaviour>(go3->GetComponent<BehaviourScript>());

    int go1TopCnt = go1Script->GetCollisionPointCountFor(Trigger::Enter, CollisionPoint::Top);
    ASSERT_EQ(go1TopCnt, 2);

    int go2BottomCnt = go2Script->GetCollisionPointCountFor(Trigger::Enter, CollisionPoint::Bottom);
    ASSERT_EQ(go2BottomCnt, 1);

    int go3BottomCnt = go3Script->GetCollisionPointCountFor(Trigger::Enter, CollisionPoint::Bottom);
    ASSERT_EQ(go3BottomCnt, 1);

    // 5. Remove one


}

void CollisionTests::SetBoxColliders() {
    BoxCollider collider;
    collider.Width(10);
    collider.Height(10);
    go1->AddComponent<BoxCollider>(std::make_shared<BoxCollider>(collider));
    collider.Width(10);
    collider.Height(10);
    go2->AddComponent<BoxCollider>(std::make_shared<BoxCollider>(collider));
}

