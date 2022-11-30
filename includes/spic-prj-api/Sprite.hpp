#ifndef SPRITERENDERER_H_
#define SPRITERENDERER_H_

#include "Component.hpp"
#include "Color.hpp"
#include <string>
#include "Facade/GraphicsFacade.hpp"
#include "Transform.hpp"
#include "Texture/TextureManager.hpp"
#include <boost/serialization/access.hpp>

namespace spic {

    /**
     * @brief A component representing a sprite (small image)
     * @spicapi
     */
    class Sprite : public Component {
    public:
        template<typename archive> void serialize(archive& ar, const unsigned /*version*/) {
            ar & _spriteId;
            ar & _spriteWidth;
            ar & _spriteHeight;
            ar & _spriteScale;
        }

        Sprite(std::string spriteId, int spriteWidth, int spriteHeight, int sortingLayer = 1, int orderInLayer = 1,
               platformer_engine::SPIC_RendererFlip flip = platformer_engine::FLIP_NONE, Color color = Color::Transparent(),
               double spriteScale = 1.0, int spriteSheetX = 0, int spriteSheetY = 0);

        [[nodiscard]] inline auto GetSpriteId() const -> std::string {return _spriteId;};
        [[nodiscard]] inline auto GetSpriteScale() const -> double {return _spriteScale;};

        /**
         * @brief Render the current sprite
         * @param Transform transform to use
         */
        void Render(spic::Transform transform);

        /**
         * @brief sets the sprite's flip
         */
        void SetFlip(platformer_engine::SPIC_RendererFlip flip) { _flip = flip; }

        /**
         * @brief sets the sprite's color
         */
        void SetColor(Color color) { _color = color; }

        /**
         * @brief sets the sprite's scale, where 1.0 is 100%
         */
        void SetSpriteScale(double spriteScale) { _spriteScale = spriteScale; }

        /**
         * @brief sets the sprite's x and y position relative to the spritesheet
         */
        void SetSpriteSheetPosition(int x, int y) { _spriteSheetX = x, _spriteSheetY = y; }

    private:
        Color _color;
        platformer_engine::SPIC_RendererFlip _flip;
        int _sortingLayer;
        int _orderInLayer;
        int _spriteSheetX;
        int _spriteSheetY;

    protected:
        std::string _spriteId; // NOLINT(cppcoreguidelines-non-private-member-variables-in-classes)
        int _spriteWidth; // NOLINT(cppcoreguidelines-non-private-member-variables-in-classes)
        int _spriteHeight; // NOLINT(cppcoreguidelines-non-private-member-variables-in-classes)
        double _spriteScale; // NOLINT(cppcoreguidelines-non-private-member-variables-in-classes)
    };

}  // namespace spic

#endif // SPRITERENDERER_H_
