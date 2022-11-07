//
// Created by Niels on 7-11-2022.
//
#include "Builder/GameObjectBuilder.hpp"

void GameObjectBuilder::Reset(const std::string& name) {
    this->gameObject = std::make_unique<>()
}