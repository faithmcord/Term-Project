/**********************
*
* File Name:    Inventory.h
* Author(s):	   Xander Palermo <ajp2s@missouristate.edu>
* Description:
*
* Course:      CSC 455 - Software Quality Assurance
* Instructor:  Mohammed Belkhouche
* Project:     Term Project
* Date:        8 November 2024
*
***********************/

#ifndef INVENTORY_H
#define INVENTORY_H

#include "Includes.cpp"
#include "Product.cpp"
#include "Database.h"

/**
 * @class Inventory
 * @brief a dictionary of all customers of the store indexed by their customer ID
 */
class Inventory:public Database<Product>{
    /**
     * @brief the directory of the transaction log file
     */
    std::string transactionLogPath;

    static std::string generateProductID ();

    /**
     * @brief appends transaction to the end of a log file
     */
    void logTransaction();

    public:

    explicit Inventory(const std::string &loadFile);

    /**
     * @brief Creates a new product and stores it into the dictionary
     *
     * @pre productName < 30 characters long
     * @pre price is a positive amount
     * @pre price contains only 2 decimal places
     *
     * @param productName   a description of the product
     * @param price         the cost to purchase the product
     * @param initialStock  the number of product currently possessed in the inventory
     * @return the product ID of the newly added product
     *          @returns -1 on invalid productName
     *          @returns -2 on invalid price
     *          @returns -3 on invalid initialStock
     */
    int createProduct(const std::string &productName, double price, int initialStock);

    //abstract
    /**
     * @brief deletes a product of the specified product ID
     *
     * @param ProductID the identifying ID numbers of the product to be deleted
     * @return 0 on successful deletion
     * @return -1 on product not found
     */
    // int removeProduct(int ProductID);

    /**
     * @brief checks for how much stock of a product is currently in possession
     *
     * @param productID identifying ID numbers of the product to be checked
     *
     * @return amount currently in stock
     * @return -1 if invalid productID
     */
    int isEnoughInInventory (const std::string &productID);

    /**
     * @brief decrements the amount of product held in inventory by the amount purchased
     *
     * @param productsPurchased number of items purchased in one transaction
     * @param productID         array of identifying ID numbers of the product to be purchased
     * @param amounts           array of corresponding quantities purchased
     * @return 0 on success
     */
    int makePurchase(int productsPurchased, int productID[], int amounts[]);

    int redeemRewards();
};

#endif //INVENTORY_H
