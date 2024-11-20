/**********************
*
* File Name:    Menu.cpp
* Author(s):    Courtney Arena <ca54s@missouristate.edu>
* Description:  Console-based menu interface for the Customer Reward System.
*
* Course:       CSC 455 - Software Quality Assurance
* Instructor:   Mohammed Belkhouche
* Project:      Term Project
* Date:         8 November 2024
*
***********************/

// MAKE
#include "Clientele.h"
#include "Inventory.h"
#include "Utilities.h"
#include "Transaction.h"

// CMAKE
#include "include/Clientele.h"
#include "include/Inventory.h"
#include "include/Utilities.h"
#include "include/Transaction.h"

#include <iostream>
#include <limits>

// Function prototypes
void registerCustomer(Clientele &clientele);
void removeCustomer(Clientele &clientele);
void addProduct(Inventory &inventory);
void removeProduct(Inventory &inventory);
void shopping(Clientele &clientele, Inventory &inventory);
void viewCustomer(Clientele &clientele);
void redeemRewards(Clientele &clientele, Rewards &rewards);

void configureRewards();
void addReward (Rewards &rewards);
void removeReward(Rewards &rewards);
void rewardsSubMenu(Rewards &rewards);

void displayMenu() {
    std::cout << "\n====== Customer Reward System Menu ======\n";
    std::cout << "1. Register New Customer\n";
    std::cout << "2. Remove Customer\n";
    std::cout << "3. Add Product\n";
    std::cout << "4. Remove Product\n";
    std::cout << "5. Shopping\n";
    std::cout << "6. View Customer by ID\n";
    std::cout << "7. Redeem Rewards\n";
    std::cout << "8. Configure Rewards\n";
    std::cout << "9. Exit\n";
    std::cout << "=========================================\n";
    std::cout << "Enter your choice (1-8): ";
}

void handleMenuChoice(int choice, Clientele &clientele, Inventory &inventory, Rewards &rewards) {
    switch (choice) {
        case 1:
            registerCustomer(clientele);
            break;
        case 2:
            removeCustomer(clientele);
            break;
        case 3:
            addProduct(inventory);
            break;
        case 4:
            removeProduct(inventory);
            break;
        case 5:
            shopping(clientele, inventory);
            break;
        case 6:
            viewCustomer(clientele);
            break;
        case 7:
            redeemRewards(clientele, rewards);
            break;
        case 8:
            rewardsSubMenu(rewards);
            break;
        case 9:
            std::cout << "\nExiting the program. Goodbye!\n";
            break;
        default:
            std::cout << "\nInvalid choice. Please try again.\n";
            break;
    }
}

// Individual functions for each menu option

void registerCustomer(Clientele &clientele) {
    std::string userName, firstName, lastName, creditCardInfo;
    int age;

    std::cout << "\n--- Register New Customer ---\n";
    std::cout << "Enter Username: ";
    std::cin >> userName;
    std::cout << "Enter First Name: ";
    std::cin >> firstName;
    std::cout << "Enter Last Name: ";
    std::cin >> lastName;

    std::cout << "Enter Age: ";
    std::cin >> age;
    if (age < 18 || age > 100) {
        std::cout << "Invalid age. Age must be between 18 and 100.\n";
        return;
    }

    std::cout << "Enter Credit Card Number (xxxx-xxxx-xxxx format): ";
    std::cin >> creditCardInfo;

    try {
        std::string custID = clientele.registerCustomer(userName, firstName, lastName, age, creditCardInfo);
        std::cout << "Customer registered successfully with ID: " << custID << "\n";
    } catch (const std::invalid_argument &e) {
        std::cout << "Error registering customer: " << e.what() << "\n";
    }
}

