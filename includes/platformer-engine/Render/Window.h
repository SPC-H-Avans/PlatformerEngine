//
// Created by Jaap Rodenburg on 07/11/2022.
//

#ifndef PLATFORMER_ENGINE_WINDOW_H
#define PLATFORMER_ENGINE_WINDOW_H

#include <string>
#include "Color.hpp"
#include "GraphicsFacade/GraphicsFacade.h"

namespace PlatformerEngine {
    /**
     * @brief The Window class represents a window on the screen.
     * @details The window is the main interface to the graphics system. It is used to draw graphics on the screen.
     */
    class Window {
    public:
        /**
         * @brief Constructor, accepting a title, a window size and background color.
         * @param width The width of the window, in pixels.
         * @param height The height of the window, in pixels.
         * @param title The title of the window.
         * @param color The background color of the window.
         * @platformerengine
         */
        Window(int width, int height, const std::string &title, const spic::Color &color);

        /**
         * @brief Render the game on the screen
         * @platformerengine
         */
        void Render();

        /**
         * @brief Close the window
         * @platformerengine
         */
        void Quit();

    private:
        GraphicsFacade graphicsFacade;
    };
}

#endif //PLATFORMER_ENGINE_WINDOW_H
