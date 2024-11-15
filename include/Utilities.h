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

static int transactionCount = 0;

class Utilities {

    static int logTransaction(  );

public:

    /***
    * @brief updates clientele and inventory atomically
    */
    template <typename Clientele, typename Inventory>
    static int makeTransaction(const Clientele& clientele, const Inventory& inventory, int custID);

    template <typename Clientele, typename Rewards>
    int Utilities::redeemRewards(const Clientele& clientele, const Rewards& rewards, int custID);

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
    int negQuantity;
    negQuantity = -quantity;
    inventory::updateInventory(productID, negQuantity);

    // Save Transaction to txt file
    //
    //
    //

    // Final Statement
    std::cout << "Transaction successful!\n";
    return 0;
}

template <typename Clientele, typename Rewards>
int Utilities::redeemRewards(const Clientele& clientele, const Rewards& rewards, int custID) {
    // Check if the client exists in the database
    if (!clientele.doesExist(custID)) {
        std::cout << "Client does not exist.\n";
        return -1;
    }

    // Display all available products using the Database's displayAll function
    std::cout << "Available products:\n";
    rewards.displayAll();

    // Prompt user to choose a product ID
    std::string rewardID;
    std::cout << "Enter the ID of the reward you wish to redeem: ";
    std::cin >> rewardID;

    // Verify reward exists
    if (!rewards.doesExist(rewardID)) {
        std::cout << "Reward selection does not exist.\n";
        return -1;
    }

    // Retrieve the product's cost in rewards points
    int rewardValue = rewards.getRewardValue(rewardID); // Hypothetical function to fetch reward point cost
    if (rewardValue <= 0) {
        std::cout << "Failed to retrieve product cost.\n";
        return -1;
    }

    // Get the customer's current rewards points
    int customerRewards = clientele.getCustomerRewards(custID);
    if (customerRewards < 0) {
        std::cout << "Failed to retrieve customer rewards points.\n";
        return -1;
    }

    // Check if the customer has enough rewards points
    if (customerRewards < rewardValue) {
        std::cout << "You do not have enough rewards points to redeem this product.\n";
        return -1;
    }

    // Deduct rewards points
    if (clientele.updateCustomerRewards(custID, -productCost) != 0) {
        std::cout << "Failed to update customer rewards points.\n";
        return -1;
    }

    // Save Transaction to txt file NEEDS to be in less than 3 lines to stay in requirements
    //
    //
    //

    // Final Statement
    std::cout << "Transaction successful!\n";
    return 0;
}


inline bool Utilities::doesFileExist(const std::string& file) {
    std::fstream fs;
    fs.open(file, std::ios::in);
    if (fs.is_open()) {
        fs.close();
        return true;
    } else
        return false;
}

#endif //UTILITIES_H
