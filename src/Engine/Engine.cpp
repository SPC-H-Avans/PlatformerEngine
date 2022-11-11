#include "Engine/Engine.hpp"
#include <thread>

const int TARGET_FPS = 60;
const double TARGET_FRAME_DELAY = 1000.0 / TARGET_FPS;

auto platformer_engine::Engine::Init(int width, int height, const std::string &title, const spic::Color &color) -> bool {
    if (_window != nullptr) {
        return false;
    }
    _window = std::make_unique<Window>(width, height, title, color);
    _physicsSystem = std::make_unique<PhysicsSystem>(); //TODO remove, this is for testing purposes
    _isRunning = true;
    while (_isRunning) {
        uint64_t start = Window::GetPerformanceFrequency();

        Update();
        Events();
        Render();

        float elapsedMs = (Window::GetPerformanceFrequency() - start) / static_cast<float>(Window::GetPerformanceFrequency()) * 1000.0F; // NOLINT(cppcoreguidelines-narrowing-conversions)
        if (TARGET_FRAME_DELAY > elapsedMs)
        {
            int waitDelay = static_cast<int>(TARGET_FRAME_DELAY) - elapsedMs;
            std::this_thread::sleep_for(std::chrono::milliseconds(waitDelay));
        }
    }
    return true;
}

void platformer_engine::Engine::Update() {
    auto &timer = Timer::Instance();
    timer.Update();
    _physicsSystem->Update();
    //Call systems
}

void platformer_engine::Engine::Events() {
   auto events = _window->ListenForEvents();
    for (const auto &item: events){
        if(item == EventsEnum::QUIT){
            Quit();
        }
    }
}

void platformer_engine::Engine::Render() {
    if (_window == nullptr) {
        std::cout << "Can not render without initializing the engine first";
        return;
    }
    _window->Render();
}

void platformer_engine::Engine::Quit() {
    _window->Quit();
    _isRunning = false;
}
