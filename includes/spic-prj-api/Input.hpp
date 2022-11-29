#ifndef INPUT_H_
#define INPUT_H_

#include "Point.hpp"
#include <string>
#include "Facade/InputFacade.hpp"

class InputFacade;

namespace spic {

    /**
     * @brief Some convenient input functions.
     */
    namespace Input {

        /**
         * @brief Is any key or mouse button currently held down? (Read Only)
         * @spicapi
         */
        bool AnyKey();

        /**
         * @brief Returns true the first frame the user hits any key or mouse button. (Read Only)
         * @spicapi
         */
        bool AnyKeyDown();

        /**
         * @brief The current mouse position in pixel coordinates. (Read Only)
         * @spicapi
         */
        Point MousePosition();

        /**
         * @brief Returns the value of the virtual axis identified by axisName.
         * @spicapi
         */
        double GetAxis();

        /**
         * @brief Returns true while the user holds down the key identified by keycode.
         * @spicapi
         */
        bool GetKey(KeyCode key);

        /**
         * @brief Returns true during the frame the user starts pressing down the key identified by keycode.
         * @spicapi
         */
        bool GetKeyDown(KeyCode key);

        /**
         * @brief Returns true during the frame the user releases the key identified by keycode.
         * @spicapi
         */
        bool GetKeyUp(KeyCode key);

        /**
         * @brief Returns whether the given mouse button is held down.
         * @spicapi
         */
        bool GetMouseButton(MouseButton which);

        /**
         * @brief Returns true during the frame the user pressed the given mouse button.
         * @spicapi
         */
        bool GetMouseButtonDown(MouseButton which);

        /**
         * @brief Returns true during the frame the user releases the given mouse button.
         * @spicapi
         */
        bool GetMouseButtonUp(MouseButton which);

        /**
 * @brief Listen of key input
 * @return Vector of events
 * @platformerengine
 */
        auto ListenForInput() -> std::vector<EventsEnum>;

    }

}  // namespace spic

#endif // INPUT_H_
