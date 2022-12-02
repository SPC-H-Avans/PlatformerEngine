#ifndef COLOR_H_
#define COLOR_H_
#include <boost/serialization/access.hpp>
#include <boost/serialization/export.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
namespace spic {

    /**
     * @brief Color represents a red-green-blue color with alpha.
     */
    class Color {
    public:
        template <class Archive>
        void serialize(Archive& ar, unsigned int version){
            ar & r;
            ar & g;
            ar & b;
            ar & a;
        }
        /**
         * @brief Constructor, accepting an rgb value and an alpha (transparency).
         * @param red The red component, 0 ≤ r ≤ 1.
         * @param green The green component, 0 ≤ g ≤ 1.
         * @param blue The blue component, 0 ≤ b ≤ 1.
         * @param alpha The transparency component, 0 ≤ alpha ≤ 1.
         * @spicapi
         */
        Color(double red, double green, double blue, double alpha);

        /**
         * @brief One of the standard colors (read-only): white.
         * @return A reference to a statically allocated Color instance.
         * @spicapi
         */
        static auto White() -> const Color & { return _white; }

        /**
         * @brief One of the standard colors (read-only): red.
         * @return A reference to a statically allocated Color instance.
         * @spicapi
         */
        static auto Red() -> const Color & { return _red; }

        /**
         * @brief One of the standard colors (read-only): green.
         * @return A reference to a statically allocated Color instance.
         * @spicapi
         */
        static auto Green() -> const Color & { return _green; }

        /**
         * @brief One of the standard colors (read-only): blue.
         * @return A reference to a statically allocated Color instance.
         * @spicapi
         */
        static auto Blue() -> const Color & { return _blue; }

        /**
         * @brief One of the standard colors (read-only): cyan.
         * @return A reference to a statically allocated Color instance.
         * @spicapi
         */
        static auto Cyan() -> const Color & { return _cyan; }

        /**
         * @brief One of the standard colors (read-only): magenta.
         * @return A reference to a statically allocated Color instance.
         * @spicapi
         */
        static auto Magenta() -> const Color & { return _magenta; }

        /**
         * @brief One of the standard colors (read-only): yellow.
         * @return A reference to a statically allocated Color instance.
         * @spicapi
         */
        static auto Yellow() -> const Color & { return _yellow; }

        /**
         * @brief One of the standard colors (read-only): transparent.
         * @return
         */
        static auto Transparent() -> const Color & { return _transparent; }

        /**
         * @brief One of the standard colors (read-only): black.
         * @return A reference to a statically allocated Color instance.
         * @spicapi
         */
        static auto Black() -> const Color & { return _black; }
        // ... more standard colors here

        /**
         * @brief Get the red value of the color.
         * @spicapi
         * @return double The red value of the color
         */
        inline auto GetRedValue() const -> const double { return r; }

        /**
         * @brief Get the green value of the color.
         * @spicapi
         * @return double The green value of the color
         */
        inline auto GetGreenValue() const -> const double { return g; }

        /**
         * @brief Get the blue value of the color.
         * @spicapi
         * @return double The blue value of the color
         */
        inline auto GetBlueValue() const -> const double { return b; }

        /**
         * @brief Get the alpha value of the color.
         * @return double The alpha value of the color
         * @spicapi
         */
        inline auto GetAlphaValue() const -> const double { return a; }

    private:
        double r = 0;
        double g = 0;
        double b = 0;
        double a = 0;

        static Color _white;
        static Color _red;
        static Color _green;
        static Color _blue;
        static Color _cyan;
        static Color _magenta;
        static Color _yellow;
        static Color _black;
        static Color _transparent;
        // ... more standard color here
    };

}

#endif // COLOR_H_
