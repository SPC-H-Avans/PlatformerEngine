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
            UIObject(const std::string &name, const std::string &tag, double width, double height);

        private:
            double _width;
            double _height;
    };

}

#endif // UIOBJECT_H_
