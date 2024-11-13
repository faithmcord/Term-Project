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
    int makePurchase(int productsPurchased, int productID[], int amounts[]);

    int redeemRewards();
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
    //TODO:
    //isProductNameValid
        //return -1
    //isProductPrice Valid
        //return -2
    // bool validInitialStock = Product::isValidQuantity(initialStock);
    // if (!validInitialStock) {
    //     return -3;
    // }
    // else {
    //     // do nothing
    // }
    // std::string productID;
    // while (Inventory::doesExist(productID) || productID.empty()) {
    //     productID = generateProductID();
    // }
    // const Product newProduct = Product(productID, productName, price, initialStock);
    // Inventory::addNew(newProduct);

    const Product newProduct = Product(productName, price, initialStock);
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
     std::string _line, nameString, priceString, quantityString;
     // std::regex pattern(" [^\\n]*\\n");

     // Colors text Red lol
     std::string errorColorMod = "\033[1;31m";
     std::string defaultColorMod = "\033[1;39m";

    while (true) {
        // do { saveFile.getline(buffer,BUFFER_SIZE, '\n'); } while (buffer[0] == '\0');
        // saveFile.getline(buffer,BUFFER_SIZE, '\n');
        // saveFile.getline(buffer,BUFFER_SIZE, '\n');
        // nameString = buffer;
        // saveFile.getline(buffer,BUFFER_SIZE, '\n');
        // priceString = buffer;
        // saveFile.getline(buffer,BUFFER_SIZE, '\n');
        // quantityString = buffer;

        // Information not needed for the constructor (Index and ID)
        std::getline (saveFile, _line);
        std::getline (saveFile, _line);

        std::getline (saveFile, nameString);
        std::getline (saveFile, priceString);
        std::getline (saveFile, quantityString);

        nameString.erase(0,6);
        priceString.erase(0,7);
        quantityString.erase(0,10);

        break;
    }



     // Until Empty Line
     // while (getline(saveFile, _line)) {
     //     if (getline(saveFile, _line) &&
     //         getline(saveFile, nameString) &&
     //         getline(saveFile, priceString) &&
     //         getline(saveFile, quantityString) ) {
//
//             std::regex_search(priceString, priceString, pattern);
//             std::regex_search(quantityString, quantityString, pattern);
//             std::regex_search(nameString, nameString, pattern);
//
//             try {
//                 this -> createProduct(nameString, stod(priceString), stoi(quantityString));
//             } catch (std::invalid_argument &invalid_argument) {
//                 std::cout << errorColorMod << "Load file problem encountered. All products might not be loaded. Please review Products.txt\n"
//                              "Reference:\t" << invalid_argument.what() << defaultColorMod << '\n';
//                 continue;
//             } catch (std::out_of_range &out_of_range) {
//                 std::cout << errorColorMod << "Load file problem encountered. All products might not be loaded. Please review Products.txt\n"
//                              "Reference:\t" << out_of_range.what() << defaultColorMod << '\n';
//                 continue;
//             }
//         } else {
//             std::cout << errorColorMod << "Load file problem encountered. All Products might not be loaded. Please review Products.txt\n"
//                                           "Reference:\t Last product in Products.txt missing information!!" << defaultColorMod << '\n';
//             break;
//         }
//     }
     saveFile.close();
}




inline int Inventory::makePurchase(int productsPurchased, int productID[], int amounts[]) {
    return -999;
}

inline int Inventory::redeemRewards() {
    return -999;
}


#endif //INVENTORY_H
