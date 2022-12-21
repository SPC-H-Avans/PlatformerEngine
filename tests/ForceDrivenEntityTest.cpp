#include <gtest/gtest.h>
#include "Behaviour/CollisionBehaviour.hpp"
#include "Physics/MoveSystem.hpp"
#include "Engine/Engine.hpp"
#include "Builder/SceneBuilder.hpp"
#include "Director/GameObjectFactory.hpp"
#include "Physics/ForceDrivenEntity.hpp"
#include "EntityState/EntityPursuitState.hpp"
#include "EntityState/EntityWanderState.hpp"
#include <random>


class ForceDrivenEntityTest : public ::testing::Test {
protected:
    void SetUp() override {
        platformer_engine::Engine &engine = platformer_engine::Engine::GetInstance();
        engine.Init(1000, 1000, "Mario Game", spic::Color::Cyan(), false);
        platformer_engine::SceneBuilder builder = platformer_engine::SceneBuilder("level1");
        engine.AddScene(builder.GetScene());
        engine.QueueActiveScene("level1");
    }

    void TearDown() override {
        platformer_engine::Engine &engine = platformer_engine::Engine::GetInstance();
        engine.Quit();
    }

    auto CreateFDE(const Point position) -> GameObject&;
};

/**
 * @brief Create a standard ForceDrivenEntity on position {10,-10} with size 15 and collisionBehaviour
 * @return A reference to the FDE GameObject
 */
auto ForceDrivenEntityTest::CreateFDE(const Point position) -> GameObject& {
    const int size = 15;
    const std::vector<std::shared_ptr<BehaviourScript>> behaviourScripts {
    };
    std::vector<platformer_engine::AnimatedSprite> animations;


    Transform transform {position, 0, 1};
    return GameObjectFactory::CreateEnemy(transform, size, size, animations, behaviourScripts);
}

/**
 * @brief Use the GameObjectDirector to create a ForceDrivenEntity, test if it starts moving in the wander state
 */
TEST_F(ForceDrivenEntityTest, WanderStateMovesEntity) {

    platformer_engine::Engine &engine = platformer_engine::Engine::GetInstance();
    Scene &scene = engine.GetActiveScene();

    auto gameObject = CreateFDE({10, 10});

    MoveSystem moveSystem;
    moveSystem.Update(1.0);
    moveSystem.Update(1.0);
    moveSystem.Update(1.0);

    auto gob = GameObject::Find(gameObject.GetName());

    ASSERT_TRUE(gob->GetTransform().position.y > 10)
        << "Y-position of the GameObject was expected to be lower than -10, but was " + std::to_string(gob->GetTransform().position.y);
    ASSERT_TRUE(gob->GetTransform().position.x != 10)
        << "X-position of the GameObject was expected to be different than 10, but was " + std::to_string(gob->GetTransform().position.y)
        + ", this means the wander state did not update the x-position after 3 movesystem calls.";

}

/**
 * @brief Test that the ForceDrivenEntity Component doesn't crash the game when it's GameObject has been removed
 */
TEST_F(ForceDrivenEntityTest, NullGameObjectDoesntCrash) {

    auto gameObject = CreateFDE({10,10});
    auto gob = GameObject::Find(gameObject.GetName());

    auto fde = gob->GetComponent<platformer_engine::ForceDrivenEntity>();
    auto emptyGameObject = std::make_shared<GameObject>();
    fde->SetGameObject(emptyGameObject);
    emptyGameObject.reset();

    MoveSystem moveSystem;
    EXPECT_NO_THROW(moveSystem.Update(1.0));
}

/**
 * @brief Test the Pursuit state with a forceDrivenEntity and a player. Assert that the entity is moving towards the
 * player by calling the MoveSystem 50 times and comparing the distance between the entity and the player.
 */
