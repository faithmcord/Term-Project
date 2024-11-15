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
            if (age < 18 || age > 100) {
                std::cout << "Invalid age. Age must be between 18 and 100.\n";
                break;
            }
            
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
            while (true) {
                std::cout << "\nEnter Customer ID to remove (or enter 0 to return to the main menu): ";
                std::string customerId;
                std::cin >> customerId;

                if (customerId == "0") {
                    std::cout << "Returning to the main menu...\n";
                    break;  // Exit the loop to return to the main menu
                }

                // Verify if the customer ID exists
                if (clientele.getCustomerRewards(customerId) == -1) {
                    std::cout << "Error: Invalid Customer ID. Please try again.\n";
                    continue;  // Restart the loop to prompt for a valid ID
                }

                // Ask for confirmation
                std::cout << "Are you sure you want to remove Customer ID " << customerId << "? (y/n): ";
                char confirmation;
                std::cin >> confirmation;

                if (confirmation == 'y' || confirmation == 'Y') {
                    // Remove the customer
                    clientele.remove(customerId);
                    std::cout << "Customer ID " << customerId << " has been successfully removed.\n";
                    break;  // Exit the loop after successful removal
                } else if (confirmation == 'n' || confirmation == 'N') {
                    std::cout << "Removal canceled. Returning to the main menu...\n";
                    break;  // Exit the loop without removing
                } else {
                    std::cout << "Invalid input. Returning to the main menu...\n";
                    break;  // Exit the loop for unexpected input
                }
            }
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

            try {
                // Add the new product to the inventory
                std::string productID = inventory.createProduct(productName, price, initialStock);
                std::cout << "Product added successfully with ID: " << productID << "\n";

                // Save the updated inventory
                inventory.save();
                std::cout << "Product inventory updated successfully.\n";

                // Return to the main menu
                std::cout << "Returning to the main menu...\n";
                break;
            } catch (const std::invalid_argument &e) {
                std::cout << "Error: " << e.what() << "\n";
            } catch (const std::exception &e) {
                std::cout << "Unexpected error: " << e.what() << "\n";
            }

            break;  // Ensure it exits the case if an error occurs
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
            while (true) {
                std::cout << "\n--- Redeem Rewards ---\n";

                std::cout << "\nEnter Customer ID to redeem rewards (or enter 0 to return to the main menu): ";
                std::string customerId;
                std::cin >> customerId;

                if (customerId == "0") {
                    std::cout << "Returning to the main menu...\n";
                    break;  // Exit the outer loop to return to the main menu
                }

                // Verify if the customer ID exists
                if (clientele.getCustomerRewards(customerId) == -1) {
                    std::cout << "Error: Invalid Customer ID. Please try again.\n";
                    continue;  // Restart the loop to prompt for a new ID
                }

                // Retrieve the current reward points for the customer
                int currentRewards = clientele.getCustomerRewards(customerId);

                // Display current reward points
                std::cout << "Customer " << customerId << " has " << currentRewards << " reward points.\n";

                bool redeemed = false;
                while (!redeemed) {
                    // Prompt user for redemption amount
                    std::cout << "\nEnter the number of points to redeem (or 0 to return to the main menu): ";
                    int pointsToRedeem;
                    std::cin >> pointsToRedeem;

                    // Validate input
                    if (std::cin.fail() || pointsToRedeem < 0) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Invalid input. Please enter a valid number of points or 0 to return to the main menu.\n";
                        continue;  // Restart the inner loop for valid input
                    }

                    if (pointsToRedeem == 0) {
                        std::cout << "Returning to the main menu...\n";
                        break;  // Exit the inner loop to return to the main menu
                    }

                    if (pointsToRedeem > currentRewards) {
                        std::cout << "Error: Insufficient reward points. You only have " << currentRewards << " points.\n";
                        continue;  // Restart the inner loop for a valid redemption amount
                    }

                    // Update the rewards
                    int updateStatus = clientele.updateCustomerRewards(customerId, -pointsToRedeem);
                    if (updateStatus == 0) {
                        std::cout << "\nSuccessfully redeemed " << pointsToRedeem << " points! Remaining balance: "
                                << (currentRewards - pointsToRedeem) << " points.\n";
                        redeemed = true;  // Exit the inner loop after successful redemption
                    } else {
                        std::cout << "Error redeeming rewards. Please try again.\n";
                    }
                }

                break;  // Exit the outer loop after completing the redemption process
            }
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

int main () {
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
