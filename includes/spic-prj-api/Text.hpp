#ifndef TEXT_H_
#define TEXT_H_

#include "UIObject.hpp"
#include "Color.hpp"
#include <string>

namespace spic {

    /**
     * @brief Enumeration for different text alignments.
     * @spicapi
     */
    enum class Alignment {
        left,
        center,
        right
    };

    /**
     * @brief Class representing a piece of text which can be rendered.
     * @spicapi
     */
    class Text : public UIObject {
        public:
            /**
             * @brief Text constructor
             * @spicapi
             */
            Text(const std::string& name, double width, double height,
                 const std::string& text, const std::string& fontPath,
                 int fontSize = 24, Color color = Color::Black(),
                 Alignment alignment = Alignment::center); // alignment is currently unused

            /**
            * @brief Render the Text
            * @spicapi
            */
            void Render() override;
        private:
            std::string _text;
            std::string _font;
            int _size;
            Alignment _alignment;
            Color _color;
    };

}

#endif // TEXT_H_
