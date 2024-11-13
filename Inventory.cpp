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

#include "Inventory.h"
#include <random>

//GLOBAL VARIABLES
const std::string DEFAULT_INVENTORY_SAVE_PATH = "products.txt";
const std::string DEFAULT_TRANSACTION_LOG_PATH = "transactions.txt";

Inventory::Inventory(const std::string &loadFile) : Database<Product> (loadFile) {
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


std::string Inventory::createProduct(const std::string &productName, double price, int initialStock) {
    //TODO:
    //isProductNameValid
        //return -1
    //isProductPrice Valid
        //return -2
    // bool validInitialStock = Product::isValidQuantity(initialStock);
    // if (!validInitialStock) {
    //     return -3;
    // }
    // else {
    //     // do nothing
    // }
    // std::string productID;
    // while (Inventory::doesExist(productID) || productID.empty()) {
    //     productID = generateProductID();
    // }
    // const Product newProduct = Product(productID, productName, price, initialStock);
    // Inventory::addNew(newProduct);

    const Product newProduct = Product(productName, price, initialStock);
    this -> addNew(newProduct);
    std::string prodID = newProduct.getID();
    return prodID;
}

int Inventory::isEnoughInInventory(const std::string &productID) {
    // locate product being queried
    const auto index = container.find(productID);
    if (index == container.end()) { // product does not exist
        return -1;
    }
    else {                          // product exists; return amount available
        const int amountInStock = index->second.getQuantity();
        return amountInStock;
    }
}

void Inventory::save() {
    // const bool fileExists = Utilities::doesFileExist(savePath);
    std::fstream saveFile;
    // if (fileExists) {
    //     std::remove(savePath.c_str());
    //     saveFile.open(savePath, std::ios::out);
    // } else {
    //     saveFile.open(savePath, std::ios::out);
    // }
    saveFile.open(savePath, std::ios::out);
    int indexNumber = 0;
    auto indexPointer = container.begin();
    const auto end = container.end();
    while (indexPointer != end) {
        std::string output = "Customer " + to_string(++indexNumber) + '\n';
        output += indexPointer->second.toString();
        saveFile << output << '\n';
        ++indexPointer;
    }
    saveFile.close();
}

void Inventory::load() {
    bool fileExists = Utilities::doesFileExist(savePath);
    if (!fileExists) {
        // nothing to load
        return;
    }
    else {
        /* Do nothing */
    }

    // Init
    std::ifstream saveFile;
    saveFile.open(savePath);
    std::string _line , nameString, priceString, quantityString;
    std::regex pattern(" [^\\n]*\\n");

    // Colors text Red lol
    std::string errorColorMod = "\033[1;31m";
    std::string defaultColorMod = "\033[1;39m";

    // Until Empty Line
    while (getline(saveFile, _line)) {
        if (getline(saveFile, _line) &&
            getline(saveFile, nameString) &&
            getline(saveFile, priceString) &&
            getline(saveFile, quantityString) ) {

            std::regex_search(priceString, priceString, pattern);
            std::regex_search(quantityString, quantityString, pattern);
            std::regex_search(nameString, nameString, pattern);

            try {
                this -> createProduct(nameString, stod(priceString), stoi(quantityString));
            } catch (std::invalid_argument &invalid_argument) {
                std::cout << errorColorMod << "Load file problem encountered. All products might not be loaded. Please review Products.txt\n"
                             "Reference:\t" << invalid_argument.what() << defaultColorMod << '\n';
                continue;
            } catch (std::out_of_range &out_of_range) {
                std::cout << errorColorMod << "Load file problem encountered. All products might not be loaded. Please review Products.txt\n"
                             "Reference:\t" << out_of_range.what() << defaultColorMod << '\n';
                continue;
            }
        } else {
            std::cout << errorColorMod << "Load file problem encountered. All Products might not be loaded. Please review Products.txt\n"
                                          "Reference:\t Last product in Products.txt missing information!!" << defaultColorMod << '\n';
            break;
        }
    }
    saveFile.close();
}



int Inventory::makePurchase(int productsPurchased, int productID[], int amounts[]) {
    return -999;
}

int Inventory::redeemRewards() {
    return -999;
}
