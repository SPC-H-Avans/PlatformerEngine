#ifndef POINT_H_
#define POINT_H_

#include <math.h>

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

        auto operator *(double &Obj) -> Point
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

        auto operator +=(Point &Obj) -> Point
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

        inline double Dot(const Point &v2)const
        {
            return x*v2.x + y*v2.y;
        }

        static Point PointNormalize(const Point &v) {
            Point vec = v;

            double vector_length = vec.Length();

            if (vector_length > std::numeric_limits<double>::epsilon()) {
                vec.x /= vector_length;
                vec.y /= vector_length;
            }

            return vec;
        }
    };



}

#endif // POINT_H_
