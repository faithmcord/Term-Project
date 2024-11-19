/**********************
*
* File Name:    Inventory.h
* Author(s):	Xander Palermo <ajp2s@missouristate.edu>
* Description:  A container object that manages and preserves all loaded Products in memory
*
* Course:      CSC 455 - Software Quality Assurance
* Instructor:  Mohammed Belkhouche
* Project:     Term Project
* Date:        8 November 2024
*
***********************/

#ifndef INVENTORY_H
#define INVENTORY_H

#include "Product.h"
#include <random>

#include "Database.h"


//GLOBAL VARIABLES
const std::string DEFAULT_INVENTORY_SAVE_PATH = "products.txt";
const std::string DEFAULT_TRANSACTION_LOG_PATH = "transactions.txt";

/**
 * @class Inventory
 * @brief a dictionary of all customers of the store indexed by their customer ID
 */
class Inventory : public Database<Product> {
private:
    /**
     * @brief the directory of the transaction log file
     */
    std::string transactionLogPath;

public:
    explicit Inventory(const std::string &loadFile);

    /**
     * @brief Creates a new product and stores it into the dictionary
     *
     * @pre productName < 30 characters long
     * @pre price is a positive amount
     * @pre price contains only 2 decimal places
     *
     * @param productName   a description of the product
     * @param price         the cost to purchase the product
     * @param initialStock  the number of product currently possessed in the inventory
     *
     * @return the product ID of the newly added product
     *
     * @throws std::invalid_argument if validation fails
     */
    std::string createProduct(const std::string &productName, double price, int initialStock);

    /**
     * Checks if there is enough of a product in the inventory to fulfil a request of a specified amount
     *
     * Performs a greater than or equal to operation
     *
     * @param productID identifying ID numbers of the product to be checked
     * @param quantity the minimum amount being referenced to
     * @return if the amount of product is greater than quantity, returns true; otherwise false
     */
    bool isEnoughInInventory(const std::string &productID, int quantity);

    /**
     * @brief checks for how much stock of a product is currently in possession
     *
     * @param productID identifying ID numbers of the product to be checked
     *
     * @return amount currently in stock
     * @return -1 if invalid productID
     */
    bool isEnoughInInventory(const std::string &productID);

    /**
     * Will change the amount of product in inventory by adding or subtracting a stated amount
     *
     * if the amount is positive, it will be added to inventory amount (simulating a restock);
     * if the amount is negative, it will be subtracted from the inventory amount (simulating a purchase)
     *
     * @param productID identifying ID number of the product being edited
     * @param amount the amount being added or subtracted from inventory
     * @return
     */
    int updateInventory(const std::string &productID, int amount);

    /**
     * Attempts to find a specified product inventory and return its set price
     *
     * @pre product exists
     *
     * @param productID identifying ID numbers of the product to be checked
     * @return the price of the product being checked; if the product does not exist, returns -1.0
     */
    double getPrice(const std::string &productID);

    /**
     * Clears the inventory object and resets the product ID maker
     */
    void clear() override;

    /**
     * Saves the current state of the inventory to the savePath set upon creation of the object
     */
    void save() override;

    /**
     * Loads the previous state of an inventory from the savePath set upon creation of the object
     */
    void load() override;
};


inline Inventory::Inventory(const std::string &loadFile) : Database<Product>(loadFile) {
    savePath = loadFile;
    transactionLogPath = DEFAULT_TRANSACTION_LOG_PATH;
}

inline std::string Inventory::createProduct(const std::string &productName, double price, int initialStock) {
    const Product newProduct = Product(productName, price, initialStock);
    this->addNew(newProduct);
    std::string prodID = newProduct.getID();
    return prodID;
}

inline bool Inventory::isEnoughInInventory(const std::string &productID, int quantity) {
    // locate product being queried
    const auto index = container.find(productID);
    if (index == container.end()) {
        // product does not exist
        return false;
    } else {
        // product exists; return amount available
        const int amountInStock = index->second.getQuantity();
        if (amountInStock >= quantity) {
            return true;
        } else {
            return false;
        }
    }
}

inline int Inventory::updateInventory(const std::string &productID, int amount) {
    // locate the product being queried
    const auto index = container.find(productID);
    if (index == container.end()) {
        // product does not exist
        return -1;
    } else {
        if (amount > 0) {
            // add to inventory amount
            index->second.addStock(amount);
        } else if (amount < 0) {
            // subtract from inventory amount
            amount *= -1;
            index->second.removeStock(amount);
        } else {
            // quantity == 0 -> do nothing
        }
        return 0;
    }
}

inline double Inventory::getPrice(const std::string &productID) {
    // locate the product being queried
    const auto index = container.find(productID);
    if (index == container.end()) {
        // product does not exist
        return -1.0;
    } else {
        // product exists; return price
        const double price = index->second.getPrice();
        return price;
    }
}

inline void Inventory::clear() {
    Product::clear();
    container.clear();
}

inline void Inventory::save() {
    // open file
    std::fstream saveFile;
    saveFile.open(savePath, std::ios::out);

    // initialize values
    int indexNumber = 0;
    auto indexPointer = container.begin();
    const auto end = container.end();

    //for each product in container -> add to .txt file
    while (indexPointer != end) {
        saveFile << "Product " << ++indexNumber << ":\n";
        std::string output;
        output += indexPointer->second.toString();
        saveFile << output << '\n';
        ++indexPointer;
    }
    saveFile.close();
}

inline void Inventory::load() {
    // Check if file exists to load from
    bool fileExists = Utilities::doesFileExist(savePath);
    if (!fileExists) {
        // nothing to load
        return;
    } else {
        /* Do nothing */
    }

    // Init
    std::ifstream saveFile;
    saveFile.open(savePath);

    // Colors text Red lol
    std::string errorColorMod = "\033[1;31m";
    std::string defaultColorMod = "\033[1;39m";

    // For every item described in the .txt file
    while (true) {
        // Initialize variables
        std::string line, nameString, priceString, quantityString;

        //Check if there is another product
        std::getline(saveFile, line);
        if (line == "\0") {
            break;
        } else {
            /* Do nothing */
        }
        std::getline(saveFile, line); // describes ID, which is created in real-time

        // Grab important data
        std::getline(saveFile, nameString);
        std::getline(saveFile, priceString);
        std::getline(saveFile, quantityString);

        // Remove metadata from fields and attempt to recreate product
        nameString.erase(0, 6);
        priceString.erase(0, 7);
        quantityString.erase(0, 10);

        // Catch if file has been corrupted
        try {
            this->createProduct(nameString, stod(priceString), stoi(quantityString));
        } catch (std::invalid_argument &invalid_argument) {
            // One or more of the attribute does not fit into input range
            continue;
        } catch (std::out_of_range &out_of_range) {
            // One or more of the attributes creates a integer/floating-point overflow
            continue;
        }
    }
    saveFile.close();
}

#endif //INVENTORY_H
