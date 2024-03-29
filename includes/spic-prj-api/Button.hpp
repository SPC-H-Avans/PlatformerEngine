#ifndef BUTTON_H_
#define BUTTON_H_

#include "UIObject.hpp"
#include <functional>

namespace spic {

    /**
     * @brief Instances of this class are clickable user interface items.
     */
    class Button : public UIObject {
        public:
        template<typename archive>
        void serialize(archive &ar, const unsigned /*version*/) {
            ar & boost::serialization::base_object<UIObject, Button>(*this);
            boost::serialization::void_cast_register<Button, UIObject>();
            ar & _sprite;
            ar & interactable;
        }
            /**
             * @brief Button constructor
             * @spicapi
             */
            Button(const std::string &name, const Sprite& sprite, const std::string imgPath,
                   double width, double height, bool disabled = false);

            Button();

            /**
             * @brief Render the button
             * @spicapi
             */
            void Render() override;

            /**
             * @brief This function is called when the button is clicked, which
             *        will trigger a call to the registered onClick member.
             * @spicapi
             */
            void Click();

            /**
             * @brief Register the onClick handler to be used when the button is clicked.
             * @param callback The function to register, usually a lambda. But this can be
             *        any kind of callable.
             * @spicapi
             */
            void OnClick(std::function<void()> callback) { onClick = callback; }

            /**
             * @brief Get the sprite
             * @spicapi
             */
            inline auto GetSprite() -> Sprite { return _sprite; }

        private:
            /**
             * @brief When false, the button will not react to clicks.
             */
            bool interactable;

            /**
             * @brief The registered click handler.
             */
            std::function<void()> onClick;

            /**
             * @brief The sprite to render when the button is clicked.
             */
            Sprite _sprite;
    };

}

#endif // BUTTON_H_
