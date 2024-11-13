#include "gtest/gtest.h"
#include "include/Inventory.h"

class InventoryTest : public testing::Test {
protected:
    void SetUp() override {
        inventory = new Inventory(DEFAULT_INVENTORY_SAVE_PATH);
    }

    void TearDown() override {
        delete inventory;
    }

    Inventory *inventory;
};

TEST_F(InventoryTest, Constructor) {
    EXPECT_NE(inventory, nullptr);
}