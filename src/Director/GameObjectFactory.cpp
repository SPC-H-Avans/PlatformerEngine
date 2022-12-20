
#include <stdexcept>

#include "Director/GameObjectFactory.hpp"
#include "Engine/Engine.hpp"
#include "BehaviourScript.hpp"
#include "Physics/Templates/FlyingGumbaTemplate.hpp"
#include "Physics/Templates/MarioPhysicsTemplate.hpp"
#include "Physics/ForceDrivenEntity.hpp"
#include "Text.hpp"
#include "Button.hpp"


static int tileCounter = 1;

auto GameObjectFactory::CreateTile(const std::string& namePrefix, const spic::Sprite& sprite, // TODO: switch sprite and transform for consistency
                                   Transform transform, int colliderWidth, int colliderHeight) -> GameObject& {
    auto builder =
            GameObjectBuilder(namePrefix + std::to_string(tileCounter))
                    .AddSprite(sprite);
    auto obj = builder.GetGameObject();
    obj->SetTransform(transform);

    // collider
    auto collider = BoxCollider();
    collider.Width(colliderWidth);
    collider.Height(colliderHeight);
    obj->AddComponent<BoxCollider>(std::make_shared<BoxCollider>(collider));

    ++tileCounter;
    return *obj;
}

auto GameObjectFactory::CreateBackgroundObject(const std::string& namePrefix, const spic::Sprite &sprite,
                                               Transform transform) -> GameObject & {
    auto builder =
            GameObjectBuilder(namePrefix + std::to_string(tileCounter))
                    .AddSprite(sprite);
    auto obj = builder.GetGameObject();
    obj->SetTransform(transform);

    ++tileCounter;
    return *obj;
}

auto GameObjectFactory::CreateScriptedTile(const std::string& namePrefix, const spic::Sprite& sprite,
                                           Transform transform, int colliderWidth, int colliderHeight, bool obstructsMovement,
                                           const std::vector<std::shared_ptr<BehaviourScript>>& behaviourScripts) -> GameObject & {
    auto builder =
            GameObjectBuilder(namePrefix + std::to_string(tileCounter))
                    .AddSprite(sprite);

    auto obj = builder.GetGameObject();
    obj->SetTransform(transform);

    // collider
    auto collider = BoxCollider();
    collider.Width(colliderWidth);
    collider.Height(colliderHeight);
    collider.SetObstructsMovement(obstructsMovement);
    obj->AddComponent<BoxCollider>(std::make_shared<BoxCollider>(collider));

    // scripts
    for (const auto &script: behaviourScripts) {
        obj->AddComponent<BehaviourScript>(script);
    }

    ++tileCounter;
    return *obj;
}

auto GameObjectFactory::CreatePlayer(int playerId, Transform transform, int colliderWidth, int colliderHeight,
                                     std::vector<platformer_engine::AnimatedSprite> &animations,
                                     const std::vector<std::shared_ptr<BehaviourScript>> &behaviourScripts) -> GameObject & {
    auto builder = GameObjectBuilder(std::string(NET_PLAYER_PREFIX) + std::to_string(playerId), "player")
            // animations
            .AddAnimator(animations).SetOwnerId(playerId);
    auto obj = builder.GetGameObject();

    // transform
    obj->SetTransform(transform);

    // rigidbody
    MarioPhysicsTemplate physicsTemplate;
    auto playerBody = RigidBody(physicsTemplate);
    playerBody.BodyType(spic::BodyType::dynamicBody);
    obj->AddComponent<RigidBody>(std::make_shared<RigidBody>(playerBody));

    // collider
    auto collider = BoxCollider();
    collider.Width(colliderWidth);
    collider.Height(colliderHeight);
    collider.SetPosition(transform.position);
    collider.SetColliderType(ColliderType::Body);
    obj->AddComponent<BoxCollider>(std::make_shared<BoxCollider>(collider));

    // scripts
    for (const auto &script: behaviourScripts) {
        obj->AddComponent<BehaviourScript>(script);
    }

    return *obj;
}

auto GameObjectFactory::CreateEnemy(Transform transform, int colliderWidth, int colliderHeight,
                                    std::vector<platformer_engine::AnimatedSprite> &animations,
                                    const std::vector<std::shared_ptr<BehaviourScript>> &behaviourScripts) -> GameObject & {
    auto& scene = platformer_engine::Engine::GetInstance().GetActiveScene();

    auto builder = GameObjectBuilder("enemy" + std::to_string(scene.GetObjectCount()), "enemy")
            // animations
            .AddAnimator(animations);
    auto obj = builder.GetGameObject();

    // transform
    obj->SetTransform(transform);

    // rigidbody
    FlyingGumbaTemplate physicsTemplate;
    auto enemyBody = std::make_shared<RigidBody>(physicsTemplate);
    enemyBody->BodyType(spic::BodyType::dynamicBody);
    obj->AddComponent<RigidBody>(enemyBody);

    // Force Driven Entity component
    auto sharedFde = std::make_shared<platformer_engine::ForceDrivenEntity>();
    obj->AddComponent<platformer_engine::ForceDrivenEntity>(sharedFde);

    // collider
    auto collider = BoxCollider();
    collider.Width(colliderWidth);
    collider.Height(colliderHeight);
    collider.SetPosition(transform.position);
    collider.SetColliderType(ColliderType::Body);
    obj->AddComponent<BoxCollider>(std::make_shared<BoxCollider>(collider));

    // scripts
    for (const auto &script: behaviourScripts) {
        obj->AddComponent<BehaviourScript>(script);
    }

    return *obj;
}

auto GameObjectFactory::CreateText(const Transform &transform, const std::string &objectId, const std::string &text,
                                   const std::string &fontPath, int textWidth, int textHeight,
                                   int fontSize, const Color &textColor) -> Text {
    auto textObject = Text(objectId, textWidth, textHeight, text, fontPath, fontSize, textColor);

    textObject.SetTransform(transform);

    auto textPtr = std::make_shared<Text>(textObject);
    return *textPtr;
}

auto GameObjectFactory::CreateButton(const Transform &transform, const std::string &objectId, const spic::Sprite &sprite,
                                     const std::string &imgPath, int buttonWidth, int buttonHeight,
                                     const std::function<void()> &onClick) -> Button {
    auto buttonObject = Button(objectId, sprite, imgPath, buttonWidth, buttonHeight);

    buttonObject.SetTransform(transform);
    buttonObject.OnClick(onClick);

    auto buttonPtr = std::make_shared<Button>(buttonObject);
    return *buttonPtr;
}
