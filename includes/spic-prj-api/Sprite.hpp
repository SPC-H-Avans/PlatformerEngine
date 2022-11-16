#ifndef SPRITERENDERER_H_
#define SPRITERENDERER_H_

#include "Component.hpp"
#include "Color.hpp"
#include <string>
#include "Facade/GraphicsFacade.hpp"

namespace spic {

    /**
     * @brief A component representing a sprite (small image)
     * @spicapi
     */
    class Sprite : public Component {
    public:
        Sprite(std::string spriteId, int sortingLayer, int orderInLayer, int spriteWidth, int spriteHeight, platformer_engine::SPIC_RendererFlip flip = platformer_engine::FLIP_NONE, Color color = Color::Transparent());
        private:
        Color _color;
            platformer_engine::SPIC_RendererFlip _flip;
            int _sortingLayer;
            int _orderInLayer;

    protected:
        std::string _spriteId;
        int _spriteWidth;
        int _spriteHeight;
    };

}  // namespace spic

#endif // SPRITERENDERER_H_
