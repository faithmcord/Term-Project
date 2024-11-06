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

#include "Clientele.cpp"
#include "Inventory.cpp"

string REWARDS_CONFIG_PATH = "config.txt"; //store $ -> point conversion
const int MAX_CART_SIZE = 20;

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
    int makeTransaction(Clientele clientele, Inventory inventory, int custID);

    bool doesFileExist(string file);

};