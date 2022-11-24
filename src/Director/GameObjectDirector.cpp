#include <stdexcept>

#include "Director/GameObjectDirector.hpp"
#include "Engine/Engine.hpp"

auto GameObjectDirector::CreateTile(const std::shared_ptr<Sprite>& sprite,
                                    Transform transform) -> std::shared_ptr<GameObject> {
    auto& scene = platformer_engine::Engine::GetInstance().GetActiveScene();
    auto builder =
            GameObjectBuilder("tile" + std::to_string(scene->GetObjectCount()))
                    .AddSprite(sprite)
            // TODO add rigidbody, etc
            ;
    auto obj = builder.GetGameObject();
    obj->SetTransform(transform);
    return obj;
}

auto GameObjectDirector::CreateBackgroundObject(const std::shared_ptr<Sprite> &sprite,
                                                Transform transform) -> std::shared_ptr<GameObject> {
    auto& scene = platformer_engine::Engine::GetInstance().GetActiveScene();
    auto builder =
            GameObjectBuilder("tile" + std::to_string(scene->GetObjectCount()))
                    .AddSprite(sprite)
    ;
    auto obj = builder.GetGameObject();
    obj->SetTransform(transform);
    return obj;
}

//auto GameObjectDirector::CreatePlayer() -> std::shared_ptr<GameObject> { // probably add width and height parameters and more to use in GameObjectBuilder functions
//    auto builder =
//            GameObjectBuilder("player")
////            .AddAnimator()
//            .AddAudioSource()
//            .AddBehaviourScript()
//            .AddCollider()
//            .AddRigidBody()
////            .AddSprite();
//            ;
//    return builder.GetGameObject();
//}
