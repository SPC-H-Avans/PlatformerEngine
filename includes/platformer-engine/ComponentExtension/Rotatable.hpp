#ifndef PLATFORMER_ENGINE_ROTATABLE_HPP
#define PLATFORMER_ENGINE_ROTATABLE_HPP
#include <boost/serialization/export.hpp>
#include <boost/serialization/access.hpp>
namespace platformer_engine {
    class Rotatable {
    public:
        Rotatable() = default;

        virtual ~Rotatable() = default;

        template<typename archive>
        void serialize(archive &ar, const unsigned /*version*/) {
        }

        /**
         * @brief Update the rotation of the object
         * @param newRotation New rotation
         */
        virtual void UpdateRotation(double newRotation) = 0;

    };

    BOOST_SERIALIZATION_ASSUME_ABSTRACT(platformer_engine::Rotatable);
}  // namespace platformer_engine
#endif //PLATFORMER_ENGINE_ROTATABLE_HPP
