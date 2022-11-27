#include <gtest/gtest.h>
#include "Builder/GameObjectBuilder.hpp"
#include "BehaviourScript.hpp"
#include "RigidBody.hpp"
#include "BoxCollider.hpp"
#include "Physics/PhysicsSystem.hpp"
#include "Physics/MarioRigidBody.hpp"
#include "Behaviour/CollisionBehaviour.hpp"

class PhysicsTests : public ::testing::Test {
protected:
    void SetUp() override {

        GameObject mario = GameObject("Mario"); //Dynamic rigidbody
        GameObject block = GameObject("Block");

        //Set X,Y pos of objects
        mario.SetTransform(Transform {Point {0, 3}, 0, 0});
        block.SetTransform(Transform {Point {0, 0}, 0, 0});

        //Set Rigidbody on both objects;
        MarioRigidBody marioBody;
        marioBody.BodyType(spic::BodyType::dynamicBody);
        mario.AddComponent<RigidBody>(std::make_shared<MarioRigidBody>(marioBody));

        RigidBody blockBody;
        blockBody.BodyType(spic::BodyType::staticBody);
        block.AddComponent<RigidBody>(std::make_shared<RigidBody>(blockBody));


        mario.AddComponent<BehaviourScript>(std::make_shared<platformer_engine::CollisionBehaviour>());
        block.AddComponent<BehaviourScript>(std::make_shared<BehaviourScript>());

        _mario = GameObject::Find("Mario");
        _block = GameObject::Find("Block");

        //Set Colliders on objects
        SetBoxColliders();
    }

    void TearDown() override {
        GameObject::Destroy(_mario);
        GameObject::Destroy(_block);
    }

    std::shared_ptr<GameObject> _mario;
    std::shared_ptr<GameObject> _block;
    PhysicsSystem physics = PhysicsSystem();

    void SetBoxColliders();
};

/**
 * @brief Tests if a Mario Phyics GameObject doesn't fall through a static object with collision;
 */
TEST_F(PhysicsTests, MarioDoesntFallThroughBlock) {

    // 1. Declare start x and y location of the Mario GameObject
    auto marioStartX = 0.0;
    auto marioStartY = -10.0;

    // 2. Set the location so that the block and mario overlap
    _mario->SetTransform(Transform {Point {marioStartX, marioStartY}, 0, 0});
    _block->SetTransform(Transform {Point {0, 0}, 0, 0});
    physics.Update();

    auto marioNextX = _mario->GetTransform().position.x;
    auto marioNextY = _mario->GetTransform().position.y;

    // 3. Assert that the Mario object's location has not been updated
    ASSERT_TRUE(marioNextX == marioStartX && marioNextY == marioStartY)
        << "The Mario Physics character fell through a block, the y velocity should have been 0, but was " +
        std::to_string(marioNextY);
}

/**
 * @brief Tests if a Mario Phyics GameObject falls when there is no Collision at the bottom, but stops falling when
 * it has reached the ground;
 */
TEST_F(PhysicsTests, MarioFallsUntilBlock) {

    // 1. Declare start x and y location of the Mario GameObject
    auto marioStartX = 0.0;
    auto marioStartY = 0.0;

    // 2. Set the location so that the block and mario don't overlap
    _mario->SetTransform(Transform {Point {marioStartX, marioStartY}, 0, 0});
    _block->SetTransform(Transform {Point {0, 101}, 0, 0});
    physics.Update();

    auto marioNextY = _mario->GetTransform().position.y;

    // 3. Assert that Mario fell down, so the Y-pos has increased
    ASSERT_TRUE(marioNextY > marioStartY)
        << "Mario Physics didn't update the object to fall down, y-pos stayed the same.";

    // 4. Update the physics 50 times, Mario should only fall until the block and then stop moving
    for(int i = 0; i < 50; i++) {
        physics.Update();
    }

    auto marioFinalY = _mario->GetTransform().position.y;

    // 5. Assert that Mario stopped falling on top of the block
    ASSERT_EQ(marioFinalY, 91) << "Mario Physics object should stop falling when it collides on the bottom";

}


void PhysicsTests::SetBoxColliders() {
    BoxCollider collider;
    collider.Width(10);
    collider.Height(10);
    _mario->AddComponent<BoxCollider>(std::make_shared<BoxCollider>(collider));
    collider.Width(10);
    collider.Height(10);
    _block->AddComponent<BoxCollider>(std::make_shared<BoxCollider>(collider));
}