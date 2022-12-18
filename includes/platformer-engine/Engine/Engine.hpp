#ifndef PLATFORMER_ENGINE_ENGINE_HPP
#define PLATFORMER_ENGINE_ENGINE_HPP

#include <memory>

#include "Render/Window.hpp"
#include "Timer/Timer.hpp"
#include "Scene.hpp"
#include "Physics/PhysicsSystem.hpp"
#include "Texture/RenderSystem.hpp"
#include "Behaviour/BehaviourSystem.hpp"
#include "UI/ClickSystem.hpp"
#include "Networking/ServerNetworkManager.hpp"
#include "Networking/ClientNetworkManager.hpp"
#include "Exceptions/NoWindowException.hpp"
#include "Behaviour/BehaviourSystem.hpp"
#include "Audio/AudioManager.hpp"
#include "Storage/DataStorageManager.hpp"
#include "Networking/NetworkingStatus.hpp"


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
         * @param debugLogs Enable debug logs
         * @return bool True if the engine is initialized, false if not
         * @platformerengine
         */
        auto
        Init(int width, int height, const std::string &title, const spic::Color &color, bool fullScreen, bool debugLogs = false) -> bool;

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
         * @brief Queues a scene to be set as active whenever the engine finds possible
         * @param scene Scene to be set active
         * @platformerengine
         */
        void QueueActiveScene(const std::string &sceneName);

        /**
         * @brief Get the current active Scene
         * @return std::unique_ptr<spic::Scene>& Current active scene
         * @platformerengine
         */
        auto GetActiveScene() -> spic::Scene &;

        /**
         * @brief Add a scene to the scene list
         * @param scene
         * @param isDefault determines wether the scene will be set as the default scene
         */
        void AddScene(const Scene &scene, bool isDefault = false);

        /**
         * @brief Get the server network manager when active
         * @return ServerNetworkManager
         */
        auto GetServerNetworkManager() -> ServerNetworkManager &;

        /**
         * @brief Get the client network manager when active
         * @return ClientNetworkManager
         */
        auto GetClientNetworkManager() -> ClientNetworkManager &;

        /**
         * @brief Host a new server and load into a scene
         * @param sceneId scene to use
         * @param playerLimit Max player amount
         * @param port Port
         */
        void HostServer(const std::string &sceneId, int playerLimit, int port);

        /**
         * @brief Join a server by IP and port
         * @param ip IP of the server
         * @param port Port of the server
         */
        void JoinServer(const std::string &ip, int port);

        /**
         * @brief Returns the number of frames per second
         */
        inline auto GetFPS() -> int { return _fps; }

        /**
         * @brief Get local client is, local client id is 0 when not in a server or when being the host
         * @return int local client id
         */
        auto GetLocalClientId() -> const int;

        /**
         * @brief Get the networking status
         * @return NetworkingStatus
         */
        auto GetNetworkingStatus() -> const NetworkingStatus;

        /**
         * @brief Is debug logs enabled
         * @return bool True if debug logs are enabled, false if not
         */
        [[nodiscard]] inline auto IsDebugLogsEnabled() const -> bool { return _debugLogs; }

        /**
         * @brief Set debug logs enabled
         * @param enabled  True if debug logs are enabled, false if not
         */
        inline void SetDebugLogsEnabled(bool enabled) { _debugLogs = enabled; }

        /**
         * @brief Get a reference to the window
         * @return a reference to the window
         */
        auto GetWindow() -> Window &{
            if(_window == nullptr){
                throw spic::NoWindowException();
            }

            return *_window;
        }

        /**
         * @brief returns the name of the scene set as default.
         * @return
         */
        auto GetDefaultSceneName() -> std::string {
            return _defaultScene;
        }

        /**
        * @brief returns the manager for datastoring
        * @return a DataStorageManager for saving and loading to a file
        */
        auto GetDataManager() -> DataStorageManager& {
            return *_dataManager;
        }

    private:
        Engine() = default;

        ~Engine() = default;

        bool _isRunning = false;
        bool _debugLogs = false;
        int _fps = 0;

         /**
         * @brief Set the current active Scene
         * @param scene Scene to make active
         * @platformerengine
         */
        void SetActiveScene(const std::string &sceneName);

        std::unique_ptr<Window> _window = nullptr;
        std::unique_ptr<PhysicsSystem> _physicsSystem = nullptr;
        std::unique_ptr<RenderSystem> _renderSystem = nullptr;
        std::unique_ptr<BehaviourSystem> _behaviourSystem = nullptr;
        std::unique_ptr<ClickSystem> _clickSystem = nullptr;
        std::unique_ptr<ServerNetworkManager> _serverNetworkManager = nullptr;
        std::unique_ptr<ClientNetworkManager> _clientNetworkManager = nullptr;
        std::unique_ptr<DataStorageManager> _dataManager = nullptr;

        std::vector<Scene> _scenes;
        std::optional<std::string> _queuedScene;
        std::string _defaultScene;
    };
}//namespace platformer_engine

#endif //PLATFORMER_ENGINE_ENGINE_HPP
