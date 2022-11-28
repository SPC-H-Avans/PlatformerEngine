#include <stdexcept>

#include "Director/GameObjectDirector.hpp"
#include "Engine/Engine.hpp"
#include "Physics/MarioRigidBody.hpp"
#include "BehaviourScript.hpp"
#include "Behaviour/MarioInputBehaviour.hpp"
#include "Behaviour/CollisionBehaviour.hpp"

auto GameObjectDirector::CreateTile(const std::shared_ptr<Sprite>& sprite,
                                    Transform transform, int colliderWidth, int colliderHeight) -> std::shared_ptr<GameObject> {
    auto& scene = platformer_engine::Engine::GetInstance().GetActiveScene();
    auto builder =
            GameObjectBuilder("tile" + std::to_string(scene.GetObjectCount()))
                    .AddSprite(sprite)
    ;
    auto obj = builder.GetGameObject();
    obj->SetTransform(transform);

    // collider
    auto collider = BoxCollider();
    collider.Width(colliderWidth);
    collider.Height(colliderHeight);
    obj->AddComponent<BoxCollider>(std::make_shared<BoxCollider>(collider));

    scene.AddObject(obj);
    return obj;
}

auto GameObjectDirector::CreateBackgroundObject(const std::shared_ptr<Sprite> &sprite,
                                                Transform transform) -> std::shared_ptr<GameObject> {
    auto& scene = platformer_engine::Engine::GetInstance().GetActiveScene();
    auto builder =
            GameObjectBuilder("tile" + std::to_string(scene.GetObjectCount()))
                    .AddSprite(sprite)
    ;
    auto obj = builder.GetGameObject();
    obj->SetTransform(transform);
    scene.AddObject(obj);
    return obj;
}

auto GameObjectDirector::CreatePlayer(const std::shared_ptr<platformer_engine::AnimatedSprite>& sprite,
                                      Transform transform, int colliderWidth, int colliderHeight) -> std::shared_ptr<GameObject> { // probably add width and height parameters and more to use in GameObjectBuilder functions
    auto& scene = platformer_engine::Engine::GetInstance().GetActiveScene();
    auto builder =
            GameObjectBuilder("player" + std::to_string(scene.GetObjectCount()))
                    .AddAnimator(sprite)
                    .AddBehaviourScript(std::make_shared<platformer_engine::MarioInputBehaviour>());
    ;
    auto obj = builder.GetGameObject();
    obj->SetTransform(transform);

    // rigidbody
    auto marioBody = MarioRigidBody();
    marioBody.BodyType(spic::BodyType::dynamicBody);
    obj->AddComponent<RigidBody>(std::make_shared<MarioRigidBody>(marioBody));

    // collider
    auto collider = BoxCollider();
    collider.Width(colliderWidth);
    collider.Height(colliderHeight);
    obj->AddComponent<BoxCollider>(std::make_shared<BoxCollider>(collider));

    // Add collision behaviourscript
    obj->AddComponent<BehaviourScript>(std::make_shared<platformer_engine::CollisionBehaviour>());

    scene.AddObject(obj);
    return obj;
}
