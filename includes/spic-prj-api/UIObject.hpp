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

    protected:
            double _width;
            double _height;
    };

}

#endif // UIOBJECT_H_
