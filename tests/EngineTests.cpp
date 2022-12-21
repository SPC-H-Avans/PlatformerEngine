#include <gtest/gtest.h>
#include "Engine/Engine.hpp"
#include "Builder/SceneBuilder.hpp"

class EgnineTests : public ::testing::Test {
    void SetUp() override {
        platformer_engine::Engine &engine = platformer_engine::Engine::GetInstance();
        engine.Init(1000, 1000, "Mario Game", spic::Color::Cyan(), false);
        platformer_engine::SceneBuilder builder = platformer_engine::SceneBuilder("levelEgnineTests");
        engine.AddScene(builder.GetScene());
        engine.QueueActiveScene("levelEgnineTests");
    }

};
