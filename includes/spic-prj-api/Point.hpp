#ifndef POINT_H_
#define POINT_H_

#include <cmath>

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

        auto operator /(float &Obj) -> Point
        {
            x /= Obj;
            y /= Obj;
            return *this;
        }

        auto operator /(double &Obj) -> Point
        {
            x /= Obj;
            y /= Obj;
            return *this;
        }

        auto operator /(Point &Obj) -> Point
        {
            x /= Obj.x;
            y /= Obj.y;
            return *this;
        }

        auto operator *(double Obj) -> Point
        {
            x *= Obj;
            y *= Obj;
            return *this;
        }

        auto operator *=(float &Obj) -> Point
        {
            x *= Obj;
            y *= Obj;
            return *this;
        }

        auto operator *(const Point &Obj) -> Point
        {
            x *= Obj.x;
            y *= Obj.y;
            return *this;
        }

        auto operator +(const Point &Obj) -> Point
        {
            x += Obj.x;
            y += Obj.y;
            return *this;
        }

        auto operator +=(Point Obj) -> Point
        {
            x += Obj.x;
            y += Obj.y;
            return *this;
        }

        auto operator -(const Point &Obj) -> Point
        {
            x -= Obj.x;
            y -= Obj.y;
            return *this;
        }

        inline double Length()const
        {
            return sqrt(x * x + y * y);
        }

        auto Equals(Point Obj) const -> bool {
            return x == Obj.x && y == Obj.y;
        }

        void Normalize(){
            double vector_length = this->Length();

            if (vector_length > std::numeric_limits<double>::epsilon())
            {
                this->x /= vector_length;
                this->y /= vector_length;
            }
        }

        /**
        * @brief Truncates this vector so that its length does not exceed the maximum value
        * @param max The maximum value that x and y cannot exceed
        */
        auto Truncate(float max)-> Point {
            if (this->Length() > max)
            {
                this->Normalize();

                *this *= max;
            }
            return *this;
        }

        [[nodiscard]] inline auto LengthSq() const -> double
        {
            return (x * x + y * y);
        }

        [[nodiscard]] inline auto Dot(const Point &other)const -> double
        {
            return x*other.x + y*other.y;
        }

        static auto PointNormalize(const Point &v) -> Point {
            Point vec = v;

            double vector_length = vec.Length();

            if (vector_length > std::numeric_limits<double>::epsilon()) {
                vec.x /= vector_length;
                vec.y /= vector_length;
            }

            return vec;
        }

        // Function to calculate distance
        [[nodiscard]] auto Distance(const Point &other) const -> float
        {
            // Calculating distance
            return sqrt(pow(other.x - x, 2) + pow(other.y - y, 2) * 1.0);
        }
    };



}

#endif // POINT_H_
