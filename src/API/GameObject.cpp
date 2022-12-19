#include <stdexcept>
#include "GameObject.hpp"
#include "Exceptions/GameObjectAlreadyInSceneException.hpp"
#include "ComponentExtension/Scaleable.hpp"
#include "Exceptions/InvalidSizeException.hpp"
#include "ComponentExtension/Rotatable.hpp"

using namespace spic;

//Creates the static instances of GameObjects
std::map<std::string, std::shared_ptr<GameObject>> GameObject::_instances{};

GameObject::GameObject(const std::string &name) {
    std::string objName = name;
    if (_instances.count(name) > 0)
        objName += "- Copy";

    this->_name = objName;
    auto selfptr = std::make_shared<GameObject>(*this);
    _self = selfptr;
    selfptr->_self = selfptr;

    if (name != "Null")
        _instances[objName] = selfptr;
}

void GameObject::ResetSelf() {
    auto selfptr = std::make_shared<GameObject>(*this);
    _self = selfptr;
    selfptr->_self = selfptr;

    if (_name != "Null")
        _instances[_name] = selfptr;
}


GameObject::GameObject(const std::string &name, const std::string &tag) : _tag(tag) {
    std::string objName = name;
    if (_instances.count(name) > 0)
        objName += "- Copy";

    this->_name = objName;
    auto selfptr = std::make_shared<GameObject>(*this);
    _self = selfptr;
    selfptr->_self = selfptr;
    _instances[objName] = selfptr;
}


auto GameObject::operator=(const GameObject &other) -> GameObject & {
    _name = other._name;
    _active = other._active;
    _tag = other._tag;
    _components = other._components;
    _transform = other._transform;
    _ownerId = other._ownerId;
    _layer = other._layer;
    _self = other._self;

    return *this;
};

bool GameObject::operator==(const spic::GameObject &other) { return _name == other._name; }

auto GameObject::operator!=(const spic::GameObject &other) -> bool { return _name != other._name; }

GameObject::operator bool() { return true; } //Docs don't know what it is used for


//void GameObject::AddChild(std::shared_ptr<GameObject> child) {
//    child->_parent = GameObject::Find(this->_name);
//    _children.emplace_back(child);
//}

auto GameObject::GetName() const -> std::string { return _name; }

auto GameObject::GetTag() const -> std::string { return _tag; }

//auto GameObject::Children() -> std::vector<std::shared_ptr<GameObject>> { return _children; }
//
//auto GameObject::Parent() -> std::shared_ptr<GameObject> { return _parent; }


auto GameObject::Find(const std::string &name, bool includeInactive) -> std::shared_ptr<GameObject> {
    if (_instances.count(name) > 0) {
        auto instance = _instances[name];
        if (includeInactive || instance->Active())
            return instance;
    }

    return nullptr;
}

auto GameObject::FindGameObjectsWithTag(const std::string &tag) -> std::vector<std::shared_ptr<GameObject>> {
    std::vector<std::shared_ptr<GameObject>> result;
    for (auto const &[key, val]: _instances) {
        if (val->_tag == tag && val->Active())
            result.emplace_back(val);
    }
    return result;
}

auto GameObject::FindWithTag(const std::string &tag) -> std::shared_ptr<GameObject> {
    for (auto const &[key, val]: _instances) {
        if (val->_tag == tag && val->Active())
            return val;
    }
    return nullptr;
}

void GameObject::Destroy(spic::Component *obj) {
    if (obj == nullptr)
        throw std::runtime_error("Given pointer is empty or invalid");

    for (auto &[name, instance]: _instances) { //For every gameobject
        for (auto &[type, cList]: instance->_components) { //For every componentType
            for (auto iter = cList.begin(); iter != cList.end(); iter++) { //For every component in list
                if (obj == iter->get()) {
                    cList.erase(iter);
                    iter->reset();
                }
            }
        }
    }
}

void GameObject::Destroy(std::shared_ptr<GameObject> obj) {
    if (obj == nullptr)
        throw std::runtime_error("Given pointer is empty or invalid");

//    for(auto& child : obj->_children) {
//        Destroy(child);
//    }

    std::shared_ptr<GameObject> gameObject = Find(obj->_name);
    if (gameObject != nullptr) {
        _instances.erase(gameObject->_name);
        gameObject.reset();
    }
}


void GameObject::Active(bool flag) { _self.lock()->_active = flag; }

bool GameObject::Active() const { return _self.lock()->_active; }

auto GameObject::IsActiveInWorld() const -> bool {
    if (!Active())
        return false;

//    auto par = _self.lock()->_parent;
//
//    if(par != nullptr)
//        return par->IsActiveInWorld();

    return true;
}

void GameObject::SetTransform(const spic::Transform &transform) {
    if (transform.scale < 0) {
        throw InvalidSizeException("scale", "cannot be smaller than 0");
    }

    auto selfPtr = _self.lock();
    auto oldScale = selfPtr->GetTransform().scale;
    auto oldRotation = selfPtr->GetTransform().rotation;
    if (transform.rotation != oldRotation || oldScale != transform.scale) {
        if(oldScale == 0){
            oldScale = 1;
        }
        std::vector<std::string> keys;
        keys.reserve(_components.size()); // For efficiency

        for (auto &_component: _components) {
            keys.push_back(_component.first);
        }

        for (const auto &key: keys) {
            std::vector<std::shared_ptr<Component>> const components = _components[key];
            for (const auto &component: components) {
                //check if component is type of Scaleable
                auto scaleableExtension = std::dynamic_pointer_cast<platformer_engine::Scaleable>(component);
                if (scaleableExtension != nullptr) {
                    scaleableExtension->UpdateScale(oldScale, transform.scale);
                }
                auto rotatableExtension = std::dynamic_pointer_cast<platformer_engine::Rotatable>(component);
                if (rotatableExtension != nullptr) {
                    rotatableExtension->UpdateRotation(transform.rotation);
                }
            }
        }
    }
    selfPtr->_transform = transform;
}

auto GameObject::GetTransform() -> Transform {
    auto selfPtr = _self.lock();
    if (selfPtr != nullptr) {
        return selfPtr->_transform;
    }
    return {};
}

void GameObject::SetOwnerId(int uid) {
    _self.lock()->_ownerId = uid;
}

auto GameObject::GetOwnerId() -> int {
    return _self.lock()->_ownerId;
}

void GameObject::FixComponents() {
    //loop thru all __components values
    std::vector<std::string> keys;
    keys.reserve(_components.size()); // For efficiency

    for (auto &_component: _components) {
        keys.push_back(_component.first);
    }

    for (const auto &key: keys) {
        std::vector<std::shared_ptr<Component>> components = _components[key];
        for (const auto &component: components) {
            component->SetGameObject(_self);
        }
    }
}

void GameObject::FixGameObjectAfterDeserialize() {
    this->ResetSelf();
    this->FixComponents();
}





