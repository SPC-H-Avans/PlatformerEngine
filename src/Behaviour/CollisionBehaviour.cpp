#include "Behaviour/CollisionBehaviour.hpp"
#include "GameObject.hpp"
#include "RigidBody.hpp"
#include "BoxCollider.hpp"
#include "Engine/Engine.hpp"

namespace platformer_engine {

    void CollisionBehaviour::OnStart() {
    }

    void CollisionBehaviour::OnUpdate(double speedMultiplier) {
    }

    void CollisionBehaviour::OnTriggerEnter2D(Collision collision) {
        if(collision.GetSelfCollider()->GetColliderType() != ColliderType::Body) return;
        _activeCollisions.push_back(collision);
        UpdateMoveRestriction(collision, false);
        Unstuck(collision);
    }

    void CollisionBehaviour::OnTriggerExit2D(Collision collision) {
        if(collision.GetSelfCollider()->GetColliderType() != ColliderType::Body) return;
        // Remove the collision from _activeCollisions
        for (auto &col: _activeCollisions) {
            const int currentId = col.GetId();
            if (currentId == collision.GetId()) {
                auto newEnd = std::remove_if(_activeCollisions.begin(), _activeCollisions.end(),
                                             [currentId](const Collision &col) { return col.GetId() == currentId; });
                _activeCollisions.erase(newEnd, _activeCollisions.end());
            }
        }
        UpdateMoveRestriction(collision, true);
    }

    void CollisionBehaviour::OnTriggerStay2D(Collision collision) {
    }

    void CollisionBehaviour::UpdateMoveRestriction(Collision &col, bool allow) {
        if (!col.GetOtherCollider()->GetObstructsMovement()) return;
        auto point = col.Contact();
        auto gameObjWeak = GetGameObject();
        const std::shared_ptr<spic::GameObject> gameObj{gameObjWeak.lock()};
        if (gameObj) {
            auto body = std::static_pointer_cast<RigidBody>(gameObj->GetComponent<RigidBody>());
            if (body != nullptr) {
                if (allow) {
                    body->AllowMoveTo(point);
                } else {
                    body->DenyMoveTo(point);
                }
            }
        } else { // gameObjWeak is already deleted
            gameObjWeak.reset();
        }
    }

    void CollisionBehaviour::Unstuck(Collision &collision) {
        std::shared_ptr<GameObject> currentGameObject{GetGameObject().lock()};
        auto &engine = platformer_engine::Engine::GetInstance();
        const auto localClientId = engine.GetLocalClientId();
        if (currentGameObject &&
            currentGameObject->GetOwnerId() == localClientId) {
            auto currentTransform = currentGameObject->GetTransform();
            auto oldTransform = currentTransform;

            auto currentCollider = std::dynamic_pointer_cast<BoxCollider>(collision.GetSelfCollider());

            auto collidingGameObject = collision.GetOtherCollider()->GetGameObject().lock();
            if(collidingGameObject) {
                auto collidingTransform = collidingGameObject->GetTransform();
                auto collidingCollider = std::dynamic_pointer_cast<BoxCollider>(collision.GetOtherCollider());

                if (collision.Contact() == CollisionPoint::Top) {
                    currentTransform.position.y = collidingTransform.position.y + collidingCollider->Height();
                } else if (collision.Contact() == CollisionPoint::Bottom) {
                    currentTransform.position.y = collidingTransform.position.y - currentCollider->Height();
                } else if (collision.Contact() == CollisionPoint::Left) {
                    currentTransform.position.x = collidingTransform.position.x + collidingCollider->Width();
                } else if (collision.Contact() == CollisionPoint::Right) {
                    currentTransform.position.x = collidingTransform.position.x - currentCollider->Width();
                }

                currentGameObject->SetTransform(currentTransform);
                if(!currentTransform.position.Equals(oldTransform.position)) {
                    try {
                        switch (engine.GetNetworkingStatus()) {
                            case platformer_engine::MultiplayerClient:
                                engine.GetClientNetworkManager().UpdateNetworkedGameObjectTransform(currentTransform,
                                                                                                    currentGameObject->GetName());
                                break;
                            case platformer_engine::MultiplayerServer:
                                engine.GetServerNetworkManager().UpdateNetworkedGameObjectTransform(currentTransform,
                                                                                                    currentGameObject->GetName());
                                break;
                            case platformer_engine::Singleplayer:
                                break;
                        }
                    } catch (std::exception &e) {
                        //Just ignore the exception, we will try resending the transform later
                    }
                }

            } else {
                collidingGameObject.reset();
            }
        } else {
            currentGameObject.reset();
        }
    }
}  // namespace platformer_engine
BOOST_CLASS_EXPORT(platformer_engine::CollisionBehaviour);