/**********************
*
* File Name:    Utilities.h
* Author(s):    Xander Palermo <ajp2s@missouristate.edu>
* Description:  A container object that manages and preserves all loaded customers in memory
*
* Course:      CSC 455 - Software Quality Assurance
* Instructor:  Mohammed Belkhouche
* Project:     Term Project
* Date:        8 November 2024
*
***********************/

#ifndef UTILITIES_H
#define UTILITIES_H

#include <fstream>

const std::string REWARDS_CONFIG_PATH = "config.txt"; //store $ -> point conversion
constexpr int MAX_CART_SIZE = 20;

struct item {
    int productID;
    int amount;
};

struct ShoppingCart {
    item productsInCart[MAX_CART_SIZE];
};

class Utilities {
public:

    /***
    * @brief updates clientele and inventory atomically
    */
    template <typename Clientele, typename Inventory>
    static int makeTransaction(const Clientele& clientele, const Inventory& inventory, int custID);

    static bool doesFileExist(const std::string& file);

};

    template <typename Clientele, typename Inventory>
    int Utilities::makeTransaction(const Clientele& clientele, const Inventory& inventory, int custID) {
        // Check if the client exists in the database
        if (!clientele.doesExist(custID)) {
            std::cout << "Client does not exist.\n";
            return -1;
        }

        // Display all available products using the Database's displayAll function
        std::cout << "Available products:\n";
        inventory.displayAll();

        // Prompt user to choose a product ID
        std::string productID;
        std::cout << "Enter the ID of the product you wish to purchase: ";
        std::cin >> productID;

        //Check if product exists in the database
        if (!inventory.doesExist(productID)) {
            std::cout << "Product does not exist.\n";
            return -1;
        }

        // Ask for the quantity to purchase
        int quantity;
        std::cout << "Enter the quantity for product ID " << productID << ": ";
        std::cin >> quantity;
        if (quantity <= 0) {
            std::cout << "Invalid quantity.\n";
            return -1;
        }

        // Check if there is enough stock for the requested quantity
        if (!inventory.isEnoughInStock(productID, quantity)) {
            std::cout << "Insufficient stock for product ID " << productID << ".\n";
            return -1;
        }

        // Update Stock
        //
        //
        //

        // Save Transaction to txt file
        //
        //
        //

        // Final Statement
        std::cout << "Transaction successful!\n";
        return 0;
    }


// bool Utilities::doesFileExist(const std::string& file) {
//     std::fstream fs;
//     fs.open(file, std::ios::in);
//     if (fs.is_open()) {
//         fs.close();
//         return true;
//     } else
//         return false;
// }

#endif //UTILITIES_H
