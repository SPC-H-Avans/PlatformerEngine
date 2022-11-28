#include <stdexcept>

#include "Director/GameObjectDirector.hpp"
#include "Engine/Engine.hpp"
#include "Physics/MarioRigidBody.hpp"
#include "BehaviourScript.hpp"
#include "Behaviour/CollisionBehaviour.hpp"

auto GameObjectDirector::CreateTile(const std::shared_ptr<Sprite>& sprite,
                                    Transform transform) -> std::shared_ptr<GameObject> {
    auto& scene = platformer_engine::Engine::GetInstance().GetActiveScene();
    auto builder =
            GameObjectBuilder("tile" + std::to_string(scene.GetObjectCount()))
                    .AddSprite(sprite)
    // TODO add rigidbody, etc
    ;
    auto obj = builder.GetGameObject();
    obj->SetTransform(transform);


    // Add a BoxCollider
    auto collider = BoxCollider();
    collider.Width(14);
    collider.Height(16);
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
                                      Transform transform) -> std::shared_ptr<GameObject> { // probably add width and height parameters and more to use in GameObjectBuilder functions
    auto& scene = platformer_engine::Engine::GetInstance().GetActiveScene();
    auto builder =
            GameObjectBuilder("player" + std::to_string(scene.GetObjectCount()))
                    .AddAnimator(sprite)
//            .AddAudioSource()
//            .AddBehaviourScript()
//            .AddCollider()
//            .AddRigidBody()
    ;
    auto obj = builder.GetGameObject();
    obj->SetTransform(transform);

    // rigidbody
    auto marioBody = MarioRigidBody();
    marioBody.BodyType(spic::BodyType::dynamicBody);
    obj->AddComponent<RigidBody>(std::make_shared<MarioRigidBody>(marioBody));

    // collider
    auto collider = BoxCollider();
    collider.Width(24); // TODO: magic num
    collider.Height(24);
    obj->AddComponent<BoxCollider>(std::make_shared<BoxCollider>(collider));

    // Add collision behaviourscript
    obj->AddComponent<BehaviourScript>(std::make_shared<platformer_engine::CollisionBehaviour>());

    scene.AddObject(obj);
    return obj;
}
