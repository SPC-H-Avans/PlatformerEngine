#include <algorithm>
#include "Scene.hpp"
#include "Exceptions/NotImplementedException.hpp"
#include "Exceptions/GameObjectAlreadyInSceneException.hpp"
#include "Exceptions/CameraNotInSceneException.hpp"

void spic::Scene::RenderScene() {
    //Loop through all game objects in scene, call the render component and render it
    throw NotImplementedException();
}

void spic::Scene::AddObject(const std::shared_ptr<GameObject>& gameObject) {
    if (GetObjectByName(gameObject->GetName()) != nullptr)
    {
        throw GameObjectAlreadyInSceneException(gameObject->GetName());
    }
    _contents.push_back(gameObject);
}

void spic::Scene::ImportLevel(const std::string& path, const std::string& fileName, const std::string& levelName) {
    //Import level and set it to a local variable in this scene object..
    throw NotImplementedException();
}

void spic::Scene::RemoveObject(const std::string& name) {
    auto itr = std::remove_if(_contents.begin(),_contents.end(), [&name](const std::shared_ptr<GameObject>& obj){return obj->GetName() == name;});

    _contents.erase(itr,_contents.end());
}

std::shared_ptr<spic::GameObject> spic::Scene::GetObjectByName(const std::string& name) {
    auto foundItemIterator = find_if(_contents.begin(), _contents.end(), [&name](const std::shared_ptr<GameObject>& obj) {return obj->GetName() == name;});

    if (foundItemIterator != _contents.end())
    {
        return foundItemIterator.operator*();
    }
    return nullptr;
}

void spic::Scene::AddCamera(const std::shared_ptr<Camera> &camera) {
    if(GetCameraByName(camera->GetName()) != nullptr){
        throw GameObjectAlreadyInSceneException(camera->GetName());
    }
    AddObject(camera->Parent());
    AddCamera(camera);

    if(_activeCamera == nullptr){
        _activeCamera = camera;
    }
}

std::shared_ptr<spic::Camera> spic::Scene::GetCameraByName(const std::string& name) {
    auto foundItemIterator = find_if(_cameras.begin(), _cameras.end(), [&name](const std::shared_ptr<Camera>& obj) {return obj->GetName() == name;});

    if (foundItemIterator != _cameras.end()) {
        return foundItemIterator.operator*();
    }

    return nullptr;
}

void spic::Scene::DeleteCameraByName(const std::string &name) {
    auto itr = std::remove_if(_cameras.begin(),_cameras.end(), [&name](const std::shared_ptr<Camera>& obj){return obj->GetName() == name;});

    _cameras.erase(itr,_cameras.end());
    RemoveObject(name);
}

void spic::Scene::SetActiveCameraByName(const std::string &name) {
    auto foundCamera = GetCameraByName(name);
    if(foundCamera == nullptr){
        throw CameraNotInSceneException(name);
    }
    _activeCamera = foundCamera;
}
