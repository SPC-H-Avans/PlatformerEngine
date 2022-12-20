#ifndef POINT_H_
#define POINT_H_

namespace spic {

    /**
     * @brief Struct representing both a 2D point and a 2D vector.
     * @spicapi
     */
    struct Point {
        double x = 0.0;
        double y = 0.0;

        template<typename archive> void serialize(archive& ar, const unsigned /*version*/) {
            ar & x;
            ar & y;
        }
        auto operator*(double multiplier) -> Point{
            this->x = this->x * multiplier;
            this->y = this->y * multiplier;
            return *this;
        }
    };

}

#endif // POINT_H_
