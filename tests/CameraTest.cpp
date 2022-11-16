#include <gtest/gtest.h>
#include "Camera.hpp"
#include "Exceptions/InvalidSizeException.hpp"


/**
 * @brief Tests if Camera objects are created with their correct name;
 */

//TODO: fix test with new construction
TEST(CameraTest, IsCameraCorrectlyCreated) {
    std::string name = "Cam_IsCameraCorrectlyCreated";
    int aspectWidth = 1;
    int aspectHeight = 2;

    // 1. Create a camera with valid input values
    auto cam = spic::Camera(name, "tag1", spic::Color::White(), aspectWidth, aspectHeight);

    // 2. Assert that the camera can be found in GameObjects
    auto gameObjPtr = spic::GameObject::Find(name);
    ASSERT_TRUE(gameObjPtr != nullptr);

    // 3. Assert that the camera GameObject can be cast to a Camera object
    auto camObjPtr = std::static_pointer_cast<spic::Camera>(gameObjPtr);
    ASSERT_TRUE(camObjPtr != nullptr);

    // 4. Assert that the input values (aspectWidth and aspectHeight are still available and correct)
    ASSERT_TRUE(camObjPtr->GetAspectHeight() == aspectHeight);
    ASSERT_TRUE(camObjPtr->GetAspectWidth() == aspectWidth);
}

/**
 * @brief Tests if the correct errors are thrown when creating Camera's with illegal boundries;
 */
TEST(CameraTest, CameraHasCorrectBoundries) {
    std::string name = "Cam_CameraHasCorrectBoundries";

    // 1. Create camera's with invalid input values (aspectWidth and aspectHeight should be > 0)
    // 2. Assert that InvalidSizeExceptions are thrown

    ASSERT_THROW(
            spic::Camera(name, name, spic::Color::White(), 0, 1),
            spic::InvalidSizeException)
            << "A camera with aspectWidth of 0 should throw an InvalidSizeException";
    ASSERT_THROW(
            spic::Camera(name, name, spic::Color::White(), -1, 1),
            spic::InvalidSizeException)
            << "A camera with aspectWidth of -1 should throw an InvalidSizeException";
    ASSERT_THROW(
            spic::Camera(name, name, spic::Color::White(), 1, 0),
            spic::InvalidSizeException)
            << "A camera with aspectHeight of 0 should throw an InvalidSizeException";
    ASSERT_THROW(
            spic::Camera(name, name, spic::Color::White(), 1, -1),
            spic::InvalidSizeException)
            << "A camera with aspectHeight of -1 should throw an InvalidSizeException";
}

/**
 * @brief Tests if the correct errors are thrown when zooming Camera's with illegal boundries;
 */
TEST(CameraTest, CameraZoomHasCorrectBoundries) {
    std::string name = "Cam_CameraZoomHasCorrectBoundries";

    // 1. Create a camera with valid input values (aspectWidth and aspectHeight should be > 0)
    auto cam = spic::Camera(name, name, spic::Color::White(), 100, 100);

    // 2. Assert that InvalidSizeException is thrown when the camera zooms to incorrect positions
    ASSERT_THROW(cam.Zoom(0, 1), spic::InvalidSizeException)
            << "A camera zoom with aspectWidth of 0 should throw an InvalidSizeException";
    ASSERT_THROW(cam.Zoom(-1, 1), spic::InvalidSizeException)
            << "A camera zoom with aspectWidth of -1 should throw an InvalidSizeException";
    ASSERT_THROW(cam.Zoom(1, 0), spic::InvalidSizeException)
            << "A camera zoom with aspectHeight of 0 should throw an InvalidSizeException";
    ASSERT_THROW(cam.Zoom(1, -1), spic::InvalidSizeException)
            << "A camera zoom with aspectHeight of -1 should throw an InvalidSizeException";

    ASSERT_NO_THROW(cam.Zoom(1, 1))
            << "A Camera zoom with aspectWidth = 1 and aspectHeight = 1 should not throw an error";

}

