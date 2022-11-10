#ifndef PLATFORMER_ENGINE_TEXTUREMANAGER_H
#define PLATFORMER_ENGINE_TEXTUREMANAGER_H

#include <string>
#include <utility>
#include "Facade/GraphicsFacade.hpp"

//Singleton class to manage all textures
namespace platformer_engine {
    class TextureManager {
    public:
        static TextureManager &GetInstance() {
            static TextureManager s_instance;
            return s_instance;
        }

        /**
         * @brief initialize the TextureManager with the GraphicsFacade
         * @param graphicsFacade a shared ptr of the graphics facade
         */
        void Init(const std::shared_ptr<GraphicsFacade>& graphicsFacade) {
            _graphicsFacade = graphicsFacade;
        }

        /**
         * @brief Load a texture from a file, with an id (id is used to remove textures)
         * @param id Id of the texture
         * @param fileName Path to the texture file
         * @return A true or false value, true if the texture is loaded, false if not
         */
        bool LoadTexture(const std::string& id, const std::string& fileName);

        /**
         * @brief Remove a texture from the texture manager and memory
         * @param id
         */
        void Remove(const std::string& id);

        /**
         * @brief Clear all textures from memory
         * @return
         */
        void Clear();

        /**
         * @brief Draw a texture with the specified parameters
         * @param id ID of the texture
         * @param x X position of the texture
         * @param y Y position of the texture
         * @param width width of the texture
         * @param height height of the texture
         * @param flip Flip the texture according to SPIC_RendererFlip Enum
         */
        void DrawTexture(const std::string& id, int x, int y, int width, int height, const SPIC_RendererFlip& flip = FLIP_NONE);

        TextureManager(TextureManager const &) = delete;

        void operator=(TextureManager const &) = delete;

    private:
        TextureManager() {};

        std::shared_ptr<GraphicsFacade> _graphicsFacade{nullptr};
    };
}
#endif //PLATFORMER_ENGINE_TEXTUREMANAGER_H
