#include <stdexcept>
#include "GameObject.hpp"
using namespace spic;

//Creates the static instances of GameObjects
std::map<std::string, std::shared_ptr<GameObject>> GameObject::instances;

GameObject::GameObject(const std::string &name) {
    std::string objName = name;
    if(instances.count(name) > 0)
        objName += "- Copy";

    this->name = objName;
    auto selfptr = std::make_shared<GameObject>(*this);
    self = selfptr;
    instances[objName] = selfptr;
}

GameObject::GameObject(const std::string &name, const std::string& tag) : tag(tag) {
    std::string objName = name;
    if(instances.count(name) > 0)
        objName += "- Copy";

    this->name = objName;
    auto selfptr = std::make_shared<GameObject>(*this);
    self = selfptr;
    instances[objName] = selfptr;
}

bool GameObject::operator==(const spic::GameObject &other) { return _name==other._name; }

bool GameObject::operator!=(const spic::GameObject &other) { return _name!=other._name; }

GameObject::operator bool() { return true; } //Docs don't know what it is used for


void GameObject::AddChild(std::shared_ptr<GameObject> child) {
    child->_parent = GameObject::Find(this->_name);
    _children.emplace_back(child);
}

auto GameObject::GetName() -> std::string { return _name; }

auto GameObject::Children() -> std::vector<std::shared_ptr<GameObject>> { return _children; }

auto GameObject::Parent() -> std::shared_ptr<GameObject> { return _parent; }


auto GameObject::Find(const std::string &name) -> std::shared_ptr<GameObject> {
    if(instances.count(name) > 0)
        return instances[name];

    return nullptr;
}

auto GameObject::FindGameObjectsWithTag(const std::string &tag) -> std::vector<std::shared_ptr<GameObject>> {
    std::vector<std::shared_ptr<GameObject>> result;
    for(auto const& [key, val] : instances) {
        if (val->_tag == tag)
            result.emplace_back(val);
    }
    return result;
}

auto GameObject::FindWithTag(const std::string &tag) -> std::shared_ptr<GameObject> {
    for(auto const& [key, val] : instances) {
        if (val->_tag == tag)
            return val;
    }
    return nullptr;
}

void GameObject::Destroy(spic::Component *obj) {
    if(obj == nullptr)
        throw std::runtime_error("Given pointer is empty or invalid");

    for(auto& [name, instance] : instances) { //For every gameobject
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
    instances.erase(gameObject->_name);
    gameObject.reset();
}



void GameObject::Active(bool flag) { self.lock()->active = flag; }
bool GameObject::Active() const { return self.lock()->active; }

auto GameObject::IsActiveInWorld() const -> bool {
    if(!Active())
        return false;

    auto par = self.lock()->parent;

    if(par != nullptr)
        return par->IsActiveInWorld();

    return true;
}

void GameObject::SetTransform(const spic::Transform &transform) {
    GameObject::Find(this->_name)->_transform = transform;
}
auto GameObject::GetTransform() -> Transform { return GameObject::Find(this->_name)->_transform; }





