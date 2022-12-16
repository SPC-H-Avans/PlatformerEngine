#ifndef PLATFORMER_ENGINE_SCALEABLE_HPP
#define PLATFORMER_ENGINE_SCALEABLE_HPP

#include <boost/serialization/export.hpp>
#include <boost/serialization/access.hpp>

namespace platformer_engine {
    class Scaleable {
    public:
        Scaleable() = default;

        virtual ~Scaleable() = default;

        template<typename archive>
        void serialize(archive &ar, const unsigned /*version*/) {
        }

        /**
         * @brief Update the scale of the object
         * @param oldScale Old scale
         * @param newScale New scale
         */
        virtual void UpdateScale(double oldScale, double newScale) = 0;

    };

    BOOST_SERIALIZATION_ASSUME_ABSTRACT(platformer_engine::Scaleable);
}  // namespace platformer_engine
#endif //PLATFORMER_ENGINE_SCALEABLE_HPP
