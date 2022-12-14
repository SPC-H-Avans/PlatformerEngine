#include <algorithm>
#include "Scene.hpp"
#include "LevelParser/LevelParser.hpp"
#include "Debug.hpp"
#include "Exceptions/NotImplementedException.hpp"
#include "Exceptions/GameObjectAlreadyInSceneException.hpp"
#include "Exceptions/CameraNotInSceneException.hpp"
#include "Animator.hpp"

spic::Scene::Scene(const std::string &sceneName) : _sceneName(sceneName) {}

void spic::Scene::SetNextScene(const std::string sceneName) {_nextScene = sceneName;};

auto spic::Scene::GetNextScene() const -> std::optional<std::string> { return _nextScene;};

void spic::Scene::RenderScene() {

    RenderGameObjects();
    RenderUIObjects();
}

void spic::Scene::RenderGameObjects() {
    for (const auto &item: _contents) {
        auto animatorComponent = item->GetComponent<spic::Animator>();
        if (animatorComponent != nullptr) {
            auto animator = std::static_pointer_cast<spic::Animator>(animatorComponent);
            if (animator->Active()) {
                animator->Render(item->GetTransform());
                continue;
            }
        }
        auto spriteComponent = item->GetComponent<spic::Sprite>();
        if (spriteComponent != nullptr) {
            auto sprite = std::static_pointer_cast<spic::Sprite>(spriteComponent);
            if (sprite->Active()) {
                sprite->Render(item->GetTransform());
                continue;
            }
        }
    }
}

void spic::Scene::RenderUIObjects() {
    for (const auto &item: _uiObjects) {
        item->Render();
    }
}

void spic::Scene::AddObject(const std::shared_ptr<spic::GameObject> &gameObject) {
    if (GetObjectByName(gameObject->GetName()) != nullptr) {
        throw GameObjectAlreadyInSceneException(gameObject->GetName());
    }
    
    auto gameObjectPtr = GameObject::Find(gameObject.GetName(), true);
    _contents.push_back(gameObjectPtr);
    _origins.push_back(*gameObjectPtr);
}

void spic::Scene::AddUIObject(const std::shared_ptr<spic::UIObject> &uiObject) {
    if (GetObjectByName(uiObject->GetName()) != nullptr) {
        throw spic::GameObjectAlreadyInSceneException(uiObject->GetName());
    }
//    auto obj = std::make_shared<UIObject>(uiObject);
    _uiObjects.push_back(uiObject);
//    _origins.push_back(*uiObject);
}

void spic::Scene::ImportLevel(const std::string &id, const std::string &filePath, const std::string &fileName,
                              const std::map<int, std::function<spic::GameObject(Transform)>> &config) {
    platformer_engine::LevelParser::ParseLevel(*this, id, filePath, fileName, config);
}

void spic::Scene::RemoveObject(const std::string &name) {
    auto itr = std::remove_if(_contents.begin(), _contents.end(),
                              [&name](const std::shared_ptr<GameObject> &obj) { return obj->GetName() == name; });

    _contents.erase(itr, _contents.end());

    auto itrOrigins = std::remove_if(_origins.begin(), _origins.end(),
                                     [&name](const GameObject &obj) { return obj.GetName() == name; });

    _origins.erase(itrOrigins, _origins.end());

}

auto spic::Scene::GetObjectByName(const std::string &name) -> std::shared_ptr<spic::GameObject> {
    auto foundItemIterator = find_if(_contents.begin(), _contents.end(),
                                     [&name](const std::shared_ptr<GameObject> &obj) {
                                         return obj->GetName() == name;
                                     });

    if (foundItemIterator != _contents.end()) {
        return foundItemIterator.operator*();
    }
    return nullptr;
}

auto spic::Scene::GetObjectCount() -> int {
    return _contents.size();
}

void spic::Scene::AddCamera(Camera &camera) {
    if (GetCameraByName(camera.GetName()) != nullptr) {
        throw GameObjectAlreadyInSceneException(camera.GetName());
    }

    auto sharedCamera = std::make_shared<Camera>(camera);
    _cameras.push_back(sharedCamera);

    if (_activeCamera == nullptr) {
        _activeCamera = sharedCamera;
    }
}

auto spic::Scene::GetCameraByName(const std::string &name) -> std::shared_ptr<spic::Camera> {
    auto foundItemIterator = find_if(_cameras.begin(), _cameras.end(),
                                     [&name](const std::shared_ptr<Camera> &obj) { return obj->GetName() == name; });

    if (foundItemIterator != _cameras.end()) {
        return foundItemIterator.operator*();
    }

    return nullptr;
}

void spic::Scene::DeleteCameraByName(const std::string &name) {
    auto itr = std::remove_if(_cameras.begin(), _cameras.end(),
                              [&name](const std::shared_ptr<Camera> &obj) { return obj->GetName() == name; });

    _cameras.erase(itr, _cameras.end());
    RemoveObject(name);
}

void spic::Scene::SetActiveCameraByName(const std::string &name) {
    auto foundCamera = GetCameraByName(name);
    if (foundCamera == nullptr) {
        throw CameraNotInSceneException(name);
    }
    _activeCamera = foundCamera;
}

auto spic::Scene::GetActiveCamera() -> std::shared_ptr<spic::Camera> {
    return _activeCamera;
}

void spic::Scene::ResetScene() {
    _contents.clear();

    for (auto &origin: _origins) {
        auto instance = GameObject::Find(origin.GetName(), true);

        if (instance == nullptr) {
            GameObject g(origin.GetName());
            instance = GameObject::Find(origin.GetName(), true);
        }

        _contents.push_back(instance);
        *instance = origin;
    }
}

//spic::Scene::~Scene() { // TODO: destructor
//    platformer_engine::LevelParser::LevelParser::GetInstance().Clean();
//
//    //TODO destroy all in scene
//}

