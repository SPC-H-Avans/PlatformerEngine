#ifndef PLATFORMER_ENGINE_GRAPHICSFACADE_HPP
#define PLATFORMER_ENGINE_GRAPHICSFACADE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Color.hpp"
#include "Utility/NumberUtil.hpp"
#include <memory>
#include <functional>

#include <string>
#include <vector>

namespace platformer_engine {

    /**
     * @brief Facade class that creates a SDL2 window and renderer
     */
    class GraphicsFacade {
    public:
        GraphicsFacade() = default;
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
        auto Init(int width, int height, const std::string &title, const spic::Color &color) -> bool;

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
        
        /**
         * @brief Get interval between tick
         * @return Uinit64 tick interval
         */
        static inline auto GetPerformanceFrequency() -> Uint64 { return SDL_GetPerformanceFrequency(); }

    private:
        std::unique_ptr<SDL_Window, std::function<void(SDL_Window *)>> _window{nullptr};
        std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer *)>> _renderer{nullptr};

        /**
         * @brief Converts the color value, which is a double between 0 and 1 to a value between 0 and 255 as int
         * @param colorValue colorValue between 0 and 1
         * @return int colorValue between 0 and 255
         */
        static auto ConvertColorValueToSDLValue(const double &colorValue) -> int;
    };
}//namespace platformer_engine

#endif //PLATFORMER_ENGINE_GRAPHICSFACADE_HPP