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
    //instances[objName] = std::shared_ptr<GameObject>(this);
    instances[objName] = std::make_shared<GameObject>(*this);
}

GameObject::GameObject(const std::string &name, const std::string& tag) {
    std::string objName = name;
    if(instances.count(name) > 0)
        objName += "- Copy";

    this->name = objName;
    this->tag = tag;
    //instances[objName] = std::shared_ptr<GameObject>(this);
    instances[objName] = std::make_shared<GameObject>(*this);
}

bool GameObject::operator==(const spic::GameObject &other) { return name==other.name; }

bool GameObject::operator!=(const spic::GameObject &other) { return name!=other.name; }

GameObject::operator bool() { return true; } //Docs don't know what it is used for


void GameObject::AddChild(std::shared_ptr<GameObject> child) {
    child->parent = GameObject::Find(this->name);
    children.emplace_back(child);
}

std::string GameObject::GetName() { return name; }

std::vector<std::shared_ptr<GameObject>> GameObject::Children() { return children; }

std::shared_ptr<GameObject> GameObject::Parent() { return parent; }


std::shared_ptr<GameObject> GameObject::Find(const std::string &name) {
    if(instances.count(name) > 0)
        return instances[name];

    return nullptr;
}

std::vector<std::shared_ptr<GameObject>> GameObject::FindGameObjectsWithTag(const std::string &tag) {
    std::vector<std::shared_ptr<GameObject>> result;
    for(auto const& [key, val] : instances) {
        if (val->tag == tag)
            result.emplace_back(val);
    }
    return result;
}

std::shared_ptr<GameObject> GameObject::FindWithTag(const std::string &tag) {
    for(auto const& [key, val] : instances) {
        if (val->tag == tag)
            return val;
    }
    return nullptr;
}

void GameObject::Destroy(spic::Component *obj) {
    if(obj == nullptr)
        throw std::runtime_error("Given pointer is empty or invalid");

    for(auto& [name, instance] : instances) { //For every gameobject
        for(auto& [type, cList] : instance->components ) { //For every componentType
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

    for(auto& child : obj->children) {
        Destroy(child);
    }

    std::shared_ptr<GameObject> gameObject = Find(obj->name);
    instances.erase(gameObject->name);
    gameObject.reset();
}


void GameObject::Active(bool flag) { active = flag; }
bool GameObject::Active() const { return active; }

bool GameObject::IsActiveInWorld() const {
    if(!Active())
        return false;

    if(parent != nullptr)
        return parent->IsActiveInWorld();

    return true;
}

void GameObject::SetTransform(const spic::Transform &transform) {
    GameObject::Find(this->name)->transform = transform;
}
auto GameObject::GetTransform() -> Transform { return GameObject::Find(this->name)->transform; }

template<class T>
auto GameObject::GetComponent() const -> std::shared_ptr<Component> {
    if(std::is_base_of<Component, T>::value) {
        auto obj = GameObject::Find(this->_name);
        if(obj != nullptr) {
            if(obj->_components.count(typeid(T).name()) > 0) {
                auto cList = obj->_components[typeid(T).name()];
                if(!cList.empty())
                    return cList.front();
            }
        }
    }
    return nullptr;
}




