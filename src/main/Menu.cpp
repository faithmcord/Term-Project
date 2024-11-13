/**********************
*
* File Name:    Menu.cpp
* Author(s):    Courtney Arena <ca54s@missouristate.edu>
* Description:
*
* Course:      CSC 455 - Software Quality Assurance
* Instructor:  Mohammed Belkhouche
* Project:     Term Project
* Date:        8 November 2024
*
***********************/

#include "include/Clientele.h"
#include "include/Inventory.h"
#include <iostream>

void displayMenu() {
    std::cout << "====== Customer Reward System Menu ======\n";
    std::cout << "1. Register New Customer\n";
    std::cout << "2. Remove Customer\n";
    std::cout << "3. Add Product\n";
    std::cout << "4. Remove Product\n";
    std::cout << "5. Shopping\n";
    std::cout << "6. View Customer by ID\n";
    std::cout << "7. Redeem Rewards\n";
    std::cout << "8. Exit\n";
    std::cout << "=========================================\n";
    std::cout << "Enter your choice: ";
}

void handleMenuChoice(int choice, Clientele &clientele, Inventory &inventory) {
    switch (choice) {
        case 1:
            // Call the function to register a new customer
            // clientele.registerCustomer();
            break;
        case 2:
            // Call the function to remove a customer
            // clientele.remove();
            break;
        case 3:
            // Call the function to add a new product
            // inventory.createProduct();
            break;
        case 4:
            // Call the function to remove a product
            // inventory.remove();
            break;
        case 5:
            // Call the function for shopping
            // Transaction::shopping();
            break;
        case 6:
            // Call the function to view a customer by ID
            // clientele.displayOne();
            break;
        case 7:
            // Call the function to redeem rewards
            // Transaction::redeemRewards();
            break;
        case 8:
            std::cout << "Exiting the program. Goodbye!";
            break;
        default:
            std::cout << "Invalid choice. Please try again.";
    }
}

int main() {
    int choice;
    // Product::productCount = 0;
    Inventory inventory = Inventory(DEFAULT_INVENTORY_SAVE_PATH);
    Clientele clientele = Clientele(DEFAULT_CLIENTELE_SAVE_PATH);
    do {
        displayMenu();
        std::cin >> choice;
        handleMenuChoice(choice, clientele, inventory);
    } while (choice != 8);  // 8 is the exit condition

    return 0;
}