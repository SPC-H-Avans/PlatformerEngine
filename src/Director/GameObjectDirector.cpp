#include <stdexcept>

#include "Director/GameObjectDirector.hpp"

auto GameObjectDirector::CreateTile() -> std::shared_ptr<GameObject> {
    std::cout << 123 << "\n";
    auto builder =
            GameObjectBuilder("tile")
            // TODO
            ;
    return builder.GetGameObject();
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
