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
