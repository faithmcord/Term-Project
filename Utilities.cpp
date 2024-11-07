/**********************
*
* File Name:    Utilities.cpp
* Author(s):    Xander Palermo <ajp2s@missouristate.edu>
* Description:  A container object that manages and preserves all loaded customers in memory
*
* Course:      CSC 455 - Software Quality Assurance
* Instructor:  Mohammed Belkhouche
* Project:     Term Project
* Date:        8 November 2024
*
***********************/

#include <fstream>

const std::string REWARDS_CONFIG_PATH = "config.txt"; //store $ -> point conversion
constexpr int MAX_CART_SIZE = 20;

struct item {
    int productID;
    int amount;
};

struct ShoppingCart {
    item productsInCart[MAX_CART_SIZE];
};

class Utilities {
  public:

    /***
    * @brief updates clientele and inventory atomically
    */
    template <typename Clientele, typename Inventory>
    static int makeTransaction(const Clientele& clientele, const Inventory& inventory, int custID);

    static bool doesFileExist(const std::string& file);

};

template <typename Clientele, typename Inventory>
int Utilities::makeTransaction(const Clientele& clientele, const Inventory& inventory, int custID) {
    return 0;
}

bool Utilities::doesFileExist(const std::string& file) {
    std::fstream fs;
    fs.open(file, std::ios::in);
    if (fs.is_open()) {
        fs.close();
        return true;
    } else
        return false;
}

