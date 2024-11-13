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

#include "include/Clientele.h"
#include "include/Inventory.h"
#include "include/Utilities.h"
#include <iostream>

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
        case 1: {  // Register New Customer
            std::cout << "\n--- Register New Customer ---\n";
            clientele.registerCustomer();  // Make sure this function handles input and validation
            break;
        }
        case 2: {  // Remove Customer
            std::string customerId;
            std::cout << "\nEnter Customer ID to remove: ";
            std::cin >> customerId;
            clientele.removeCustomer(customerId);  // Assume this function verifies and deletes the customer
            break;
        }
        case 3: {  // Add Product
            std::cout << "\n--- Add New Product ---\n";
            inventory.createProduct();  // Function to handle input for product details and validation
            break;
        }
        case 4: {  // Remove Product
            std::string productId;
            std::cout << "\nEnter Product ID to remove: ";
            std::cin >> productId;
            inventory.removeProduct(productId);  // Verify and remove the product from inventory
            break;
        }
        case 5: {  // Shopping
            std::cout << "\n--- Shopping ---\n";
            Utilities::shopping(clientele, inventory);  // Pass objects for transaction handling
            break;
        }
        case 6: {  // View Customer by ID
            std::string customerId;
            std::cout << "\nEnter Customer ID to view: ";
            std::cin >> customerId;
            clientele.displayOne(customerId);  // Display customer info by ID
            break;
        }
        case 7: {  // Redeem Rewards
            std::cout << "\n--- Redeem Rewards ---\n";
            Utilities::redeemRewards(clientele);  // Assume redeemRewards prompts for necessary info
            break;
        }
        case 8:
            std::cout << "\nExiting the program. Goodbye!\n";
            break;
        default:
            std::cout << "\nInvalid choice. Please try again.\n";
            break;
    }
}

int main() {
    int choice;
    Inventory inventory(DEFAULT_INVENTORY_SAVE_PATH);
    Clientele clientele(DEFAULT_CLIENTELE_SAVE_PATH);
    do {
        displayMenu();
        std::cin >> choice;
        
        // Validate input to ensure it is an integer
        if (std::cin.fail()) {
            std::cin.clear();  // Clear error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Discard invalid input
            std::cout << "\nInvalid input. Please enter a number.\n";
            continue;
        }
        
        handleMenuChoice(choice, clientele, inventory);
    } while (choice != 8);  // 8 is the exit condition

    return 0;
}
