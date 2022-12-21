#include "Engine/Engine.hpp"
#include "Exceptions/NoWindowException.hpp"
#include "Exceptions/NoServerNetworkManagerActiveException.hpp"
#include "Exceptions/ServerAlreadyActiveException.hpp"
#include "Exceptions/ClientAlreadyActiveException.hpp"
#include "Exceptions/SceneNotLoadedException.hpp"
#include "Exceptions/NoClientNetworkManagerActiveException.hpp"
#include <thread>

const int MILLIS_IN_SECOND = 1000;
const int TARGET_FPS = 60;
const double TARGET_FRAME_DELAY = MILLIS_IN_SECOND / TARGET_FPS;

auto
platformer_engine::Engine::Init(int width, int height, const std::string &title, const spic::Color &color,
                                bool fullScreen,
                                bool debugLogs) -> bool {
    if (_window != nullptr) {
        return false;
    }
    _window = std::make_unique<Window>(width, height, title, color, fullScreen);
    _renderSystem = std::make_unique<RenderSystem>();
    _moveSystem = std::make_unique<MoveSystem>();
    _physicsSystem = std::make_unique<PhysicsSystem>();
    _behaviourSystem = std::make_unique<BehaviourSystem>();
    _dataManager = std::make_unique<DataStorageManager>();
    _clickSystem = std::make_unique<ClickSystem>(fullScreen);

    _debugLogs = debugLogs;

    return true;
}

void platformer_engine::Engine::Start() {
    if (_window == nullptr) {
        throw spic::NoWindowException();

    }

    if (_queuedScene.has_value()) {
        SetActiveScene(_queuedScene.value());
    }

    auto timeInMillis = Window::GetTicks();
    int framesThisSecond = 0;

    _isRunning = true;
    while (_isRunning) {
        uint64_t start = Window::GetPerformanceFrequency();

        Render();
        Update();
        Events();

        framesThisSecond++;
        if (timeInMillis < Window::GetTicks() - MILLIS_IN_SECOND) {
            timeInMillis = Window::GetTicks();
            _fps = framesThisSecond;
            framesThisSecond = 0;
        }

        float elapsedMs =
                (Window::GetPerformanceFrequency() - start) / static_cast<float>(Window::GetPerformanceFrequency()) *
                1000.0F; // NOLINT(cppcoreguidelines-narrowing-conversions)
        if (TARGET_FRAME_DELAY > elapsedMs) {
            int waitDelay = static_cast<int>(TARGET_FRAME_DELAY) - elapsedMs;
            std::this_thread::sleep_for(std::chrono::milliseconds(waitDelay));
        }
    }
}

void platformer_engine::Engine::Update() {
    if (_queuedScene.has_value()) {
        SetActiveScene(_queuedScene.value());
    }

    auto &timer = Timer::Instance();
    timer.Update();

    auto speedMultiplier = /*timer.deltaTime() * */ _speedMultiplier;
    //Call systems
    _moveSystem->Update(speedMultiplier);
    _physicsSystem->Update(speedMultiplier);
    _renderSystem->Update(speedMultiplier);
    _behaviourSystem->Update(speedMultiplier);
    _clickSystem->Update(speedMultiplier);
}

void platformer_engine::Engine::Events() {
    if (_serverNetworkManager != nullptr) {
        _serverNetworkManager->Events();
    }
    auto events = _window->ListenForEvents();
    for (const auto &item: events) {
        if (item == EventsEnum::QUIT) {
            Quit();
        }
    }
}

void platformer_engine::Engine::Render() {
    if (_window == nullptr) {
        throw spic::NoWindowException();
    }
    _window->Clear();
    _renderSystem->Render();
    _window->Render();
}

void platformer_engine::Engine::Quit() {
    _window->Quit();
    _isRunning = false;
}

void platformer_engine::Engine::QueueActiveScene(const std::string &sceneName) {
    if (!std::any_of(_scenes.begin(), _scenes.end(),
                     [sceneName](const Scene &scene) { return scene.GetSceneName() == sceneName; })) {
        throw spic::SceneNotLoadedException();
    }

    _queuedScene = sceneName;
}

void platformer_engine::Engine::SetActiveScene(const std::string &sceneName) {
    if (_window == nullptr) {
        throw spic::NoWindowException();
    }
    for (auto &item: _scenes) {
        if (item.GetSceneName() == sceneName) {
            _window->SetActiveScene(item);

            if (GetNetworkingStatus() == NetworkingStatus::MultiplayerServer) {
                GetServerNetworkManager().CreateNetworkedScene(GetActiveScene());
            }

            //Call all startup functions on systems
            _behaviourSystem->Start();
            _queuedScene.reset();
            return;
        }
    }
    throw spic::SceneNotLoadedException();
}

auto platformer_engine::Engine::GetActiveScene() -> spic::Scene & {
    if (_window == nullptr) {
        throw spic::NoWindowException();
    }
    return _window->GetActiveScene();
}

auto platformer_engine::Engine::GetServerNetworkManager() -> platformer_engine::ServerNetworkManager & {
    if (_serverNetworkManager == nullptr) throw spic::NoServerNetworkManagerActiveException();
    return _serverNetworkManager.operator*();
}

auto platformer_engine::Engine::GetClientNetworkManager() -> platformer_engine::ClientNetworkManager & {
    if (_clientNetworkManager == nullptr) throw spic::NoClientNetworkManagerActiveException();
    return _clientNetworkManager.operator*();
}

void platformer_engine::Engine::HostServer(const std::string &sceneId, int playerLimit, int port) {
    if (GetActiveScene().GetSceneName() != sceneId) {
        SetActiveScene(sceneId);
    }
    if (_serverNetworkManager != nullptr) throw spic::ServerAlreadyActiveException();
    if (_clientNetworkManager != nullptr) throw spic::ClientAlreadyActiveException();
    _serverNetworkManager = std::make_unique<ServerNetworkManager>(GetActiveScene(), playerLimit, port);
}

void platformer_engine::Engine::JoinServer(const std::string &ip, int port) {
    if (_serverNetworkManager != nullptr) throw spic::ServerAlreadyActiveException();
    if (_clientNetworkManager != nullptr) throw spic::ClientAlreadyActiveException();
    _clientNetworkManager = std::make_unique<ClientNetworkManager>();
    _clientNetworkManager->ConnectToServer(ip, port);
}

void platformer_engine::Engine::AddScene(const Scene &new_scene, bool isDefault) {
    if (_defaultScene == "" || isDefault == true) {
        _defaultScene = new_scene.GetSceneName();
    }

    auto iter = std::find_if(_scenes.begin(), _scenes.end(), [&new_scene](const Scene &scene) {
        return scene.GetSceneName() == new_scene.GetSceneName();
    });
    if (iter != _scenes.end())
        *iter = new_scene;
    else
        _scenes.push_back(new_scene);
}

auto platformer_engine::Engine::GetLocalClientId() -> const int {
    if (_clientNetworkManager != nullptr) {
        return _clientNetworkManager->GetLocalPlayerId();
    }
    return 0;
}

auto platformer_engine::Engine::GetNetworkingStatus() -> const platformer_engine::NetworkingStatus {
    if (_clientNetworkManager != nullptr) {
        return NetworkingStatus::MultiplayerClient;
    }
    if (_serverNetworkManager != nullptr) {
        return NetworkingStatus::MultiplayerServer;
    }
    return NetworkingStatus::Singleplayer;
}

