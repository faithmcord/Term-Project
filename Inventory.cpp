/**********************
*
* File Name:    Inventory.cpp
* Author(s):
* Description:
*
* Course:      CSC 455 - Software Quality Assurance
* Instructor:  Mohammed Belkhouche
* Project:     Term Project
* Date:        8 November 2024
*
***********************/

#include "Includes.cpp"
#include "Product.cpp"
#include "DataBase.cpp"

//GLOBALS
string DEFAULT_SAVE_PATH = 'products.txt';
string DEFAULT_TRANSACTION_LOG_PATH = 'transactions.txt';


//NOTE: Inventory.cpp and Clientele.cpp can be abstracted to one class

/**
 * @class Inventory
 * @extends map
 * @brief a dictionary of all customers of the store indexed by their customer ID
 */
class Inventory:public map<int, Product::Product>{
    /**
    * @brief the directory of the save file
    */
    string savePath;

    /**
     * @brief the directory of the transaction log file
     */
    string transactionLogPath;

    /**
     * @brief appends transaction to the end of a log file
     */
    void logTransaction();


    public:

    explicit Inventory();

    explicit Inventory(const string &loadFile);

    explicit Inventory(const string &loadFile, const string &transLogFile);

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
    int createProduct(string productName, float price, int initialStock);

    //abstract
    /**
     * @brief deletes a product of the specified product ID
     *
     * @param ProductID the identifying ID numbers of the product to be deleted
     * @return 0 on successful deletion
     * @return -1 on product not found
     */
    int removeProduct(int ProductID);

    //abstract
    /**
     * @brief displays a list of all products available
     * @returns nothing
     */
    void display();

    /**
     * @brief checks for how much stock of a product is currently in possession
     *
     * @param productID identifying ID numbers of the product to be checked
     *
     * @return amount currently in stock
     * @return -1 if invalid productID
     */
    static int isEnoughInInventory (int productID);

    /**
     * @brief decrements the amount of product held in inventory by the amount purchased
     *
     * @param productsPurchased number of items purchased in one transaction
     * @param productID         array of identifying ID numbers of the product to be purchased
     * @param amounts           array of corresponding quantities purchased
     * @return 0 on success
     */
    int makePurchase(int productsPurchased, int productID[], int amounts[]);

    int preserveState();

    int redeemRewards();
};


Inventory::Inventory() {
 savePath = DEFAULT_SAVE_PATH;
 transactionLogPath = DEFAULT_SAVE_PATH;
}

Inventory::Inventory(const string &loadFile) {
 savePath = loadFile;
 transactionLogPath = DEFAULT_SAVE_PATH;
}

Inventory::Inventory(const string &loadFile, const string &transLogFile) {
 savePath = loadFile;
 transactionLogPath = DEFAULT_SAVE_PATH;
}


void Inventory::logTransaction() {

}

int Inventory::createProduct(string productName, float price, int initialStock) {
 return 0;
}

int Inventory::removeProduct(int ProductID) {
 return 0;
}

void Inventory::display() {

}

int Inventory::isEnoughInInventory(int productID) {
 return 0;
}

int Inventory::makePurchase(int productsPurchased, int productID[], int amounts[]) {
 return 0;
}