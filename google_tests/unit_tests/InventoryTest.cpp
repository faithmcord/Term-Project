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

    Inventory *inventory = nullptr;
};

TEST_F(InventoryTest, Constructor) {
    EXPECT_NE(inventory, nullptr);
}

TEST_F(InventoryTest, newProduct) {

    //SUCCESSFULLY PLACE SOMETHING INTO THE INVENTORY
    inventory -> createProduct("TEST TITLE", 12.34, 9999);

    testing::internal::CaptureStdout();
    inventory -> displayAll();
    std::string output = testing::internal::GetCapturedStdout();

    // Ensure something prints
    EXPECT_NE(output,"");

    // REJECT IMPOSSIBLE PRODUCTS
    EXPECT_THROW(inventory -> createProduct("INVALID PRODUCT", -1, 0); , std::invalid_argument);
    EXPECT_THROW(inventory -> createProduct("", 12.34, 9999);, std::invalid_argument);
    EXPECT_THROW(inventory -> createProduct("INVALID PRODUCT", 12.34, -1);, std::invalid_argument);

}

TEST_F(InventoryTest, removeProduct) {
    Product *product = new Product("TEST TITLE", 12.34, 9999);
    inventory -> addNew(*product);

    testing::internal::CaptureStdout();
    inventory -> displayAll();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output, "");

    std::string prodID = product -> getID();
    int result = inventory -> remove(prodID);

    testing::internal::CaptureStdout();
    inventory -> displayAll();
    output = testing::internal::GetCapturedStdout();

    EXPECT_EQ( result, 0);
    EXPECT_EQ( output, "NO ENTRIES EXIST\n" );

    result = inventory -> remove(prodID);
    EXPECT_EQ(result, -1);

    delete product;
}