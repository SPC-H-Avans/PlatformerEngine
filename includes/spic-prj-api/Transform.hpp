#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include "Point.hpp"

namespace spic {
    /**
     * @brief Instances of this class represent specific 2D transformations.
     * @spicapi
     */
    struct Transform {
        Point position; // Translation (shift)
        double rotation = 0.0; // Rotation, in radians
        double scale = 1.0; // Multiplication factor
    };
} // namespace spic

#endif // TRANSFORM_H_
