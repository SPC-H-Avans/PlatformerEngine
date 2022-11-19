#include <gtest/gtest.h>
#include "Builder/GameObjectBuilder.hpp"
#include "BehaviourScript.hpp"
#include "RigidBody.hpp"
#include "BoxCollider.hpp"
#include <queue>
#include "Physics/PhysicsSystem.hpp"
#include "Resources/TestCollisionBehavior.hpp"

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


        g1.AddComponent<BehaviourScript>(std::make_shared<TestCollisionBehavior>());
        g2.AddComponent<BehaviourScript>(std::make_shared<TestCollisionBehavior>());


        go1 = GameObject::Find("dynamic1");
        go2 = GameObject::Find("static1");
    }

    std::shared_ptr<GameObject> go1;
    std::shared_ptr<GameObject> go2;
    PhysicsSystem physics = PhysicsSystem();
     //Static rigidbody
};

/**
 * @brief Tests if there are no collision detections when nothing is colliding;
 */
TEST_F(CollisionTests, IsNoCollisionDetected) {

    // 1. Transform both objects to make sure they're not colliding
    go1->SetTransform(Transform {Point {0, 20}, 0, 0});
    go2->SetTransform(Transform {Point {0, 0}, 0, 0});

    // 2. Set Colliders on objects (with sizes that don't collide)
    BoxCollider collider;
    collider.Width(10);
    collider.Height(10);
    go1->AddComponent<BoxCollider>(std::make_shared<BoxCollider>(collider));
    collider.Width(10);
    collider.Height(10);
    go2->AddComponent<BoxCollider>(std::make_shared<BoxCollider>(collider));

    // 3. Run PhysicsEngine for collisions
    physics.Update();

    auto go1Script = std::static_pointer_cast<TestCollisionBehavior>(go1->GetComponent<BehaviourScript>());
    auto go2Script = std::static_pointer_cast<TestCollisionBehavior>(go2->GetComponent<BehaviourScript>());

    // 4. Assert that both Behaviour scripts have no collision triggers
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

    // 2. Set Colliders on objects (with sizes that do collide)
    BoxCollider bc1;
    bc1.Width(10);
    bc1.Height(10);
    go1->AddComponent<BoxCollider>(std::make_shared<BoxCollider>(bc1));

    BoxCollider bc2;
    bc2.Width(10);
    bc2.Height(10);
    go2->AddComponent<BoxCollider>(std::make_shared<BoxCollider>(bc2));

    // 3. Run PhysicsEngine for collisions
    physics.Update();

    auto go1Script = std::static_pointer_cast<TestCollisionBehavior>(go1->GetComponent<BehaviourScript>());
    auto go2Script = std::static_pointer_cast<TestCollisionBehavior>(go2->GetComponent<BehaviourScript>());

    // 4. Assert that both Behaviour scripts have one collision trigger
    ASSERT_EQ(go1Script->GetTriggerCount(), 1)
                                << "The GameObject 1 had " +
                                std::to_string(go1Script->GetTriggerCount()) +
                                " triggers, expected 1";
    ASSERT_EQ(go2Script->GetTriggerCount(), 1)
                                << "The GameObject 2 had " +
                                   std::to_string(go1Script->GetTriggerCount()) +
                                   " triggers, expected 1";

    // 5. Assert that the collision points are correct
    auto cp1 = go1Script->GetTriggerFor(Trigger::Enter).second;
    auto cp2 = go2Script->GetTriggerFor(Trigger::Enter).second;
    ASSERT_EQ(cp1, CollisionPoint::Top);
    ASSERT_EQ(cp2, CollisionPoint::Bottom);

    // 6. Run the physics system again without changing any values
    physics.Update();

    // 7. Assert that the 'Stay' Trigger has been triggered
    auto stayTrigger1 = go1Script->HasTriggered(Trigger::Stay);
    auto stayTrigger2 = go2Script->HasTriggered(Trigger::Stay);
    ASSERT_TRUE(stayTrigger1);
    ASSERT_TRUE(stayTrigger2);


    // 8. Update GameObject 1's location so they don't overlap anymore
    go1->SetTransform(Transform {Point {0, 20}, 0, 0});

    // 9. Run PhysicsEngine for collisions
    physics.Update();

    // 10. Assert that the Collision left has been triggered
    auto exitTrigger1 = go1Script->HasTriggered(Trigger::Exit);
    auto exitTrigger2 = go2Script->HasTriggered(Trigger::Exit);
    ASSERT_TRUE(exitTrigger1);
    ASSERT_TRUE(exitTrigger2);

}

// todo: Test collision system for left, right, up, down collision locations