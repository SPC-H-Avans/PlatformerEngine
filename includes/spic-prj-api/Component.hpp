#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <memory>
#include <boost/serialization/access.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/export.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include "boost/archive/text_iarchive.hpp"
#include "boost/archive/text_oarchive.hpp"
#include "Networking/boost/portable_binary_iarchive.hpp"
#include "Networking/boost/portable_binary_oarchive.hpp"

namespace spic {
    class GameObject;

    /**
     * @brief Base class for all components.
     */
    class Component {
    public:

        template<typename archive>
        void serialize(archive &ar, const unsigned /*version*/) {
            ar & _active;
        }

        Component() = default;

        /**
         * @brief Virtual destructor.
         * @spicapi
         */
        virtual ~Component() = default;

        Component(const Component &other) = default;

        auto operator=(const Component &other) -> Component & = default;

        Component(Component &&other) = default;

        auto operator=(Component &&other) -> Component & = default;

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

        /**
         * @brief Set a new parent game object
         * @param gObj GameObject
         */
        void SetGameObject(std::weak_ptr<GameObject> gObj) {
            _gameObject = std::move(gObj);
        }

        /**
         * @brief Get the parent game object
         * @return GameObject, parent game object
         */
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

BOOST_SERIALIZATION_ASSUME_ABSTRACT(spic::Component);

#endif // COMPONENT_H_
