#include <stdexcept>
#include "GameObject.hpp"
using namespace spic;

//Creates the static instances of GameObjects
std::map<std::string, std::shared_ptr<GameObject>> GameObject::_instances;


GameObject::GameObject() {
    std::string objName = xg::newGuid();
    if(_instances.count(objName) > 0)
        objName += "- Copy";

    this->_name = objName;
    auto selfptr = std::make_shared<GameObject>(*this);
    _self = selfptr;
    selfptr->_self = selfptr;
    _instances[objName] = selfptr;
}

GameObject::GameObject(const std::string &name) {
    std::string objName = name;
    if(_instances.count(name) > 0)
        objName += "- Copy";

    this->_name = objName;
    auto selfptr = std::make_shared<GameObject>(*this);
    _self = selfptr;
    selfptr->_self = selfptr;
    _instances[objName] = selfptr;
}

GameObject::GameObject(const std::string &name, const std::string& tag) : _tag(tag) {
    std::string objName = name;
    if(_instances.count(name) > 0)
        objName += "- Copy";

    this->_name = objName;
    auto selfptr = std::make_shared<GameObject>(*this);
    _self = selfptr;
    selfptr->_self = selfptr;
    _instances[objName] = selfptr;
}

auto GameObject::operator=(const GameObject& other) -> GameObject& {
    if(_name == other._name) {
        _active = other._active;
        _tag = other._tag;
        _components = other._components;
        _transform = other._transform;
        _children = other._children;
        _parent = other._parent;
        _ownerId = other._ownerId;
        _layer = other._layer;
    }

    return *this;
};

bool GameObject::operator==(const spic::GameObject &other) { return _name==other._name; }

auto GameObject::operator!=(const spic::GameObject &other) -> bool { return _name!=other._name; }

GameObject::operator bool() { return true; } //Docs don't know what it is used for


void GameObject::AddChild(std::shared_ptr<GameObject> child) {
    child->_parent = GameObject::Find(this->_name);
    _children.emplace_back(child);
}

auto GameObject::GetName() -> std::string { return _name; }

auto GameObject::Children() -> std::vector<std::shared_ptr<GameObject>> { return _children; }

auto GameObject::Parent() -> std::shared_ptr<GameObject> { return _parent; }


auto GameObject::Find(const std::string &name) -> std::shared_ptr<GameObject> {
    if(_instances.count(name) > 0) {
        auto instance = _instances[name];
        if(instance->Active() == true)
            return instance;
    }

    return nullptr;
}

auto GameObject::FindGameObjectsWithTag(const std::string &tag) -> std::vector<std::shared_ptr<GameObject>> {
    std::vector<std::shared_ptr<GameObject>> result;
    for(auto const& [key, val] : _instances) {
        if (val->_tag == tag && val->Active())
            result.emplace_back(val);
    }
    return result;
}

auto GameObject::FindWithTag(const std::string &tag) -> std::shared_ptr<GameObject> {
    for(auto const& [key, val] : _instances) {
        if (val->_tag == tag && val->Active())
            return val;
    }
    return nullptr;
}

void GameObject::Destroy(spic::Component *obj) {
    if(obj == nullptr)
        throw std::runtime_error("Given pointer is empty or invalid");

    for(auto& [name, instance] : _instances) { //For every gameobject
        for(auto& [type, cList] : instance->_components ) { //For every componentType
            for(auto iter = cList.begin(); iter != cList.end(); iter++) { //For every component in list
                if(obj == iter->get()) {
                    cList.erase(iter);
                    iter->reset();
                }
            }
        }
    }
}

void GameObject::Destroy(std::shared_ptr<GameObject> obj) {
    if(obj == nullptr)
        throw std::runtime_error("Given pointer is empty or invalid");

    for(auto& child : obj->_children) {
        Destroy(child);
    }

    std::shared_ptr<GameObject> gameObject = Find(obj->_name);
    _instances.erase(gameObject->_name);
    gameObject.reset();
}



void GameObject::Active(bool flag) { _self.lock()->_active = flag; }
bool GameObject::Active() const { return _self.lock()->_active; }

auto GameObject::IsActiveInWorld() const -> bool {
    if(!Active())
        return false;

    auto par = _self.lock()->_parent;

    if(par != nullptr)
        return par->IsActiveInWorld();

    return true;
}

void GameObject::SetTransform(const spic::Transform &transform) {
    _self.lock()->_transform = transform;
}
auto GameObject::GetTransform() -> Transform { return _self.lock()->_transform; }

void GameObject::SetOwnerId(int uid) {
    _self.lock()->_ownerId = uid;
}

auto GameObject::GetOwnerId() -> int {
    return _self.lock()->_ownerId;
}





