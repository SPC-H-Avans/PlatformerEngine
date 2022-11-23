#include <stdexcept>

#include "Director/GameObjectDirector.hpp"

auto GameObjectDirector::CreateTile(
        const std::shared_ptr<Sprite>& sprite,
        Transform transform
        ) -> std::shared_ptr<GameObject> {
    std::cout << 123 << "\n";
    auto builder =
            GameObjectBuilder("tile")
                    .AddSprite(sprite)
            // TODO
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
