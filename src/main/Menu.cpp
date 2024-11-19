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

#include "Clientele.h"
#include "Inventory.h"
#include "Utilities.h"
#include <iostream>
#include <limits>

#include "Transaction.h"
#include "include/Clientele.h"
#include "include/Inventory.h"

// Function prototypes
void registerCustomer(Clientele &clientele);
void removeCustomer(Clientele &clientele);
void addProduct(Inventory &inventory);
void removeProduct(Inventory &inventory);
void shopping(Clientele &clientele, Inventory &inventory);
void viewCustomer(Clientele &clientele);
void redeemRewards(Clientele &clientele);


void displayMenu() {
    std::cout << "\n====== Customer Reward System Menu ======\n";
    std::cout << "1. Register New Customer\n";
    std::cout << "2. Remove Customer\n";
    std::cout << "3. Add Product\n";
    std::cout << "4. Remove Product\n";
    std::cout << "5. Shopping\n";
    std::cout << "6. View Customer by ID\n";
    std::cout << "7. Redeem Rewards\n";
    std::cout << "8. Exit\n";
    std::cout << "=========================================\n";
    std::cout << "Enter your choice (1-8): ";
}

void handleMenuChoice(int choice, Clientele &clientele, Inventory &inventory) {
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
            redeemRewards(clientele);
            break;
        case 8:
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
    try {
        inventory.remove(productId);
        std::cout << "Product removed successfully.\n";
    } catch (const std::invalid_argument &e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void shopping(Clientele &clientele, Inventory &inventory) {
    std::cout << "\n--- Shopping ---\n";

    // Step 1: Prompt for customer username
    std::cout << "Enter your username: ";
    std::string username;
    std::cin >> username;

    // Step 2: Validate if the customer exists
    std::string customerID;
    bool customerFound = false;
    for (const auto &entry : clientele.getContainer()) {
        if (entry.second.getUsername() == username) {
            customerID = entry.first;
            customerFound = true;
            break;
        }
    }

    if (!customerFound) {
        std::cout << "Error: Username not found. Returning to main menu...\n";
        return;
    }

    // Step 3: List available products
    std::cout << "\nAvailable Products:\n";
    for (const auto &entry : inventory.getContainer()) {
        const auto &product = entry.second;
        std::cout << "ID: " << entry.first
                  << " | Name: " << product.getName()
                  << " | Price: $" << product.getPrice()
                  << " | Stock: " << product.getQuantity() << "\n";
    }

    // Step 4: Prompt for product ID and quantity
    std::cout << "\nEnter the Product ID of the item you want to purchase: ";
    std::string productID;
    std::cin >> productID;

    const auto productIter = inventory.getContainer().find(productID);
    if (productIter == inventory.getContainer().end()) {
        std::cout << "Error: Invalid Product ID. Returning to main menu...\n";
        return;
    }

    std::cout << "Enter the quantity to purchase: ";
    int quantity;
    std::cin >> quantity;

    // Step 5: Check inventory stock
    int stockAvailable = inventory.isEnoughInInventory(productID);
    if (stockAvailable < quantity) {
        std::cout << "Error: Not enough stock available. Returning to main menu...\n";
        return;
    }

    // Step 6: Confirm purchase
    const auto &product = productIter->second;
    double totalCost = product.getPrice() * quantity;
    std::cout << "\nPurchase Summary:\n";
    std::cout << "Product: " << product.getName()
              << "\nQuantity: " << quantity
              << "\nTotal Cost: $" << totalCost << "\n";

    std::cout << "Do you want to confirm this purchase? (yes/no): ";
    std::string confirmation;
    std::cin >> confirmation;

    if (confirmation != "yes") {
        std::cout << "Purchase canceled. Returning to main menu...\n";
        return;
    }

    // Step 7: Process purchase
    inventory.updateInventory(productID, -quantity);  // Decrease inventory by the quantity purchased
    clientele.updateCustomerRewards(customerID, static_cast<int>(totalCost / 10));  // Add rewards points

    std::cout << "Purchase successful! Rewards have been added to your account.\n";

    // Step 8: Return to menu
    std::cout << "Returning to main menu...\n";
}


void viewCustomer(Clientele &clientele) {
    std::string customerId;
    std::cout << "\nEnter Customer ID to view: ";
    std::cin >> customerId;
    clientele.displayOne(customerId);
}

void redeemRewards(Clientele &clientele) {
    while (true) {
        std::cout << "\n--- Redeem Rewards ---\n";
        std::cout << "Enter Customer ID to redeem rewards (or enter 0 to return to the main menu): ";
        std::string customerId;
        std::cin >> customerId;

        if (customerId == "0") {
            std::cout << "Returning to the main menu...\n";
            break;
        }

        int currentRewards = clientele.getCustomerRewards(customerId);
        if (currentRewards == -1) {
            std::cout << "Invalid Customer ID. Please try again.\n";
            continue;
        }

        std::cout << "Customer has " << currentRewards << " points.\n";
        std::cout << "Enter points to redeem: ";
        int pointsToRedeem;
        std::cin >> pointsToRedeem;

        if (pointsToRedeem > currentRewards) {
            std::cout << "Not enough points.\n";
            continue;
        }

        clientele.updateCustomerRewards(customerId, -pointsToRedeem);
        std::cout << "Redeemed successfully.\n";
        break;
    }
}

int main() {
    int choice;
    Inventory inventory(DEFAULT_INVENTORY_SAVE_PATH);
    Clientele clientele(DEFAULT_CLIENTELE_SAVE_PATH);
    Transaction::loadConfig(DEFAULT_REWARDS_CONFIG_PATH);

    do {
        displayMenu();
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Try again.\n";
            continue;
        }

        handleMenuChoice(choice, clientele, inventory);
    } while (choice != 8);

    // save state for next use
    inventory.save();
    clientele.save();
    Transaction::saveConfig(DEFAULT_REWARDS_CONFIG_PATH);
    return 0;
}
