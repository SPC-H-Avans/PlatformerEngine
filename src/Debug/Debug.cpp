#include "Debug.hpp"
#include "Engine/Engine.hpp"
#include <iostream>

void spic::Debug::LogWarning(const std::string &warning) {
    std::cerr << "WARNING: " << warning << std::endl;
}

void spic::Debug::LogError(const std::string &error) {
    std::cerr << "ERROR: " << error << std::endl;
}

void spic::Debug::Log(const std::string &message) {
    if (platformer_engine::Engine::GetInstance().IsDebugLogsEnabled()) {
        std::cout << "LOG: " << message << std::endl;
    }
}
