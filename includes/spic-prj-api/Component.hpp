#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <memory>

namespace spic {
    class GameObject;

    /**
     * @brief Base class for all components.
     */
    class Component {
        public:
            Component() = default;
            /**
             * @brief Virtual destructor.
             * @spicapi
             */
            virtual ~Component() = default;
            Component(const Component& other) = default;
            auto operator=(const Component& other) -> Component& = default;
            Component(Component&& other) = default;

            auto operator=(Component&& other) -> Component& = default;

            /**
             * @brief Getter for active status.
             * @return true if active, false otherwise.
             * @spicapi
             */
            [[nodiscard]] auto Active() const -> bool { return _active; }

            /**
             * @brief flag New active status.
             * @spicapi
             */
            void Active(bool flag) { _active = flag; }

            void SetGameObject(std::weak_ptr<GameObject> gObj) {
                _gameObject = std::move(gObj);
            }

            std::weak_ptr<GameObject> GetGameObject() {
                return _gameObject;
            }

        private:
            /**
             * @brief Active status.
             */
            bool _active = true;
            /**
             * @brief weak pointer to it's GameObject
             */
            std::weak_ptr<GameObject> _gameObject;
    };

} // namespace spic

#endif // COMPONENT_H_
