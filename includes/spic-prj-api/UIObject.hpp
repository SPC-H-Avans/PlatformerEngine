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
            UIObject(const std::string &name, const std::string &tag, double width, double height);

        private:
            double width;
            double height;
    };

}

#endif // UIOBJECT_H_
