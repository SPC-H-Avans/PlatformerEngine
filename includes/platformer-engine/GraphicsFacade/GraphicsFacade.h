//
// Created by Jaap Rodenburg on 07/11/2022.
//

#ifndef PLATFORMER_ENGINE_GRAPHICSFACADE_H
#define PLATFORMER_ENGINE_GRAPHICSFACADE_H

//SDL2 Facade class that creates a SDL2 window and renderer

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Color.hpp"

#include <string>
#include <vector>

namespace PlatformerEngine {

    /**
     * @brief Facade class that creates a SDL2 window and renderer
     */
    class GraphicsFacade {
    public:
        GraphicsFacade();

        ~GraphicsFacade();

        /**
         * @brief Creates a SDL2 window and renderer
         * @param width The width of the window, in pixels
         * @param height The height of the window, in pixels
         * @param title The title of the window
         * @param color The background color of the window
         * @return True if the window and renderer were created successfully, false otherwise
         * @platformerengine
         */
        bool Init(int width, int height, const std::string &title, const spic::Color &color);

        /**
         * @brief Quit the SDL2 window and renderer
         * @platformerengine
         */
        void Quit();

        /**
         * @brief Render the game to the screen
         * @platformerengine
         */
        void Render();

        /**
         * @brief Clear the screen
         * @platformerengine
         */
        void Clear();

    private:
        std::unique_ptr<SDL_Window, std::function<void(SDL_Window *)>> window;
        std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer *)>> renderer;
    };
}

#endif //PLATFORMER_ENGINE_GRAPHICSFACADE_H
