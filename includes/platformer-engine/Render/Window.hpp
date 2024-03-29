#ifndef PLATFORMER_ENGINE_WINDOW_HPP
#define PLATFORMER_ENGINE_WINDOW_HPP

#include <string>
#include "Color.hpp"
#include "Facade/GraphicsFacade.hpp"
#include "Texture/TextureManager.hpp"
#include "Scene.hpp"
#include "Events/EventsEnum.h"

namespace platformer_engine {
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
        Window(int width, int height, const std::string &title, const spic::Color &color, bool fullScreen);

        /**
         * @brief Render the game on the screen
         * @platformerengine
         */
        void Render();

        /**
         * @brief Clears the window before rendering new objects
         * @platformerengine
         */
        void Clear();

        /**
         * @brief Close the window
         * @platformerengine
         */
        void Quit();

        static auto ListenForEvents() -> std::vector<EventsEnum>;

        /**
         * @brief Get tick interval
         * @return Uinit64 tick interval
         */
        static inline auto
        GetPerformanceFrequency() -> Uint64 { return platformer_engine::GraphicsFacade::GetPerformanceFrequency(); }

        /**
         * @brief Set the current active Scene
         * @param scene Scene to make active
         */
        void SetActiveScene(spic::Scene &scene);

        /**
         * @brief Get the current active Scene
         * @return std::unique_ptr<spic::Scene>& Current active Scene
         */
        auto GetActiveScene() -> spic::Scene &;

        /**
         * @brief Get the screen width
         * @return The screen width
         */
        [[nodiscard]] auto GetWidth() const -> int {
            return _width;
        }

        /**
         * @brief Get the screen height
         * @return The screen height
         */
        [[nodiscard]] auto GetHeight() const -> int {
            return _height;
        }

        static inline auto GetTicks() -> Uint64 { return platformer_engine::GraphicsFacade::GetTicks(); };

    private:
        int _width;
        int _height;
        spic::Scene _activeScene;
    };
}//namespace platformer_engine

#endif //PLATFORMER_ENGINE_WINDOW_HPP
