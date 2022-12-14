#ifndef PLATFORMER_ENGINE_SCENEBUILDER_H
#define PLATFORMER_ENGINE_SCENEBUILDER_H

#include <memory>
#include "GameObject.hpp"
#include "Camera.hpp"
#include "Scene.hpp"

namespace platformer_engine {
    class SceneBuilder {
    public:
        /**
         * @brief Constructor of Scene Builder
         */
        SceneBuilder(const std::string &name);

        /**
         * @brief Add a new Game Object to the scene
         * @param gameObject Game Object to add to the scene
         * @return SceneBuilder Modified Scene Builder
         */
        auto AddGameObject(const spic::GameObject& gameObject) -> SceneBuilder &;

        /**
         * @brief Add a vector of Game Objects to the scene
         * @param gameObjects Vector of Game Objects
         * @return SceneBuilder Modified Scene Builder
         */
        auto AddGameObjects(const std::vector<std::shared_ptr<spic::GameObject>>& gameObjects) -> SceneBuilder &;

        /**
         * @brief Add a new Camera to the scene
         * @param camera Camera to add to the scene
         * @return SceneBuilder Modified Scene Builder
         */
        auto AddCamera(spic::Camera &camera) -> SceneBuilder &;

        /**
         * @brief Finalize the scene and retrieve it
         * @return Scene Built scene
         */
        auto GetScene() -> spic::Scene;

    private:
        /**
         * @brief Current scene object that is being build
         */
        spic::Scene _scene = spic::Scene("New scene");
    };
}

#endif //PLATFORMER_ENGINE_SCENEBUILDER_H
