#ifndef SCENE_H_
#define SCENE_H_

#include "GameObject.hpp"
#include "Camera.hpp"

namespace spic {

    /**
     * @brief Class representing a scene which can be rendered by the Camera.
     */
    class Scene {
        public:
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
            void RemoveObject(const std::string& name);

            /**
             * @brief Get a Game Object from this scene by name
             * @param name Name of the Game Object that needs to be retrieved from this scene
             * @return std::shared_ptr<GameObject> Game Object shared pointer
             * @spicapi
             */
            std::shared_ptr<GameObject> GetObjectByName(const std::string& name);

            /**
             * @brief Import a Game Level and add it to this scene
             * @param path Folder path where to find the Game Level
             * @param fileName Name of the Game Level file
             * @param levelName Name of the Game Level (This level name will be used to retrieve the Game Level from the level ist)
             * @spicapi
             */
            void ImportLevel(const std::string& path, const std::string& fileName, const std::string& levelName);

    private:
        /**
         * @brief List of all Game Objects in this scene
         * @spicapi
         */
        std::vector<std::shared_ptr<GameObject>> _contents;

        std::vector<std::unique_ptr<Camera>> _cameras;

    };

}

#endif // SCENE_H_