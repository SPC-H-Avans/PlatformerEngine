//
// Created by Jaap Rodenburg on 07/11/2022.
//

#ifndef PLATFORMER_ENGINE_ENGINE_H
#define PLATFORMER_ENGINE_ENGINE_H

#include "Render/Window.h"


namespace PlatformerEngine {
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
        static inline Engine &getInstance() {
            static Engine instance;
            return instance;
        }

        Engine(Engine const &) = delete;

        void operator=(Engine const &) = delete;

        /**
         * @brief Start the engine and create a window
         * @param width The width of the window in px
         * @param height The height of the window in px
         * @param title  Title of the window
         * @param color Color of the window background
         * @return bool True if the engine is initialized, false if not
         * @platformerengine
         */
        bool Init(int width, int height, const std::string &title, const spic::Color &color);

        /**
         * @brief Render the game on the screen
         * @platformerengine
         */
        void Render();

        /**
         * @brief Quit the engine
         * @platformerengine
         */
        void Quit();

    private:
        Engine() = default;

    private:
        std::unique_ptr<Window> window = nullptr;
    };
}

#endif //PLATFORMER_ENGINE_ENGINE_H
