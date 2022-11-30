#include <stdexcept>

#include "Director/GameObjectDirector.hpp"
#include "Engine/Engine.hpp"
#include "Physics/PlayerRigidBody.hpp"
#include "BehaviourScript.hpp"
#include "Behaviour/PlayerInputBehaviour.hpp"
#include "Behaviour/CollisionBehaviour.hpp"
#include "Behaviour/DynamicAnimationBehaviour.hpp"

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

auto GameObjectDirector::CreatePlayer(const std::shared_ptr<platformer_engine::AnimatedSprite>& idleSprite,
                                      const std::shared_ptr<platformer_engine::AnimatedSprite>& walkSprite,
                                      const std::shared_ptr<platformer_engine::AnimatedSprite>& jumpSprite,
                                      Transform transform, int colliderWidth, int colliderHeight) -> std::shared_ptr<GameObject> { // probably add width and height parameters and more to use in GameObjectBuilder functions
    auto& scene = platformer_engine::Engine::GetInstance().GetActiveScene();

    // set up animations
    auto animations = std::vector<std::shared_ptr<platformer_engine::AnimatedSprite>>();
    animations.push_back(idleSprite);
    animations.push_back(walkSprite);
    animations.push_back(jumpSprite);

    auto builder =
            GameObjectBuilder("player" + std::to_string(scene.GetObjectCount()))
                    .AddAnimator(animations)
                    .AddBehaviourScript(std::make_shared<platformer_engine::PlayerInputBehaviour>())
                    .AddBehaviourScript(std::make_shared<platformer_engine::CollisionBehaviour>())
                    .AddBehaviourScript(std::make_shared<platformer_engine::DynamicAnimationBehaviour>(idleSprite, walkSprite, jumpSprite));
    ;
    auto obj = builder.GetGameObject();
    obj->SetTransform(transform);

    // rigidbody
    auto playerBody = PlayerRigidBody();
    playerBody.BodyType(spic::BodyType::dynamicBody);
    obj->AddComponent<RigidBody>(std::make_shared<PlayerRigidBody>(playerBody));

    // collider
    auto collider = BoxCollider();
    collider.Width(colliderWidth);
    collider.Height(colliderHeight);
    obj->AddComponent<BoxCollider>(std::make_shared<BoxCollider>(collider));

    scene.AddObject(obj);
    return obj;
}
