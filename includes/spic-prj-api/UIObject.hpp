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
        template<typename archive>
        void serialize(archive &ar, const unsigned /*version*/) {
            ar & boost::serialization::base_object<GameObject, UIObject>(*this);
            boost::serialization::void_cast_register<UIObject, GameObject>();
            ar & _width;
            ar & _height;
        }
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
    BOOST_SERIALIZATION_ASSUME_ABSTRACT(UIObject);
}

#endif // UIOBJECT_H_
