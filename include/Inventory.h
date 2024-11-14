/**********************
*
* File Name:    Inventory.h
* Author(s):	Xander Palermo <ajp2s@missouristate.edu>
* Description:  A container object that manages and preserves all loaded Products in memory
*
* Course:      CSC 455 - Software Quality Assurance
* Instructor:  Mohammed Belkhouche
* Project:     Term Project
* Date:        8 November 2024
*
***********************/

#ifndef INVENTORY_H
#define INVENTORY_H

#include "include/Product.h"
#include "Database.h"
#include <random>


//GLOBAL VARIABLES
constexpr int BUFFER_SIZE = 40;
const std::string DEFAULT_INVENTORY_SAVE_PATH = "resources/products.txt";
const std::string DEFAULT_TRANSACTION_LOG_PATH = "resources/transactions.txt";

/**
 * @class Inventory
 * @brief a dictionary of all customers of the store indexed by their customer ID
 */
class Inventory final :public Database<Product>{
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
     *
     * @return the product ID of the newly added product
     *
     * @throws std::invalid_argument if validation fails
     */
    std::string createProduct(const std::string &productName, double price, int initialStock);

    /**
     * @brief checks for how much stock of a product is currently in possession
     *
     * @param productID identifying ID numbers of the product to be checked
     *
     * @return amount currently in stock
     * @return -1 if invalid productID
     */
     int isEnoughInInventory (const std::string &productID);

    int updateInventory (int amount);

     void save() override;

     void load() override;

    /**
     * @brief decrements the amount of product held in inventory by the amount purchased
     *
     * @param productsPurchased number of items purchased in one transaction
     * @param productID         array of identifying ID numbers of the product to be purchased
     * @param amounts           array of corresponding quantities purchased
     * @return 0 on success
     */
    // int makePurchase(int productsPurchased, int productID[], int amounts[]);
    //
    // int redeemRewards();
};


inline Inventory::Inventory(const std::string &loadFile) : Database<Product> (loadFile) {
    savePath = loadFile;
    transactionLogPath = DEFAULT_TRANSACTION_LOG_PATH;
}

inline std::string Inventory::generateProductID() {
    // Init rand num generator to create ID
    std::random_device random_device;
    std::mt19937 gen(random_device());
    std::uniform_int_distribution<> dis(10000,99999);

    int generatedNum = dis(gen);

    // Concat new product ID
    std::string classifierID = "Prod";
    std::string numberID = std::to_string(generatedNum);
    std::string newID = classifierID + numberID;

    return newID;
}


inline std::string Inventory::createProduct(const std::string &productName, double price, int initialStock) {
    const Product newProduct =  Product(productName, price, initialStock);
    this -> addNew(newProduct);
    std::string prodID = newProduct.getID();
    return prodID;
}

inline int Inventory::isEnoughInInventory(const std::string &productID) {
    // locate product being queried
    const auto index = container.find(productID);
    if (index == container.end()) { // product does not exist
        return -1;
    }
    else {                          // product exists; return amount available
        const int amountInStock = index->second.getQuantity();
        return amountInStock;
    }
}

inline void Inventory::save() {
     std::fstream saveFile;
     saveFile.open(savePath, std::ios::out);
     int indexNumber = 0;
     auto indexPointer = container.begin();
     const auto end = container.end();
     while (indexPointer != end) {
         saveFile << "Customer " << ++indexNumber << '\n';
         std::string output;
         output += indexPointer->second.toString();
         saveFile << output << '\n';
         ++indexPointer;
     }
     saveFile.close();
}

inline void Inventory::load() {
     bool fileExists = Utilities::doesFileExist(savePath);
     if (!fileExists) {
         // nothing to load
         return;
     }
     else {
         /* Do nothing */
     }

     // Init
     std::ifstream saveFile;
     saveFile.open(savePath);
     // char buffer [BUFFER_SIZE];
     // std::regex pattern(" [^\\n]*\\n");

     // Colors text Red lol
     std::string errorColorMod = "\033[1;31m";
     std::string defaultColorMod = "\033[1;39m";

    while (true) {
        std::string line, nameString, priceString, quantityString;

        std::getline (saveFile, line);
        if ( line == "\0" ) {
            break;
        } else {
            /* Do nothing */
        }
        std::getline (saveFile, line);

        std::getline (saveFile, nameString);
        std::getline (saveFile, priceString);
        std::getline (saveFile, quantityString);

        nameString.erase(0,6);
        priceString.erase(0,7);
        quantityString.erase(0,10);

        try {
            this -> createProduct(nameString, stod(priceString), stoi(quantityString));
        } catch ( std::invalid_argument &invalid_argument ) {
            continue;
        } catch ( std::out_of_range &out_of_range) {
            continue;
        }

    }
     saveFile.close();
}




// inline int Inventory::makePurchase(int productsPurchased, int productID[], int amounts[]) {
//     return -999;
// }
//
// inline int Inventory::redeemRewards() {
//     return -999;
// }


#endif //INVENTORY_H
