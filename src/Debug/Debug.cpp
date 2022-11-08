//
// Created by Jaap Rodenburg on 08/11/2022.
//
#include "Debug.hpp"
#include <iostream>

void spic::Debug::LogWarning(const std::string &warning) {
    std::cerr << "ERROR: " << warning;
}