TEST_F(ForceDrivenEntityTest, TestPursuitState) {

    // 1. Define constant variables
    const int playerX = 10;
    const int playerY = 10;
    const int fdeX = 100;
    const int fdeY = 100;
    const int followRange = 10;

    // 2. Create a forceDrivenEntity, a player and define the moveSystem
    auto gameObject = CreateFDE({fdeX, fdeY});
    auto animations = std::vector<platformer_engine::AnimatedSprite>();
    auto behaviour = std::vector<std::shared_ptr<BehaviourScript>>();
    auto player = GameObjectFactory::CreatePlayer(0, Transform{{playerX,playerY}, 1, 1}, 0, 0,
           animations, behaviour);
    auto moveSystem = MoveSystem(0);

    auto playerShared = GameObject::Find(player.GetName());
    auto forceDrivenEntity = GameObject::Find(gameObject.GetName());

    // 3. Set the gravityScale for the player and FDE to 0 so gravity is not a factor
    auto playerRigidBody = std::dynamic_pointer_cast<RigidBody>(playerShared->GetComponent<RigidBody>());
    auto fdeRigidBody = std::dynamic_pointer_cast<RigidBody>(forceDrivenEntity->GetComponent<RigidBody>());
    playerRigidBody->SetGravityScale(0);
    fdeRigidBody->SetGravityScale(0);

    auto fdeComponent = std::dynamic_pointer_cast<platformer_engine::ForceDrivenEntity>(forceDrivenEntity->GetComponent<platformer_engine::ForceDrivenEntity>());

    // 4. Assert that all values were set correctly
    ASSERT_TRUE(fdeComponent != nullptr) << "ForceDrivenEntity Component was a null pointer";

    fdeComponent->SetFollowing(playerShared, followRange);
    ASSERT_EQ(fdeComponent->GetFollowing().lock(), playerShared)
        << "fdeComponent.GetFollowing() did not return the correct GameObject";
    ASSERT_EQ(fdeComponent->GetFollowRange(), followRange)
        << "fdeComponent.GetFollowRange() did not return the correct range";

    fdeComponent->FollowOn();
    ASSERT_EQ(typeid(fdeComponent->GetCurrentState()), typeid(EntityPursuitState))
        << "The ForceDrivenEntity did not go to EntityPursuitState";

    // 5. Test that the ForceDrivenEntity is moving towards the player 50 times
    for(int i = 0; i < 50; i++) {
        auto playerTransform = playerShared->GetTransform();
        auto oldFDETransform = forceDrivenEntity->GetTransform().position;
        moveSystem.Update(1);
        auto newFDETransform = forceDrivenEntity->GetTransform().position;
        ASSERT_TRUE(playerTransform.position.Distance(oldFDETransform) > playerTransform.position.Distance(newFDETransform))
            << "The ForceDrivenEntity did not move closer to the player";
    }
}

/**
 * @brief Test that the ForceDrivenEntity state can be switched between pursuit and wander
 */
TEST_F(ForceDrivenEntityTest, TestStateSwitch) {
    auto fdeObject = CreateFDE({0, 0});
    auto forceDrivenEntity = GameObject::Find(fdeObject.GetName());

    auto fdeComponent = std::dynamic_pointer_cast<platformer_engine::ForceDrivenEntity>(forceDrivenEntity->GetComponent<platformer_engine::ForceDrivenEntity>());
    ASSERT_TRUE(fdeComponent != nullptr) << "ForceDrivenEntity Component was a null pointer";

    ASSERT_EQ(typeid(fdeComponent->GetCurrentState()), typeid(EntityWanderState))
        << "The Default state of the ForceDrivenEntity was not a wander state";

    fdeComponent->FollowOn();
    ASSERT_EQ(typeid(fdeComponent->GetCurrentState()), typeid(EntityPursuitState))
        << "The FollowOn function didn't switch the state to EntityPursuitState";

    fdeComponent->WanderOn();
    ASSERT_EQ(typeid(fdeComponent->GetCurrentState()), typeid(EntityWanderState))
        << "The WanderOn function didn't switch the state to EntityWanderState";

}