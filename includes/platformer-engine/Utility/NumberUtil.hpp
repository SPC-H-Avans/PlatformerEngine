#ifndef PLATFORMER_ENGINE_NUMBERUTIL_HPP
#define PLATFORMER_ENGINE_NUMBERUTIL_HPP

namespace platformer_engine {
    class NumberUtil {
        //template function to clamp numbers between x and y
    public:
        /**
         * @brief Restrict a number between min and max
         * @tparam T
         * @param value Current number value
         * @param min Minimal value
         * @param max Max value
         * @return T value between min and max
         */
        template<typename T>
        static inline T clamp(const T &value, const T &min, const T &max) {
            if (value < min) return min;
            if (value > max) return max;
            return value;
        }
    };
}

#endif //PLATFORMER_ENGINE_NUMBERUTIL_HPP
