#include "Timer/Timer.hpp"
#include "Debug.hpp"
#include "Render/Window.hpp"

static const double MAX_DELTA_TIME = 1000.0F;
static const int MILISECONDS_PER_SECOND = 1000;

void platformer_engine::Timer::Update() {
    _lastTick = _currentTick;
    _currentTick = Window::GetPerformanceFrequency();

    if (_lastTick == -1) {
        _lastTick = _currentTick;
    }

    auto deltaTime = ((_currentTick - _lastTick) * MILISECONDS_PER_SECOND /
                               static_cast<double>(Window::GetPerformanceFrequency()));

    if (deltaTime > MAX_DELTA_TIME) {
        spic::Debug::LogWarning(
                "Can't keep up! Did the system time change, or is the application overloaded? Running " +
                std::to_string(deltaTime) + "ms behind, skipping ticks");
        deltaTime = MAX_DELTA_TIME;
    }

    _deltaTime = deltaTime / MILISECONDS_PER_SECOND;
}