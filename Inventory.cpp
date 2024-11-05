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

#include <map>

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

    public:
      //Product Addition
      int createProduct(Product::Product) {
          return 9999999;
      }

      //Product Removal
      int deleteProduct(int ProductID) {
          return 0;
      }

      //Shopping
      int makePurchase(int ProductID) {
          return 0;
      }
};
