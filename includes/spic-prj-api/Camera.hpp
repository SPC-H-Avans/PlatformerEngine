#ifndef CAMERA_H_
#define CAMERA_H_

#include "GameObject.hpp"
#include "Color.hpp"

namespace spic {

    /**
     * @brief Class representing a point of view towards the game scene.
     * @spicapi
     */
    class Camera : public GameObject {
    public:
        Camera(const std::string &name, const std::string &tag, spic::Color backgroundColor,
               double aspectWidth, double aspectHeight);
        void Zoom(double aspectWidth, double aspectHeight);

        double GetAspectWidth();
        double GetAspectHeight();
    private:
        Color _backgroundColor;
        double _aspectWidth;
        double _aspectHeight;
    };

}  // namespace spic

#endif // CAMERA_H_
