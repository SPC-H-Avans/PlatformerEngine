#ifndef SPRITERENDERER_H_
#define SPRITERENDERER_H_

#include "Component.hpp"
#include "Color.hpp"
#include <string>
#include "Facade/GraphicsFacade.hpp"
#include "Transform.hpp"
#include "Texture/TextureManager.hpp"

namespace spic {

    /**
     * @brief A component representing a sprite (small image)
     * @spicapi
     */
    class Sprite : public Component {
    public:
        Sprite(std::string spriteId, int sortingLayer, int orderInLayer, int spriteWidth, int spriteHeight,
               platformer_engine::SPIC_RendererFlip flip = platformer_engine::FLIP_NONE, Color color = Color::Transparent(),
               double spriteScale = 1.0, int spriteSheetRow = 0, int spriteSheetCol = 0);
        [[nodiscard]] inline auto GetSpriteId() const -> std::string {return _spriteId;};
        [[nodiscard]] inline auto GetSpriteScale() const -> double {return _spriteScale;};

        /**
         * @brief Render the current sprite
         * @param Transform transform to use
         */
        void Render(spic::Transform transform);

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
