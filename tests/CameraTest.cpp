#include <gtest/gtest.h>
#include "Camera.hpp"
#include "Exceptions/InvalidSizeException.hpp"

TEST(CameraTest, IsCameraCreated) {
    std::string name = "cam1";

    // 1. Create a camera with valid input values
    auto cam = spic::Camera(name, "tag1", spic::Color::White(), 1, 1);

    // 2. Assert that it has been created with the correct name
    ASSERT_TRUE(cam.GetName() == name);
}

TEST(CameraTest, CameraHasCorrectBoundries) {
    std::string name = "cam";

    // 1. Create a camera with invalid input values (aspectWidth and aspectHeight should be > 0)
    // 2. Assert that an InvalidSizeException is thrown

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

TEST(CameraTest, CameraZoomHasCorrectBoundries) {
    std::string name = "cam";

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

