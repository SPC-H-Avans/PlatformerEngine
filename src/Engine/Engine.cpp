#include "Engine/Engine.hpp"
#include <thread>

const int TARGET_FPS = 60;
const double TARGET_FRAME_DELAY = 1000.0 / TARGET_FPS;

bool PlatformerEngine::Engine::Init(int width, int height, const std::string &title, const spic::Color &color) {
    if (window != nullptr) {
        return false;
    }
    window = std::make_unique<Window>(width, height, title, color);
    isRunning = true;
    while (isRunning) {
        uint64_t start = Window::GetPerformanceFrequency();
        auto &timer = Timer::Instance();
        timer.Update();
        //Add system here for input, delta time etc etc
        window->Render();

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
    if (window == nullptr) {
        std::cout << "Can not render without initializing the engine first";
        return;
    }
    window->Render();
}

void PlatformerEngine::Engine::Quit() {
    window->Quit();
    isRunning = false;
}
