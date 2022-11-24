#include "Debug.hpp"
#include <iostream>

void spic::Debug::LogWarning(const std::string &warning) {
    std::cerr << "WARNING: " << warning << std::endl;
}

void spic::Debug::LogError(const std::string &error) {
    std::cerr << "ERROR: " << error << std::endl;
}

void spic::Debug::Log(const std::string &message) {
    std::cout << "LOG: " << message << std::endl;
}
