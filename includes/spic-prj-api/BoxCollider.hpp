#ifndef BOXCOLLIDER_H_
#define BOXCOLLIDER_H_

#include "Collider.hpp"
#include <boost/serialization/access.hpp>
#include <boost/serialization/export.hpp>

namespace spic {

    /**
     * @brief A collider which represents a rectangular collision area.
     */
    class BoxCollider : public Collider {
    public:
        template<class Archive>
        void serialize(Archive &ar, unsigned int version) {
            ar & boost::serialization::base_object<Collider, BoxCollider>(*this);
            boost::serialization::void_cast_register<BoxCollider, Collider>();
            ar & _width;
            ar & _height;
        }

        /**
         * @brief The collider's width
         * @return The current width
         * @spicapi
         */
        double Width() const { return _width; }

        /**
         * @brief The collider's width
         * @param newWidth The desired width
         * @spicapi
         */
        void Width(double newWidth) { _width = newWidth; }

        /**
         * @brief The collider's height
         * @return The current height
         * @spicapi
         */
        double Height() const { return _height; }

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

#endif // BOXCOLLIDER_H_
