#include <gtest/gtest.h>
#include "GameObject.hpp"
#include "Physics/PhysicsSystem.hpp"
#include "Physics/MarioRigidBody.hpp"

TEST(PhysicsTest, DoesMarioMove) {
    auto go1 = spic::GameObject("Mario_DoesMarioMove");
    go1.SetTransform(Transform {Point {3, 3}, 0, 0});


    MarioRigidBody body;
    body.BodyType(spic::BodyType::dynamicBody);
    go1.AddComponent<MarioRigidBody>(std::make_shared<MarioRigidBody>(body));

    auto physics = PhysicsSystem();
    physics.MoveObjects();
}