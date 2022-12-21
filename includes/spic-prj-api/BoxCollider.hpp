#ifndef BOXCOLLIDER_H_
#define BOXCOLLIDER_H_

#include "Collider.hpp"
#include <boost/serialization/access.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/vector.hpp>
#include "ComponentExtension/Scaleable.hpp"

namespace spic {

    /**
     * @brief A collider which represents a rectangular collision area.
     */
    class BoxCollider : public Collider, public platformer_engine::Scaleable {
    public:
        template<class Archive>
        void serialize(Archive &ar, unsigned int version) {
            ar.template register_type<BoxCollider>();
            ar & boost::serialization::base_object<Collider, BoxCollider>(*this);
            boost::serialization::void_cast_register<BoxCollider, Collider>();
            ar & _width;
            ar & _height;
        }

        BoxCollider() = default;

        ~BoxCollider() = default;

        void UpdateScale(double oldScale, double newScale) override;

        /**
         * @brief The collider's width
         * @return The current width
         * @spicapi
         */
        [[nodiscard]] auto Width() const -> double { return _width; }

        /**
         * @brief The collider's width
         * @param newWidth The desired width
         * @spicapi
         */
        void Width(double newWidth);

        /**
         * @brief The collider's height
         * @return The current height
         * @spicapi
         */
        [[nodiscard]] auto Height() const -> double { return _height; }

        /**
         * @brief The collider's height
         * @param newHeight The desired height
         * @spicapi
         */
        void Height(double newHeight) { _height = newHeight; }

    private:
        double _width;
        double _height;
    };

}  // namespace spic
//BOOST_SERIALIZATION_ASSUME_ABSTRACT(spic::BoxCollider);

#endif // BOXCOLLIDER_H_
