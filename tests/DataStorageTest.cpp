#include <gtest/gtest.h>
#include <Storage/DataStorageManager.hpp>
#include <GameObject.hpp>

class DataStorageTest : public ::testing::Test {

};

TEST_F(DataStorageTest, CanSaveLoadData) {
    platformer_engine::DataStorageManager _dataManager {};

    _dataManager.SaveData<spic::GameObject>("A", spic::GameObject("Test"));
    ASSERT_EQ(_dataManager.LoadData<spic::GameObject>("A")->GetName(), "Test") << "The loaded object is not equal to the saved object";
}

TEST_F(DataStorageTest, CanClearData) {
    platformer_engine::DataStorageManager _dataManager {};

    _dataManager.SaveData<spic::GameObject>("A", spic::GameObject("Test"));
    _dataManager.ClearStorage();
    ASSERT_EQ(_dataManager.LoadData<spic::GameObject>("A"), std::nullopt) << "The storage has been cleared, the saved object has not been found afterwards";
}