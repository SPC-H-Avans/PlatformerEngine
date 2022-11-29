#ifndef SCENE_H_
#define SCENE_H_

#include <functional>

#include "GameObject.hpp"
#include "Camera.hpp"

namespace spic {

    /**
     * @brief Class representing a scene which can be rendered by the Camera.
     */
    class Scene {
    public:
        Scene(const std::string &sceneName);

        Scene() = default;

        /**
         * @brief This function is called by a Camera to render the scene on the engine.
         * @spicapi
         */
        void RenderScene();

        /**
         * @brief Add a new Game Object to this scene
         * @param gameObject Game Object shared pointer
         * @spicapi
         */
        void AddObject(const std::shared_ptr<GameObject>& gameObject);

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

        [[nodiscard]] inline auto
        GetAllObjects() const -> std::vector<std::shared_ptr<GameObject>> { return _contents; };

        auto GetObjectCount() -> int;

        /**
         * @brief Import a Game Level and add it to this scene
         * @param path Folder path where to find the Game Level
         * @param fileName Name of the Game Level file
         * @param levelName Name of the Game Level (This level name will be used to retrieve the Game Level from the level ist)
         * @spicapi
         */
        static void ImportLevel(const std::string &id, const std::string &filePath, const std::string &fileName, const std::map<int, std::function<std::shared_ptr<spic::GameObject>(spic::Transform)>> &config);

        /**
         * @brief Add a camera to this scene
         * @param camera Camera shared pointer
         * @spicapi
         */
        void AddCamera(const std::shared_ptr<Camera> &camera);

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
         * @brief Remove the levels from memory
         */
//        ~Scene();

        /**
         * @brief Get current scene name
         * @return std::string Scene name
         */
        inline auto GetSceneName() const -> std::string { return _sceneName; };

    private:
        /**
         * @brief Render all GameObjects in this scene
         */
        void RenderGameObjects();

        /**
         * @brief List of all Game Objects in this scene
         * @spicapi
         */
        std::vector<std::shared_ptr<GameObject>> _contents;

        /**
         * @brief Default values of the objects used to reset a scene after its been played.
         */
        std::vector<GameObject> _origins {};

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
    };

}  // namespace spic

#endif // SCENE_H_