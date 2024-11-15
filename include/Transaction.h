/**********************
*
* File Name:    Transactions.h
* Author(s):
* Description:  A container object that manages and preserves all loaded customers in memory
*
* Course:      CSC 455 - Software Quality Assurance
* Instructor:  Mohammed Belkhouche
* Project:     Term Project
* Date:        8 November 2024
*
***********************/

#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "Inventory.h"
#include "Clientele.h"
#include "Rewards.h"
#include "Utilities.h"

const std::string DEFAULT_REWARDS_CONFIG_PATH = "./resources/config.txt"; //store $ -> point conversion
constexpr int MAX_CART_SIZE = 20;

struct item {
    int productID;
    int amount;
};

struct ShoppingCart {
    item productsInCart[MAX_CART_SIZE];
};

class Transaction {
    static int logTransaction( const std::string &savePath, const std::string &custID, const std::string &prodID, const double &price, int pointsEarned );
    static int applyRewards( double price, const std::string &custID, Clientele &clientele );

    static int transactionCount;
    static double dollarsIn;
    static int pointsOut;
  public:

    static void loadConfig (const std::string &configPath);

    static void saveConfig (const std::string &configPath);

    static void setRewardsConversion (double in, int out);

    template <typename Clientele, typename Inventory>
    static int makeTransaction(const Clientele& clientele, const Inventory& inventory, const std::string &custID);

    template <typename Clientele, typename Rewards>
    static int redeemRewards(const Clientele& clientele, const Rewards& rewards, const std::string &custID);

  };

inline int Transaction::logTransaction (const std::string &savePath, const std::string &custID, const std::string &prodID, const double &price, const int pointsEarned) {
    std::fstream file;
    file.open(savePath, std::ios::app);
    file << "Transaction " << transactionCount << ":\n";
    file << "UserID: " << custID << '\n'
        << "Product ID: " << prodID << '\n'
        << "Price: " << price << '\n'
        << "Rewards gained: " << pointsEarned << '\n';
    ++transactionCount;
    file.close();
    return 0;
}

inline int Transaction::applyRewards(double price, const std::string &custID, Clientele &clientele) {
    double points = price / dollarsIn;
    points = floor(points);
    points *= pointsOut;
    clientele.updateCustomerRewards(custID,static_cast<int>(points));
    return static_cast<int>(points);
}

inline void Transaction::loadConfig(const std::string &configPath) {
    bool fileExists = Utilities::doesFileExist(configPath);
    if (!fileExists) {
        dollarsIn = 5;
        pointsOut = 1;
        transactionCount = 1;
        return;
    }
    else {
        /* Do nothing */
    }

    std::ifstream file;
    file.open(configPath);
    std::string buffer;
    std::getline(file, buffer);
    dollarsIn = std::stod(buffer);
    std::getline(file, buffer);
    pointsOut = std::stoi(buffer);
    std::getline(file, buffer);
    transactionCount = std::stoi(buffer);
    file.close();
}

inline void Transaction::saveConfig(const std::string &configPath) {
    std::fstream file;
    file.open(configPath,std::ios::out);
    file << dollarsIn << '\n' << pointsOut << '\n' << transactionCount;
    file.close();
}

inline void Transaction::setRewardsConversion(const double in, const int out) {
    dollarsIn = in;
    pointsOut = out;
}

template <typename Clientele, typename Inventory>
int Transaction::makeTransaction(const Clientele& clientele, const Inventory& inventory, const std::string &custID) {
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
    inventory.updateInventory(productID, negQuantity);

    // Save Transaction to txt file & Apply rewards to customer
    double price = inventory.getPrice(productID);
    int pointsEarned = applyRewards(price,custID,clientele);
    logTransaction(DEFAULT_TRANSACTION_LOG_PATH, custID, productID, price, pointsEarned);


    // Final Statement
    std::cout << "Transaction successful!\n";
    return 0;
}

template <typename Clientele, typename Rewards>
int Transaction::redeemRewards(const Clientele& clientele, const Rewards& rewards, const std::string &custID) {
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
    int amount = rewards.getRewardValue(rewardID) * -1;
    if (clientele.updateCustomerRewards(custID, amount) != 0) {
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


#endif //TRANSACTION_H
