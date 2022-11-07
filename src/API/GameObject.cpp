//
// Created by Niels on 7-11-2022.
//

#include <stdexcept>
#include "GameObject.hpp"
using namespace spic;

void GameObject::Active(bool flag) { active = flag; }
bool GameObject::Active() const { return active; }

//Creates the static instances of GameObjects
std::map<std::string, std::shared_ptr<GameObject>> GameObject::instances;

//Exception causes the constructor to not call destructor, don't initialize object outside of if statement.
GameObject::GameObject(const std::string &name) {
    if(instances[name] == nullptr) {
        instances[name] = std::make_shared<GameObject>(*this);
        this->name = name;
    } else {
        throw std::invalid_argument("A GameObject with this name already exists");
    }
}

std::shared_ptr<GameObject> GameObject::Find(const std::string &name) {
    return instances[name];
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
}

