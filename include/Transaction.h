/**********************
*
* File Name:    Transactions.h
* Author(s):    Faith Cordsiemon <fmc778s@missouristate.edu>
*               Xander Palermo <ajp2s@missouristate.edu>
* Description:  A utility class that handles performing atomic transactions between databases
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

const std::string DEFAULT_REWARDS_CONFIG_PATH = "./resources/config.txt"; //store $ -> point conversion and transactionCount
constexpr int MAX_CART_SIZE = 20;

struct item {
    int productID;
    int amount;
};

struct ShoppingCart {
    item productsInCart[MAX_CART_SIZE];
};

class Transaction {
private:
    /**
     * Logs a product purchase transaction information into a log file for record keeping
     *
     * The transaction ID is derived from a global variable saved in line 3 of the loaded config file
     *
     * The Transaction ID is shared between Products and Reward Transactions
     *
     * @pre a config file has been loaded
     *
     * @param savePath the location of the log file to be appended to
     * @param custID the ID of the customer initiating the transaction
     * @param prodID the ID of the product being purchased
     * @param price the total of the item being purchased
     * @param pointsEarned the number of points awarded to the customer upon finishing the transaction
     * @return 0 on success of logging
     */
    static int logTransaction( const std::string &savePath, const std::string &custID, const std::string &prodID, const double &price, int pointsEarned );

    /**
     * Logs a rewards use transaction into a log file for record keeping
     *
     * The transaction ID is derived from a global variable saved in line 3 of the loaded config file
     *
     * The Transaction ID is shared between Products and Reward Transactions
     *
     * @pre a config file has been loaded
     *
     * @param savePath the location of the log file to be appended to
     * @param custID the ID of the customer initiating the transaction
     * @param rewardID the ID of the reward being purchased
     * @param rewardsSpent the number of rewards points spent upon finishing the transaction
     * @return
     */
    static int logRewardsUse( const std::string &savePath, const std::string &custID, const std::string &rewardID, const int &rewardsSpent);

    /**
     * Accesses a specific customer in the clientele database and administers reward points to them
     * from a transaction of a specified price
     *
     * Conversion rate of price to points is defined in line 1 and 2 of the config file loaded
     * Can be overridden by calling setRewardsConversion() and permanently changed by saveConfig()
     *
     * @pre a config file has been loaded
     *
     * @param price the total of the purchase awarding rewards to the customer
     * @param custID the ID of the customer who made the transaction
     * @param clientele the database of customers that contains the information of the customer
     * @return  the number of rewards applied to the account that was calculated
     */
    static int applyRewards( double price, const std::string &custID, Clientele &clientele );

    /**
     * Ensures that the conversion rate from dollars:points is non-zero and non-negative
     *
     * @post if the conditions above are met, the conversion rate is reset to its default rate
     * @return true if the conversion rate is valid, otherwise false.
     */
    static bool validateConversionRate ();

    static const double DEFAULT_DOLLARS_IN;     /* Automatically set value of dollars into points for dollars if there is an issue with loading */
    static const int DEFAULT_POINTS_OUT;        /* Automatically set value of dollars into points for points if there is an issue with loading */

    static int transactionCount;    /* The ID value given to the next transaction to occur */
    static double dollarsIn;        /* a part of the dollars:point ratio, describes the dollar amount */
    static int pointsOut;           /* a part of the dollar:point ratio, describes the rewards amount */

public:
    /**
     * Loads a config file to set transactionCount, and the dollar:point conversion rate for the next session
     *
     * @pre a file exists
     *
     * @post if no config file could be found, loads values to default amounts
     *
     * @param configPath the path to the file that contains information regarding the prestated variables
     *
     * @return true if values were successfully loaded, false if values were set to default
     */
    static bool loadConfig (const std::string &configPath);

    /**
     * Saves values of transactionCount, and the dollar:point conversion rate from a previous session
     *
     * @post if a file already existed in that path, it will be replaced
     *
     * @param configPath the path to the file to save the updated config
     */
    static void saveConfig (const std::string &configPath);

    /**
     * Set the conversion rate of dollars to points
     *
     * Example (in = 2, out=3) the conversion rate will be for every 2 dollars spent
     *                              a customer will be rewarded with 3 points
     *
     * @pre the parameters are non-negative and non-zero for the conversion rate
     *
     * @param in how many dollars go into the ratio to points
     * @param out how many reward points come out of dollars spent
     * @return True if the provided arguments are a valid conversion, otherwise false
     */
    static bool setRewardsConversion (double in, int out);

    template <typename Clientele, typename Inventory>
    static int makeTransaction(Clientele& clientele,  Inventory& inventory, const std::string &custID);

    template <typename Clientele, typename Rewards>
    static int redeemRewards( Clientele& clientele,  Rewards& rewards, const std::string &custID);

  };

// Set Static Variables
const double Transaction::DEFAULT_DOLLARS_IN = 5.0;
const int Transaction::DEFAULT_POINTS_OUT = 1;

int Transaction::transactionCount = 1;
double Transaction::dollarsIn = DEFAULT_DOLLARS_IN;
int Transaction::pointsOut = DEFAULT_POINTS_OUT;

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

inline bool Transaction::validateConversionRate() {
    if (dollarsIn > 0 && pointsOut > 0) {
        return true;
    }
    else { // An incorrect value was passed
        // THIS IS TEMPORARY HANDLING
        dollarsIn = DEFAULT_DOLLARS_IN;
        pointsOut = DEFAULT_POINTS_OUT;
        return false;
    }
}


inline bool Transaction::loadConfig(const std::string &configPath) {
    bool fileExists = Utilities::doesFileExist(configPath);
    if (!fileExists) {
        dollarsIn = DEFAULT_DOLLARS_IN;
        pointsOut = DEFAULT_POINTS_OUT;
        transactionCount = 1;
        return false;
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
    return validateConversionRate();
}

inline void Transaction::saveConfig(const std::string &configPath) {
    std::fstream file;
    file.open(configPath,std::ios::out);
    file << dollarsIn << '\n' << pointsOut << '\n' << transactionCount;
    file.close();
}

inline bool Transaction::setRewardsConversion(const double in, const int out) {
    dollarsIn = in;
    pointsOut = out;
    return validateConversionRate();
}

template <typename Clientele, typename Inventory>
int Transaction::makeTransaction( Clientele& clientele, Inventory& inventory, const std::string &custID) {
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
    if (!inventory.isEnoughInInventory(productID, quantity)) {
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
int Transaction::redeemRewards( Clientele& clientele,  Rewards& rewards, const std::string &custID) {
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
