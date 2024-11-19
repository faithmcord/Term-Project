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

void fill(Inventory &inventory) {
    for (int i = 1; i <= 5; i++) {
        std::string name = "Test " + std::to_string(i);
        inventory.createProduct(name, 12.34, 50);
    }
}

TEST_F(InventoryTest, Constructor) {
    EXPECT_NE(inventory, nullptr);
}

TEST_F(InventoryTest, newProduct) {
    //SUCCESSFULLY PLACE SOMETHING INTO THE INVENTORY

    // inventory -> createProduct("TEST TITLE", 12.34, 9999);
    fill(*inventory);

    testing::internal::CaptureStdout();
    inventory->displayAll();
    std::string output = testing::internal::GetCapturedStdout();

    // Ensure something prints
    EXPECT_NE(output, "");

    // REJECT IMPOSSIBLE PRODUCTS
    EXPECT_THROW(inventory -> createProduct("INVALID PRODUCT", -1, 0);, std::invalid_argument);
    EXPECT_THROW(inventory -> createProduct("", 12.34, 9999);, std::invalid_argument);
    EXPECT_THROW(inventory -> createProduct("INVALID PRODUCT", 12.34, -1);, std::invalid_argument);
}

TEST_F(InventoryTest, removeProduct) {
    Product *product = new Product("TEST TITLE", 12.34, 9999); // NOLINT(*-use-auto)
    inventory->addNew(*product);

    testing::internal::CaptureStdout();
    inventory->displayAll();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output, "");

    std::string prodID = product->getID();
    int result = inventory->remove(prodID);

    testing::internal::CaptureStdout();
    inventory->displayAll();
    output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(result, 0);
    EXPECT_EQ(output, "NO ENTRIES EXIST\n");

    result = inventory->remove(prodID);
    EXPECT_EQ(result, -1);

    delete product;
}


TEST_F(InventoryTest, save) {
    // Clear file
    std::fstream file;
    // char c;
    file.open(DEFAULT_INVENTORY_SAVE_PATH, std::ios::in);
    file.close();

    //Fill the savefile
    fill(*inventory);
    inventory->save();

    // Debug log
    // file.open(DEFAULT_INVENTORY_SAVE_PATH);
    // std::cout<<DEFAULT_INVENTORY_SAVE_PATH<<'\n';
    // while (file.get(c)) {
    //     std::cout << c;
    // }
    // file.close();

    // assertions
    EXPECT_FALSE(inventory -> empty());
    EXPECT_TRUE(Utilities::doesFileExist(DEFAULT_INVENTORY_SAVE_PATH));
}

TEST_F(InventoryTest, load) {
    // Clear file
    std::fstream file;
    // char c;
    file.open(DEFAULT_INVENTORY_SAVE_PATH, std::ios::in);
    file.close();

    //Fill the savefile
    fill(*inventory);
    inventory->save();

    // Inventory is not empty
    EXPECT_FALSE(inventory -> empty());

    // save contents to file and clear data
    inventory->save();
    inventory->clear();

    // Inventory is empty
    EXPECT_TRUE(inventory -> empty());

    // create new inventory from save data
    delete inventory;
    inventory = new Inventory(DEFAULT_INVENTORY_SAVE_PATH);
    inventory->load();

    // Debug
    // inventory -> displayAll();

    // Inventory is not empty
    EXPECT_FALSE(inventory -> empty());
}
