#ifndef PLATFORMER_ENGINE_ENGINE_HPP
#define PLATFORMER_ENGINE_ENGINE_HPP

#include "Render/Window.hpp"
#include "Timer/Timer.hpp"
#include "Physics/PhysicsSystem.hpp"
#include <memory>


namespace platformer_engine {
    /**
    * @brief Engine is a singleton class which is the core of the game
    */
    class Engine {
    public:
        /**
         * @brief Get instance of the Engine class
         * @return Engine class
         * @platformerengine
         */
        static inline auto GetInstance() -> Engine & {
            static Engine instance;
            return instance;
        }

        Engine(Engine const &) = delete;

        void operator=(Engine const &) = delete;

        Engine(Engine &&) = delete;

        void operator=(Engine &&) = delete;

        /**
         * @brief Start the engine and create a window
         * @param width The width of the window in px
         * @param height The height of the window in px
         * @param title  Title of the window
         * @param color Color of the window background
         * @return bool True if the engine is initialized, false if not
         * @platformerengine
         */
        auto Init(int width, int height, const std::string &title, const spic::Color &color) -> bool;

        /**
         * @brief Render the game on the screen
         * @platformerengine
         */
        void Render();

        /**
         * @brief Run systems to update gameObjects
         */
        void Update();

        /**
         * @brief Check for events
         * @platformerengine
         */
        void Events();

        /**
         * @brief Quit the engine
         * @platformerengine
         */
        void Quit();


    private:
        Engine() = default;
        ~Engine() = default;
        bool _isRunning = false;

        std::unique_ptr<Window> _window = nullptr;
        std::unique_ptr<PhysicsSystem> _physicsSystem = nullptr;
    };
}//namespace platformer_engine

#endif //PLATFORMER_ENGINE_ENGINE_HPP
