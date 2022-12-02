#ifndef PLATFORMER_ENGINE_TEXTUREMANAGER_H
#define PLATFORMER_ENGINE_TEXTUREMANAGER_H

#include <string>
#include <utility>
#include "Facade/GraphicsFacade.hpp"

//Singleton class to manage all textures
namespace platformer_engine {
    /**
     * @brief The Texture Manager is a singleton class that manages the loading and rendering of textures
     */
    class TextureManager {
    public:
        static auto GetInstance() -> TextureManager & {
            static TextureManager s_instance;
            return s_instance;
        }

        TextureManager(TextureManager const &) = delete;

        void operator=(TextureManager const &) = delete;

        /**
         * @brief Load a texture from a file, with an id (id is used to remove textures)
         * @param id Id of the texture
         * @param fileName Path to the texture file
         * @return A true or false value, true if the texture is loaded, false if not
         */
        auto LoadTexture(const std::string &id, const std::string &fileName) -> bool;

        /**
         * @brief Remove a texture from the texture manager and memory
         * @param id
         */
        void Remove(const std::string &id);

        /**
         * @brief Clear all textures from memory
         * @return
         */
        void ClearTextures();

        /**
         * @brief Draw a texture with the specified parameters
         * @param id ID of the texture
         * @param x X position of the texture
         * @param y Y position of the texture
         * @param width width of the texture
         * @param height height of the texture
         * @param flip Flip the texture according to SPIC_RendererFlip Enum
         * @param scale Scale of the sprite
         */
        void DrawTexture(const std::string &id, int x, int y, int width, int height,
                         const SPIC_RendererFlip &flip = FLIP_NONE, double scale = 1.0,
                         int spriteSheetX = 0, int spriteSheetY = 0);

        void DrawUIText();

        /**
         * @brief Draw a frame of a sprite sheet animation
         * @param id ID of the texture
         * @param x X location on screen
         * @param y Y Location on screen
         * @param width Width of the sprite
         * @param height Height of the sprite
         * @param row Row where the animation is located in the sprite
         * @param frame Frame to draw
         * @param flip Flip the texture according to SPIC_RendererFlip Enum
         * @param scale Scale of the sprite
         */
        void DrawFrame(const std::string &id, int x, int y, int width, int height, int row, int frame,
                       const SPIC_RendererFlip &flip = FLIP_NONE, double scale = 1.0);

    private:
        TextureManager() = default;

        ~TextureManager() = default;
    };
}
#endif //PLATFORMER_ENGINE_TEXTUREMANAGER_H