void removeCustomer(Clientele &clientele) {
    while (true) {
        std::cout << "\nEnter Customer ID to remove (or enter 0 to return to the main menu): ";
        std::string customerId;
        std::cin >> customerId;

        if (customerId == "0") {
            std::cout << "Returning to the main menu...\n";
            break;
        }

        if (clientele.getCustomerRewards(customerId) == -1) {
            std::cout << "Error: Invalid Customer ID. Please try again.\n";
            continue;
        }

        std::cout << "Are you sure you want to remove Customer ID " << customerId << "? (y/n): ";
        char confirmation;
        std::cin >> confirmation;

        if (confirmation == 'y' || confirmation == 'Y') {
            clientele.remove(customerId);
            std::cout << "Customer ID " << customerId << " has been successfully removed.\n";
            break;
        } else {
            std::cout << "Removal canceled. Returning to the main menu...\n";
            break;
        }
    }
}

void addProduct(Inventory &inventory) {
    std::string productName;
    double price;
    int initialStock;

    std::cout << "\n--- Add New Product ---\n";
    while (true) {
        std::cout << "Enter Product Name (max 30 characters): ";
        std::cin.ignore();
        std::getline(std::cin, productName);
        if (!productName.empty() && productName.length() <= 30) break;
        std::cout << "Invalid input. Please try again.\n";
    }

    while (true) {
        std::cout << "Enter Product Price (positive number): ";
        std::cin >> price;
        if (!std::cin.fail() && price > 0) break;
        std::cout << "Invalid input. Please try again.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    while (true) {
        std::cout << "Enter Initial Stock Quantity (non-negative): ";
        std::cin >> initialStock;
        if (!std::cin.fail() && initialStock >= 0) break;
        std::cout << "Invalid input. Please try again.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    try {
        std::string productID = inventory.createProduct(productName, price, initialStock);
        std::cout << "Product added successfully with ID: " << productID << "\n";
        inventory.save();
    } catch (const std::invalid_argument &e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void removeProduct(Inventory &inventory) {
    std::string productId;
    std::cout << "\nEnter Product ID to remove: ";
    std::cin >> productId;
    // try {
    const int success = inventory.remove(productId);
    if (success) {
        std::cout << "Product removed successfully.\n";
    }
    else {
        std::cout << "Could not find product\n";
    }
    // } catch (const std::invalid_argument &e) {
    //     std::cout << "Error: " << e.what() << "\n";
    // }
}

void shopping(Clientele &clientele, Inventory &inventory) {
    std::cout << "\n--- Shopping ---\n";

    // Step 1: Prompt for customer username
    std::cout << "Enter your username: ";
    std::string username;
    std::cin >> username;

    // Step 2: Validate if the customer exists
    // std::string customerID;
    // bool customerFound = false;
    // for (const auto &entry : clientele.getContainer()) {
    //     if (entry.second.getUsername() == username) {
    //         customerID = entry.first;
    //         customerFound = true;
    //         break;
    //     }
    // }
    const std::string customerID = clientele.findUser(username);
    const bool customerFound = !customerID.empty();

    if (!customerFound) {
        std::cout << "Error: Username not found. Returning to main menu...\n";
        return;
    }

    // Step 3: Call makeTransaction to handle the actual shopping and reward point update
    // This will handle product selection, validation, stock checks, and reward point application
    int result = Transaction::makeTransaction(clientele, inventory, customerID);

    if (result == 0) {
        std::cout << "Purchase successful! Rewards have been added to your account.\n";
    } else {
        std::cout << "Purchase failed. Returning to main menu...\n";
    }

    // Step 4: Return to menu
    std::cout << "Returning to main menu...\n";
}

void viewCustomer(Clientele &clientele) {
    std::string customerId;
    std::cout << "\nEnter Customer ID to view: ";
    std::cin >> customerId;
    clientele.displayOne(customerId);
}

void configureRewards() {
    std::cout << "\n--- Configure Rewards ---";
    std::cout << "Current Conversion Rate: " << Transaction::conversionToString << '\n';
    double dollarsIn;
    int pointsOut;
    do {
        std::cout << "Number of dollars go into the conversion: ";
        std::cin >> dollarsIn;
        std::cout << "Number of points to come out of the conversion ";
        std::cin >> pointsOut;
    } while (!Transaction::setRewardsConversion(dollarsIn,pointsOut));
}

void redeemRewards(Clientele &clientele, Rewards &rewards) {
    std::cout << "\n--- Redeem Rewards ---\n";

    // Step 1: Prompt for customer username
    std::cout << "Enter your username: ";
    std::string username;
    std::cin >> username;

    // Step 2: Validate if the customer exists
    const std::string customerID = clientele.findUser(username);
    const bool customerFound = !customerID.empty();

    if (!customerFound) {
        std::cout << "Error: Username not found. Returning to main menu...\n";
        return;
    }

    // Step 3: Call redeemRewards to handle the reward redemption logic
    int result = Transaction::redeemRewards(clientele, rewards, customerID);

    if (result == 0) {
        std::cout << "Reward redemption successful!\n";
    } else {
        std::cout << "Reward redemption failed. Returning to main menu...\n";
    }

    // Step 4: Return to menu
    std::cout << "Returning to main menu...\n";
}

void addReward (Rewards &rewards) {
    std::cout << "\n--- Add New Reward ---\n";

    std::string rewardName;
    int price;
    int initialStock;

    while (true) {
        std::cout << "Enter a Reward Name (max 30 characters): ";
        std::cin.ignore();
        std::getline(std::cin, rewardName);
        if (!rewardName.empty() && rewardName.length() <= 30) break;
        else std::cout << "Invalid input. Please try again.\n";
    }
    while (true) {
        std::cout << "Enter a Reward Price (positive number): ";
        std::cin >> price;
        if (!std::cin.fail() && price > 0) break;
        else std::cout << "Invalid input. Please try again.\n";
    }
    while (true) {
        std::cout << "Enter a Initial Stock Quantity (positive number): ";
        std::cin >> initialStock;
        if (!std::cin.fail() && initialStock >= 0) break;
        else std::cout << "Invalid input. Please try again.\n";
    }

    try {
        std::string rewardID = rewards.createReward(rewardName,price,initialStock);
        std::cout << "Reward added succesffuly with ID: " << rewardID;
        rewards.save();
    } catch (const std::invalid_argument &e) {
        std::cout << "ErrorL " << e.what() << "\n";
    }
}

void removeReward(Rewards& rewards) {
    std::string rewardID;
    std::cout << "\n--- Remove Reward ---\n";
    std::cout << "Enter Reward ID to remove: ";
    std::cin >> rewardID;
    const int success = rewards.remove(rewardID);
    if (success) {
        std::cout << "Reward removed successfully";
    }
    else {
        std::cout << "Could not find product\n";
    }
}

void rewardsSubMenu(Rewards &rewards) {
    do {
        std::cout << "\n============= Rewards Config ============\n";
        std::cout << "1. Change Reward Conversion Rate\n";
        std::cout << "2. Add Reward\n";
        std::cout << "3. Remove Reward\n";
        std::cout << "4. Return to Main Menu\n";
        std::cout << "=========================================\n";
        std::cout << "Enter your choice (1-8): ";

        std::string input;
        std::cin >> input;
        switch (input) {
            case 1:
                configureRewards();
                break;
            case 2:
                addReward(rewards);
                break;
            case 3:
                removeReward(rewards);
                break;
            case 4:
                return;
            default:
                std::cout << "\nInvalid choice. Please try again.\n";
            break;
    }
    } while (true);
}

int main() {
    // Create objects
    int choice;
    Inventory inventory(DEFAULT_INVENTORY_SAVE_PATH);
    Clientele clientele(DEFAULT_CLIENTELE_SAVE_PATH);
    Rewards rewards(DEFAULT_REWARDS_SAVE_PATH);

    // Load data into objects
    inventory.load();
    clientele.load();
    rewards.load();
    Transaction::loadConfig(DEFAULT_REWARDS_CONFIG_PATH);

    // Initiate GUI
    do {
        displayMenu();
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Try again.\n";
            continue;
        }

        handleMenuChoice(choice, clientele, inventory, rewards);
    } while (choice != 8);

    // save state for next use
    inventory.save();
    clientele.save();
    rewards.save();
    Transaction::saveConfig(DEFAULT_REWARDS_CONFIG_PATH);
    return 0;
}
