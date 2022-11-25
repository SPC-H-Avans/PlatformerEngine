#ifndef PLATFORMER_ENGINE_ENGINE_HPP
#define PLATFORMER_ENGINE_ENGINE_HPP

#include "Render/Window.hpp"
#include "Timer/Timer.hpp"
#include "Physics/PhysicsSystem.hpp"
#include "GameLevel/GameLevel.hpp"
#include <memory>
#include "Scene.hpp"
#include "Texture/RenderSystem.hpp"
#include "Networking/ServerNetworkManager.hpp"
#include "Networking/ClientNetworkManager.hpp"


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
         * @brief Initialize the engine
         * @param width The width of the window in px
         * @param height The height of the window in px
         * @param title  Title of the window
         * @param color Color of the window background
         * @return bool True if the engine is initialized, false if not
         * @platformerengine
         */
        auto Init(int width, int height, const std::string &title, const spic::Color &color) -> bool;

        /**
         * @brief Start the engine, open window, start timer etc.
         * @platformerengine
         */
        void Start();

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

        /**
         * @brief Set the current active Scene
         * @param scene Scene to make active
         * @platformerengine
         */
        void SetActiveScene(const std::string &sceneName);

        /**
         * @brief Get the current active Scene
         * @return std::unique_ptr<spic::Scene>& Current active scene
         * @platformerengine
         */
        auto GetActiveScene() -> spic::Scene &;

        auto GetServerNetworkManager() -> ServerNetworkManager &;

        void HostServer(const std::string &mapId, int playerLimit, int port);

        void JoinServer(const std::string &ip, int port);

    private:
        Engine() = default;

        ~Engine() = default;

        bool _isRunning = false;

        std::unique_ptr<Window> _window = nullptr;
        std::unique_ptr<PhysicsSystem> _physicsSystem = nullptr;
        std::unique_ptr<RenderSystem> _renderSystem = nullptr;
        std::unique_ptr<ServerNetworkManager> _serverNetworkManager = nullptr;
        std::unique_ptr<ClientNetworkManager> _clientNetworkManager = nullptr;

        std::vector<Scene> _scenes;
    };
}//namespace platformer_engine

#endif //PLATFORMER_ENGINE_ENGINE_HPP
