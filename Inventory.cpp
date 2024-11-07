/**********************
*
* File Name:    Inventory.cpp
* Author(s):    Xander Palermo <ajp2s@missouristate.edu>
* Description:
*
* Course:      CSC 455 - Software Quality Assurance
* Instructor:  Mohammed Belkhouche
* Project:     Term Project
* Date:        8 November 2024
*
***********************/

#include <Inventory.h>
#include <random>

//GLOBAL VARIABLES
const string DEFAULT_SAVE_PATH = "products.txt";
const string DEFAULT_TRANSACTION_LOG_PATH = "transactions.txt";

Inventory::Inventory(const string &loadFile) : Database<Product> (loadFile) {
    savePath = loadFile;
    transactionLogPath = DEFAULT_TRANSACTION_LOG_PATH;
}

std::string Inventory::generateProductID() {
    // Init rand num generator to create ID
    std::random_device random_device;
    std::mt19937 gen(random_device());
    std::uniform_int_distribution<> dis(10000,99999);

    int generatedNum = dis(gen);

    // Concat new product ID
    std::string classifierID = "Prod";
    std::string numberID = std::to_string(generatedNum);
    std::string newID = classifierID + numberID;

    return newID;
}


int Inventory::createProduct(const std::string &productName, double price, int initialStock) {
    //TODO:
    //isProductNameValid
        //return -1
    //isProductPrice Valid
        //return -2
    bool validInitialStock = Product::isValidQuantity(initialStock);
    if (!validInitialStock) {
        return -3;
    }
    else {
        // do nothing
    }
    std::string productID;
    while (Inventory::doesExist(productID) || productID.empty()) {
        productID = generateProductID();
    }
    Product newProduct = Product(productID, productName, price, initialStock);
    Inventory::addNew(newProduct);
    return 0;
}

int Inventory::isEnoughInInventory(const std::string &productID) {
    // locate product being queried
    auto index = container.find(productID);
    if (index == container.end()) { // product does not exist
        return -1;
    }
    else {                          // product exists; return amount available
        int amountInStock;
        amountInStock = index -> second.getQuantity();
        return amountInStock;
    }
}

int Inventory::makePurchase(int productsPurchased, int productID[], int amounts[]) {
    return -999;
}

int Inventory::redeemRewards() {
    return -999;
}
