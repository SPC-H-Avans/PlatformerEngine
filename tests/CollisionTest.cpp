#include <gtest/gtest.h>
#include "Builder/GameObjectBuilder.hpp"
#include "BehaviourScript.hpp"
#include "RigidBody.hpp"
#include "BoxCollider.hpp"
#include <queue>
#include "Physics/PhysicsSystem.hpp"

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


        g1.AddComponent<BehaviourScript>(std::make_shared<BehaviourScript>());
        g2.AddComponent<BehaviourScript>(std::make_shared<BehaviourScript>());


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
