#include <gtest/gtest.h>
#include "Builder/GameObjectBuilder.hpp"
#include "BehaviourScript.hpp"
#include "RigidBody.hpp"
#include "BoxCollider.hpp"
#include "Physics/PhysicsSystem.hpp"

class CollisionTests : public ::testing::Test {
protected:
    void SetUp() override {

        GameObject g1 = GameObject("dynamic1"); //Dynamic rigidbody
        GameObject g2 = GameObject("static1");

        go1 = GameObject::Find("dynamic1");
        go2 = GameObject::Find("static1");

        //Set X,Y pos of objects
        go1->SetTransform(Transform {Point {3, 3}, 0, 0});
        go2->SetTransform(Transform {Point {0, 0}, 0, 0});

        //Set Rigidbody on both objects;
        RigidBody body;
        body.BodyType(spic::BodyType::dynamicBody);
        go1->AddComponent<RigidBody>(std::make_shared<RigidBody>(body));
        body.BodyType(spic::BodyType::staticBody);
        go2->AddComponent<RigidBody>(std::make_shared<RigidBody>(body));


        go1->AddComponent<BehaviourScript>(std::make_shared<BehaviourScript>());
        go2->AddComponent<BehaviourScript>(std::make_shared<BehaviourScript>());
    }

    // void TearDown() override {}
    std::shared_ptr<GameObject> go1;
    std::shared_ptr<GameObject> go2;
    PhysicsSystem physics = PhysicsSystem();
     //Static rigidbody
};

/**
 * @brief Tests if there are no collision detections when nothing is colliding;
 */
TEST_F(CollisionTests, IsNoCollisionDetected) {

    //Set Colliders on objects
    BoxCollider collider;
    collider.Width(10);
    collider.Height(10);
    go1->AddComponent<BoxCollider>(std::make_shared<BoxCollider>(collider));
    collider.Width(10);
    collider.Height(10);
    go2->AddComponent<BoxCollider>(std::make_shared<BoxCollider>(collider));

    physics.Update();
}
