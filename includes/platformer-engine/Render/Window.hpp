
#ifndef PLATFORMER_ENGINE_WINDOW_HPP
#define PLATFORMER_ENGINE_WINDOW_HPP

#include <string>
#include "Color.hpp"
#include "Facade/GraphicsFacade.hpp"
#include "Facade/InputFacade.hpp"
#include "Scene.hpp"

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

        auto ListenForEvents() -> std::vector<EventsEnum>;

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
        void SetActiveScene(std::unique_ptr<spic::Scene> scene);

        /**
         * @brief Get the current active Scene
         * @return std::unique_ptr<spic::Scene>& Current active Scene
         */
        std::unique_ptr<spic::Scene>& GetActiveScene();


    private:
        GraphicsFacade _graphicsFacade;
        InputFacade _inputFacade;

        std::unique_ptr<spic::Scene> _activeScene = nullptr;
    };
}//namespace platformer_engine

#endif //PLATFORMER_ENGINE_WINDOW_HPP
