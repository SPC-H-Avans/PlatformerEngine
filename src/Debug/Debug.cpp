#include "Debug.hpp"
#include <iostream>

void spic::Debug::LogWarning(const std::string &warning) {
    std::cerr << "ERROR: " << warning << std::endl;
}
