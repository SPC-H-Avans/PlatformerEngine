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
#include <map>

//Singleton class for interfacing with a Graphics library
namespace platformer_engine {
    typedef enum {
        FLIP_NONE = SDL_FLIP_NONE,     /**< Do not flip */
        FLIP_HORIZONTAL = SDL_FLIP_HORIZONTAL,    /**< flip horizontally */
        FLIP_VERTICAL = SDL_FLIP_VERTICAL     /**< flip vertically */
    } SPIC_RendererFlip;

    /**
     * @brief Singleton facade class that creates a SDL2 window and renderer
     */
    class GraphicsFacade {
    public:
        static auto GetInstance() -> GraphicsFacade & {
            static GraphicsFacade s_instance;
            return s_instance;
        }

        GraphicsFacade(GraphicsFacade const &) = delete;

        void operator=(GraphicsFacade const &) = delete;

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

        static inline auto GetTicks() -> Uint64 {return SDL_GetTicks64();};

        /**
         * @brief Load a texture
         * @param id
         * @param fileName
         * @return
         */
        auto LoadTexture(const std::string &id, const std::string &fileName) -> bool;

        /**
         * @brief Load a text object
         */
        auto LoadUIText(const std::string id, const std::string filePath, const std::string text, const int fontSize, const spic::Color color) -> bool;

        /**
         * @brief Draw a texture (complete png for example)
         * @param id
         * @param x
         * @param y
         * @param width
         * @param height
         * @param flip
         */
        void DrawTexture(const std::string &id, int x, int y, int width, int height,
                         const SPIC_RendererFlip &flip = FLIP_NONE, double scale = 1.0,
                         int spriteSheetX = 0, int spriteSheetY = 0);

        /**
         * @brief Draw a text UI element
         */
        void DrawUIText(const std::string textId, const int x, const int y, const int width, const int height);

        void DrawFrame(const std::string &id, int x, int y, int width, int height, int row, int frame,
                       const SPIC_RendererFlip &flip = FLIP_NONE, double scale = 1.0);

        void ClearTextures();

        /**
         * @brief Get interval between tick
         * @return Uinit64 tick interval
         */
        static inline auto GetPerformanceFrequency() -> Uint64 { return SDL_GetPerformanceFrequency(); }


    private:
        GraphicsFacade() = default;

        std::unique_ptr<SDL_Window, std::function<void(SDL_Window *)>> _window{nullptr};
        std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer *)>> _renderer{nullptr};
        std::map<std::string, std::unique_ptr<SDL_Texture, std::function<void(
                SDL_Texture *)>>> _textureMap;
        std::map<std::string, SDL_Texture*> _uiTextMap;
//        std::map<std::string, std::unique_ptr<SDL_Texture, std::function<void(SDL_Texture *)>>> _fontMap;

        /**
         * @brief Converts the color value, which is a double between 0 and 1 to a value between 0 and 255 as int
         * @param colorValue colorValue between 0 and 1
         * @return int colorValue between 0 and 255
         */
        static auto ConvertColorValueToSDLValue(const double &colorValue) -> int;
    };
}//namespace platformer_engine

#endif //PLATFORMER_ENGINE_GRAPHICSFACADE_HPP
