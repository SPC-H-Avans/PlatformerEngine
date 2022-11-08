#ifndef PLATFORMER_ENGINE_TIMER_HPP
#define PLATFORMER_ENGINE_TIMER_HPP

#include <cstdint>

namespace platformer_engine {
    class Timer {
    public:
        /**
         * @brief Create a new timer
         */
        Timer() = default;
        ~Timer() = default;

        /**
         * @brief Get deltatime
         * @return double Deltatime
         */
        inline auto DeltaTime() const -> double { return _deltaTime; }

        /**
         * @brief Get the current time scale
         * @return double time scale
         */
        inline auto TimeScale() const -> double { return _timeScale; }

        /**
         * @brief Set the time scale
         * @param newTimeScale
         */
        inline void TimeScale(double newTimeScale) { _timeScale = newTimeScale; }

        /**
         * @brief Calculate the new delta time
         */
        void Update();

        static auto Instance() -> Timer & {
            static Timer instance;
            return instance;
        };

        /**
        * @brief Deleted copy assignment operator
        */
        auto operator=(const Timer &timer) -> Timer & = delete;

        /**
        * @brief Deleted move assignment operator
        */
        auto operator=(Timer &&timer) -> Timer & = delete;

        /**
        * @brief Deleted copy constructor
        */
        Timer(const Timer &timer) = delete;

        /**
        * @brief Deleted move constructor
        */
        Timer(Timer &&timer) = delete;

    private:
        uint64_t _currentTick = -1;
        uint64_t _lastTick = -1;
        double _deltaTime = 0.0;
        double _timeScale = 1.0;

    };
}//namespace platformer_engine

#endif //PLATFORMER_ENGINE_TIMER_HPP
