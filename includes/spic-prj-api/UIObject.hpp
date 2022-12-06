#ifndef UIOBJECT_H_
#define UIOBJECT_H_

#include "GameObject.hpp"

namespace spic {

    /**
     * @brief Base class for a user interface object like Button or Text.
     * @spicapi
     */
    class UIObject : public GameObject {
        public:
            /**
             * @brief UIObject constructor
             * @spicapi
             */
            UIObject(const std::string &name, double width, double height);

            virtual void Render() = 0;

            /**
             * @brief Get the width
             * @spicapi
             */
            inline auto GetWidth() -> double { return _width; }

            /**
             * @brief Get the height
             * @spicapi
             */
            inline auto GetHeight() -> double { return _height; }

    protected:
            double _width;
            double _height;
    };

}

#endif // UIOBJECT_H_
