#include <gtest/gtest.h>
#include "Director/GameObjectDirector.hpp"
#include "Behaviour/CollisionBehaviour.hpp"
#include "Physics/PhysicsSystem.hpp"
#include "Physics/MoveSystem.hpp"
#include "Engine/Engine.hpp"
#include "Builder/SceneBuilder.hpp"

/**
 * @brief Create a standard ForceDrivenEntity on position {10,-10} with size 15 and collisionBehaviour
 * @return A reference to the FDE GameObject
 */
auto CreateFDE() -> GameObject& {
    const Point position (Point{10,10});
    const int size = 15;
    const std::vector<std::shared_ptr<BehaviourScript>> behaviourScripts {
    };
    std::vector<platformer_engine::AnimatedSprite> animations;


    Transform transform {position, 0, 1};
    return GameObjectDirector::CreateEnemy(transform, size, size, animations, behaviourScripts);
}

/**
 * @brief Use the GameObjectDirector to create a ForceDrivenEntity, test if it starts moving in the wander state
 */
TEST(ForceDrivenEntityTest, WanderStateMovesEntity) {

    platformer_engine::Engine &engine = platformer_engine::Engine::GetInstance();
    engine.Init(1000, 1000, "Mario Game", spic::Color::Cyan(), false);
    platformer_engine::SceneBuilder builder = platformer_engine::SceneBuilder("level1");
    engine.AddScene(builder.GetScene());
    engine.QueueActiveScene("level1");
    Scene &scene = engine.GetActiveScene();

    auto gameObject = CreateFDE();

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


// Todo: Make a test for the pursuit state to check if the length between the object and the following object is declining
// Todo: Also move the target around to different locations and check for the same thing