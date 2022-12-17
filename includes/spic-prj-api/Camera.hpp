#ifndef CAMERA_H_
#define CAMERA_H_

#include <optional>
#include "GameObject.hpp"
#include "Color.hpp"
#include <boost/serialization/access.hpp>
#include <boost/serialization/export.hpp>

namespace spic {

    /**
     * @brief Class representing a point of view towards the game scene.
     * @spicapi
     */
    class Camera : public GameObject {
    public:

        template<class Archive>
        void serialize(Archive &ar, unsigned int version) {
            ar & boost::serialization::base_object<GameObject, Camera>(*this);
            boost::serialization::void_cast_register<Camera, GameObject>();
            ar & _backgroundColor;
            ar & _aspectHeight;
            ar & _aspectWidth;
        }

        Camera(const std::string &name = "Null");

        Camera(const std::string &name, const std::string &tag, spic::Color backgroundColor,
               double aspectWidth, double aspectHeight);

        void Zoom(double aspectWidth, double aspectHeight);

        double GetAspectWidth();

        double GetAspectHeight();

        /**
         * @brief Let the camera follow a game object
         * @param gameObject the game object you want to follow
         */
        void SetTarget(const GameObject &target) {
            _target = target;
        }

        Transform GetTarget(int screenWidth, int screenHeight) {
            if (_target.has_value()) {
                Transform transform = _target->GetTransform();

                transform.position.x = transform.position.x - (screenWidth / 2);
                transform.position.y = transform.position.y - (screenHeight / 2);

                if (transform.position.x < 0) {
                    transform.position.x = 0;
                }
                if (transform.position.y < 0) {
                    transform.position.y = 0;
                }
                if (transform.position.x > (2 * screenWidth - _aspectWidth)) {
                    transform.position.x = (2 * screenWidth - _aspectWidth);
                }
                if (transform.position.y > (screenHeight - _aspectHeight)) {
                    transform.position.y = (screenHeight - _aspectHeight);
                }

                return transform;
            }
            try {
                return GetTransform();
            } catch (std::exception &e) {
                return {};
            }
        }

    private:
        Color _backgroundColor;
        double _aspectWidth;
        double _aspectHeight;
        std::optional<GameObject> _target;
    };

}  // namespace spic

#endif // CAMERA_H_
