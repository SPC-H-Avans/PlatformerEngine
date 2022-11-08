//
// Created by jhpar on 7-11-2022.
//

#ifndef PLATFORMER_ENGINE_TIMER_HPP
#define PLATFORMER_ENGINE_TIMER_HPP

#include <cstdint>

namespace PlatformerEngine {
    class Timer {
    public:
        /**
         * @brief Create a new timer
         */
        Timer() = default;

        /**
         * @brief Get deltatime
         * @return double Deltatime
         */
        inline double DeltaTime() const { return _deltaTime; }

        /**
         * @brief Get the current time scale
         * @return double time scale
         */
        inline double TimeScale() const { return _timeScale; }

        /**
         * @brief Set the time scale
         * @param newTimeScale
         */
        inline void TimeScale(double newTimeScale) { _timeScale = newTimeScale; }

        /**
         * @brief Calculate the new delta time
         */
        void Update();

        static Timer &Instance() {
            static Timer instance;
            return instance;
        };

        /**
        * @brief Deleted copy assignment operator
        */
        Timer &operator=(const Timer &timer) = delete;

        /**
        * @brief Deleted move assignment operator
        */
        Timer &operator=(Timer &&timer) = delete;

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
}

#endif //PLATFORMER_ENGINE_TIMER_HPP
