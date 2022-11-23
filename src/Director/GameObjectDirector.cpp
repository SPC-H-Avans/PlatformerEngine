#include <stdexcept>

#include "Director/GameObjectDirector.hpp"

auto GameObjectDirector::CreateTile(
        std::string name, // TODO: instead of parsing name, just use a generic name and concat the number of GameObjects at the end, create a method in Scene to get no. of objects
        const std::shared_ptr<Sprite>& sprite,
        Transform transform
        ) -> std::shared_ptr<GameObject> {
    auto builder =
            GameObjectBuilder(name)
                    .AddSprite(sprite)
            // TODO add rigidbody and such
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
