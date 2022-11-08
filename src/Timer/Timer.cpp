#include "Timer/Timer.hpp"
#include "Debug.hpp"
#include "Render/Window.hpp"

static const double MAX_DELTA_TIME = 1000.0f;

void PlatformerEngine::Timer::Update() {
    _lastTick = _currentTick;
    _currentTick = Window::GetPerformanceFrequency();

    if (_lastTick == -1) {
        _lastTick = _currentTick;
    }

    auto deltaTime = (double) ((_currentTick - _lastTick) * 1000 /
                               (double) Window::GetPerformanceFrequency());

    if (deltaTime > MAX_DELTA_TIME) {
        spic::Debug::LogWarning(
                "Can't keep up! Did the system time change, or is the application overloaded? Running " +
                std::to_string(deltaTime) + "ms behind, skipping ticks");
        deltaTime = MAX_DELTA_TIME;
    }

    _deltaTime = deltaTime / 1000;
}