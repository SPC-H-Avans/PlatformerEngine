#include "Engine/Engine.hpp"
#include <thread>

const int TARGET_FPS = 60;
const double TARGET_FRAME_DELAY = 1000.0 / TARGET_FPS;

auto PlatformerEngine::Engine::Init(int width, int height, const std::string &title, const spic::Color &color) -> bool {
    if (_window != nullptr) {
        return false;
    }
    _window = std::make_unique<Window>(width, height, title, color);
    _isRunning = true;
    while (_isRunning) {
        uint64_t start = Window::GetPerformanceFrequency();
        auto &timer = Timer::Instance();
        timer.Update();
        //Add system here for input, delta time etc etc
        _window->Render();

        float elapsedMs = (Window::GetPerformanceFrequency() - start) / static_cast<float>(Window::GetPerformanceFrequency()) * 1000.0f; // NOLINT(cppcoreguidelines-narrowing-conversions)
        if (TARGET_FRAME_DELAY > elapsedMs)
        {
            int waitDelay = (int)TARGET_FRAME_DELAY - elapsedMs;
            std::this_thread::sleep_for(std::chrono::milliseconds(waitDelay));
        }
    }
    return true;
}

void PlatformerEngine::Engine::Render() {
    if (_window == nullptr) {
        std::cout << "Can not render without initializing the engine first";
        return;
    }
    _window->Render();
}

void PlatformerEngine::Engine::Quit() {
    _window->Quit();
    _isRunning = false;
}
