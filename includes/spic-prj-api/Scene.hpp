#ifndef SCENE_H_
#define SCENE_H_

#include <functional>

#include "GameObject.hpp"
#include "Camera.hpp"
#include <boost/serialization/access.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/vector.hpp>
#include "UIObject.hpp"

namespace spic {

    /**
     * @brief Class representing a scene which can be rendered by the Camera.
     */
    class Scene {
    public:
        template<typename archive>
        void serialize(archive &ar, const unsigned /*version*/) {
            ar & _sceneName;
            ar & _origins;
            //ar & _contents;
            ar & _activeCamera;
            ar & _cameras;
        }

        Scene(const std::string &sceneName);

        Scene() = default;

        /**
         * @brief This function is called by a Camera to render the scene on the engine.
         * @spicapi
         */
        void RenderScene();

        /**
         * @brief Make a copy of the referenced gameObject and add it to the scene
         * @param gameObject Game Object shared pointer
         * @spicapi
         */
        void AddObject(const GameObject &gameObject);

        /**
         * @brief Add a new UI Object to this scene
         * @param uiObject
         * @spicapi
         */
        void AddUIObject(const std::shared_ptr<spic::UIObject> &uiObject);

        /**
         * @brief Remove a Game Object from this scene by name
         * @param name Name of the Game Objects that needs to be removed from this scene
         * @spicapi
         */
        void RemoveObject(const std::string &name);

        /**
         * @brief Get a Game Object from this scene by name
         * @param name Name of the Game Object that needs to be retrieved from this scene
         * @return std::shared_ptr<GameObject> Game Object shared pointer
         * @spicapi
         */
        auto GetObjectByName(const std::string &name) -> std::shared_ptr<GameObject>;

        /**
         * @brief Get the GameObjects in this scene
         * @spicapi
         */
        [[nodiscard]] inline auto
        GetAllObjects() const -> std::vector<std::shared_ptr<GameObject>> { return _contents; };

        /**
         * @brief Get the UIObjects in this scene
         * @spicapi
         */
        [[nodiscard]] inline auto
        GetAllUIObjects() const -> std::vector<std::shared_ptr<UIObject>> { return _uiObjects; };

        /**
         * @brief Get the number of GameObjects currently in this scene
         * @spicapi
         */
        auto GetObjectCount() -> int;

        /**
         * @brief Import a Game Level and add it to this scene
         * @param id The id of the level
         * @param filePath Folder path where to find the Game Level
         * @param fileName Name of the Game Level file
         * @param config A map of Tile IDs and their corresponding Game Object constructors
         * @spicapi
         */
        void ImportLevel(const std::string &id, const std::string &filePath, const std::string &fileName,
                         const std::map<int, std::function<spic::GameObject(Transform)>> &config);

        /**
         * @brief Add a camera to this scene
         * @param camera Camera shared pointer
         * @spicapi
         */
        void AddCamera(Camera &camera);

        /**
         * @brief Get a camera by name from this scene
         * @param name Camera name
         * @return std::shared_ptr<Camera> Camera shared pointer
         * @spicapi
         */
        auto GetCameraByName(const std::string &name) -> std::shared_ptr<Camera>;

        /**
         * @brief Set active camera by name; this camera will be used to render the scene
         * @param name Camera name
         * @spicapi
         */
        void SetActiveCameraByName(const std::string &name);

        /**
         * @brief Get the currently active camera
         * @spicapi
         */
        auto GetActiveCamera() -> std::shared_ptr<spic::Camera>;

        /**
         * @brief Delete camera by name from this scene
         * @param name Camera name
         */
        void DeleteCameraByName(const std::string &name);

        /**
         * @brief resets all GameObjects connected to this scene to their original state.
         */
        void ResetScene();

        /**
         * @brief Get current scene name
         * @return std::string Scene name
         */
        inline auto GetSceneName() const -> std::string { return _sceneName; };

        /**
         * @brief Sets a scene name for handling scene flow.
         * @param sceneName String must be a valid scene loaded on the engine
         */
        void SetNextScene(const std::string sceneName);

        /**
         *
         * @return an optional which can hold the next scene if not nullopt
         */
        auto GetNextScene() const -> std::optional<std::string>;

    private:
        /**
         * @brief Render all GameObjects in this scene
         */
        void RenderGameObjects();

        /**
         * @brief Render all UIObjects in this scene
         */
        void RenderUIObjects();

        /**
         * @brief List of all Game Object Unique Identifiers in this scene
         * @spicapi
         */
        std::vector<std::shared_ptr<GameObject>> _contents;

        /**
         * @brief List of all UIObjects in this scene
         * @spicapi
         */
        std::vector<std::shared_ptr<UIObject>> _uiObjects;

        /**
         * @brief Default values of the objects used to reset a scene after its been played.
         */
        std::vector<GameObject> _origins{};

        /**
         * @brief List of all Cameras in this scene
         * @spicapi
         */
        std::vector<std::shared_ptr<Camera>> _cameras;

        /**
         * @brief Active Camera in this scene
         * @spicapi
         */
        std::shared_ptr<Camera> _activeCamera = nullptr;
        std::string _sceneName{"Null Scene"};
        std::optional<std::string> _nextScene;
    };

}  // namespace spic

#endif // SCENE_H_