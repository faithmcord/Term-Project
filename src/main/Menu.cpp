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
            
            std::cout << "Enter Credit Card Number (xxxx-xxxx-xxxx format): ";
            std::cin >> creditCardInfo;
            
            try {
                // Call registerCustomer with the collected information
                std::string custID = clientele.registerCustomer(userName, firstName, lastName, age, creditCardInfo);
                std::cout << "Customer registered successfully with ID: " << custID << "\n";
            } catch (const std::invalid_argument &e) {
                std::cout << "Error registering customer: " << e.what() << "\n";
            }
            break;
        }
        case 2: {  // Remove Customer
            std::string customerId;
            std::cout << "\nEnter Customer ID to remove: ";
            std::cin >> customerId;
            clientele.remove(customerId);  // Assume this function verifies and deletes the customer
            break;
        }
        case 3: {  // Add Product
            std::string productName;
            double price;
            int initialStock;

            std::cout << "\n--- Add New Product ---\n";
            std::cout << "Enter Product Name: ";
            std::cin.ignore();  // To clear the newline from previous input
            std::getline(std::cin, productName);
            
            std::cout << "Enter Product Price: ";
            std::cin >> price;
            
            std::cout << "Enter Initial Stock Quantity: ";
            std::cin >> initialStock;

            // Check if product price and stock are valid
            if (price <= 0) {
                std::cout << "Invalid price. Price must be a positive number.\n";
                break;
            }
            if (initialStock < 0) {
                std::cout << "Invalid stock. Stock cannot be negative.\n";
               
            break;
        }
        case 4: {  // Remove Product
            std::string productId;
            std::cout << "\nEnter Product ID to remove: ";
            std::cin >> productId;
            inventory.remove(productId);  // Verify and remove the product from inventory
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
