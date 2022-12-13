#include <stdexcept>

#include "Director/GameObjectDirector.hpp"
#include "Engine/Engine.hpp"
#include "Physics/PlayerRigidBody.hpp"
#include "BehaviourScript.hpp"
#include "Text.hpp"
#include "Button.hpp"

auto GameObjectDirector::CreateTile(const spic::Sprite &sprite, // TODO: switch sprite and transform for consistency
                                    Transform transform, int colliderWidth, int colliderHeight) -> GameObject & {
    auto &scene = platformer_engine::Engine::GetInstance().GetActiveScene();
    auto builder =
            GameObjectBuilder("tile" + std::to_string(scene.GetObjectCount()))
                    .AddSprite(sprite);
    auto obj = builder.GetGameObject();
    obj->SetTransform(transform);

    // collider
    auto collider = BoxCollider();
    collider.Width(colliderWidth);
    collider.Height(colliderHeight);
    obj->AddComponent<BoxCollider>(std::make_shared<BoxCollider>(collider));

    scene.AddObject(obj);
    return *obj;
}

auto GameObjectDirector::CreateBackgroundObject(const spic::Sprite &sprite,
                                                Transform transform) -> GameObject & {
    auto &scene = platformer_engine::Engine::GetInstance().GetActiveScene();
    auto builder =
            GameObjectBuilder("tile" + std::to_string(scene.GetObjectCount()))
                    .AddSprite(sprite);
    auto obj = builder.GetGameObject();
    obj->SetTransform(transform);
    scene.AddObject(obj);
    return *obj;
}

auto GameObjectDirector::CreatePlayer(int playerId, Transform transform, int colliderWidth, int colliderHeight,
                                      std::vector<platformer_engine::AnimatedSprite> &animations,
                                      const std::vector<std::shared_ptr<BehaviourScript>> &behaviourScripts) -> GameObject & {
    auto &scene = platformer_engine::Engine::GetInstance().GetActiveScene();

    auto builder = GameObjectBuilder(std::string(NET_PLAYER_PREFIX) + std::to_string(playerId))
            // animations
            .AddAnimator(animations).SetOwnerId(playerId);
    auto obj = builder.GetGameObject();

    // transform
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

    // scripts
    for (const auto &script: behaviourScripts) {
        obj->AddComponent<BehaviourScript>(script);
    }

    scene.AddObject(obj);
    return *obj;
}

auto GameObjectDirector::CreateText(Transform transform, const std::string objectId, const std::string &text,
                                    const std::string &fontPath, int textWidth, int textHeight,
                                    int fontSize, Color textColor) -> Text & {
    auto &scene = platformer_engine::Engine::GetInstance().GetActiveScene();
    auto textObject = Text(objectId, textWidth, textHeight, text, fontPath, fontSize, textColor);

    textObject.SetTransform(transform);
    auto textPtr = std::make_shared<Text>(textObject);

    scene.AddUIObject(textPtr);
    return *textPtr;
}

auto GameObjectDirector::CreateButton(Transform transform, const std::string objectId, const spic::Sprite &sprite,
                                      const std::string &imgPath, int buttonWidth, int buttonHeight,
                                      std::function<void()> onClick) -> Button & {
    auto &scene = platformer_engine::Engine::GetInstance().GetActiveScene();
    auto buttonObject = Button(objectId, sprite, imgPath, buttonWidth, buttonHeight);

    buttonObject.SetTransform(transform);
    buttonObject.OnClick(onClick);
    auto buttonPtr = std::make_shared<Button>(buttonObject);
    scene.AddUIObject(buttonPtr);
    return *buttonPtr;
}
